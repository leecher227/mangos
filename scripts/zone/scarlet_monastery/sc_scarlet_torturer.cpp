/* Copyright (C) 2006,2007 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "../../sc_defines.h"

// **** This script is still under Developement ****

#define SPELL_IMMOLATE		37668

#define SAY_AGGRO1			"What? Oh no. I don't care what you have to say. I just enjoy inflicting pain."
#define SAY_AGGRO2			"You will talk eventually. You might as well spill it now."
#define SAY_AGGRO3			"Confess and we shall set you free."

struct MANGOS_DLL_DECL scarlet_torturerAI : public ScriptedAI
{
    scarlet_torturerAI(Creature *c) : ScriptedAI(c) {Reset();}

    Unit *pTarget;
    uint32 Immolate_Timer;

    void Reset()
    {
        pTarget = NULL;
        Immolate_Timer = 45000;

        if (m_creature)
        {
            m_creature->RemoveAllAuras();
            DoStopAttack();
            DoGoHome();
        }
    }

    void AttackStart(Unit *who)
    {
        if (!who)
            return;

        if (m_creature->getVictim() == NULL && who->isTargetableForAttack() && who!= m_creature)
        {
            DoStartMeleeAttack(who);
            
            //Switch between 3 different aggro saying
            switch (rand()%3)
                {
                case 0:
                    DoYell(SAY_AGGRO1,LANG_UNIVERSAL,NULL);
                    break;

                case 1:
                    DoYell(SAY_AGGRO2,LANG_UNIVERSAL,NULL);
                    break;

                case 2:
                    DoYell(SAY_AGGRO3,LANG_UNIVERSAL,NULL);
                    break;
                }

            pTarget = who;
        }
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!who)
            return;

        if (who->isTargetableForAttack() && IsVisible(who) && who->isInAccessablePlaceFor(m_creature) && m_creature->IsHostileTo(who))
        {
            if ( m_creature->getVictim() == NULL)
            {
                //Begin melee attack if we are within range
                DoStartMeleeAttack(who);

                pTarget = who;
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        //If we had a target and it wasn't cleared then it means the player died from some unknown source
        //But we still need to reset
        if (m_creature->isAlive() && pTarget && !m_creature->getVictim())
        {
            Reset();
            return;
        }

        //Check if we have a current target
        if( m_creature->getVictim() && m_creature->isAlive())
        {
            //Check if we should stop attacking because our victim is no longer attackable
            if (needToStop())
            {
                Reset();
                return;
            }
            
            //Immolate_Timer
            if (Immolate_Timer < diff)
            {
                //Cast
                DoCast(m_creature->getVictim(),SPELL_IMMOLATE);

                //45 seconds until we should cast this agian
                Immolate_Timer = 45000;
            }else Immolate_Timer -= diff;

            //If we are within range melee the target
            if( m_creature->IsWithinDist(m_creature->getVictim(), ATTACK_DIST))
            {
                //Make sure our attack is ready and we arn't currently casting
                if( m_creature->isAttackReady() && !m_creature->m_currentSpell)
                {
                    Unit* newtarget = m_creature->SelectHostilTarget();
                    if(newtarget)
                        AttackStart(newtarget);

                    m_creature->AttackerStateUpdate(m_creature->getVictim());
                    m_creature->resetAttackTimer();
                }
            }
            
            //If we are still alive and we lose our victim it means we killed them
            if(m_creature->isAlive() && !m_creature->getVictim())
            {
                Reset();
            }
        }
    }
}; 
CreatureAI* GetAI_scarlet_torturer(Creature *_Creature)
{
    return new scarlet_torturerAI (_Creature);
}


void AddSC_scarlet_torturer()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="scarlet_torturer";
    newscript->GetAI = GetAI_scarlet_torturer;
    m_scripts[nrscripts++] = newscript;
}