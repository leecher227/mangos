/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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


/* ScriptData
SDName: Boss_Prince_Malchezzar
SD%Complete: 100
SDComment: 
SDCategory: Karazhan
EndScriptData */

#include "sc_creature.h"

#define SAY_AGGRO           "Madness has brought you here to me. I shall be your undoing!"
#define SOUND_AGGRO         9218
#define SAY_SUMMON1         "You face not Malchezaar alone, but the legions I command!"
#define SOUND_SUMMON1       9322
#define SAY_SUMMON2         "All realities, all dimensions are open to me!"
#define SOUND_SUMMON2       9224
#define SAY_PHASE2          "Simple fools! Time is the fire in which you'll burn!"
#define SOUND_PHASE2        9220
#define SAY_PHASE3          "How can you hope to withstand against such overwhelming power?"
#define SOUND_PHASE3        9321
#define SAY_PDEATH1         "You are, but a plaything, unfit even to amuse."
#define SOUND_PDEATH1       9319
#define SAY_PDEATH2         "Your greed, your foolishness has brought you to this end."
#define SOUND_PDEATH2       9318
#define SAY_PDEATH3         "Surely you did not think you could win."
#define SOUND_PDEATH3       9222
#define SAY_DEATH           "I refuse to concede defeat. I am a prince of the Eredar! I am..."
#define SOUND_DEATH         9221

// 19 Coordinates for Infernal spawns
struct InfernalPoint
{
    float x,y;
};

#define INFERNAL_Z  275.5

static InfernalPoint InfernalPoints[] =
{
    {-10922.8, -1985.2},
    {-10916.2, -1996.2},
    {-10932.2, -2008.1},
    {-10948.8, -2022.1},
    {-10958.7, -1997.7},
    {-10971.5, -1997.5},
    {-10990.8, -1995.1},
    {-10989.8, -1976.5},
    {-10971.6, -1973.0},
    {-10955.5, -1974.0},
    {-10939.6, -1969.8},
    {-10958.0, -1952.2},
    {-10941.7, -1954.8},
    {-10943.1, -1988.5},
    {-10948.8, -2005.1},
    {-10984.0, -2019.3},
    {-10932.8, -1979.6},
    {-10932.8, -1979.6},
    {-10935.7, -1996.0}
};

#define TOTAL_INFERNAL_POINTS 19

//Enfeeble is supposed to reduce hp to 1 and then heal player back to full when it ends
//Along with reducing healing and regen while enfeebled to 0%
//This spell effect will only reduce healing

//Enfeeble during phase 1 and 2
#define SPELL_ENFEEBLE          30843
#define SPELL_ENFEEBLE_EFFECT   41624

//Shadownova used during all phases
#define SPELL_SHADOWNOVA        30852

//Shadow word pain during phase 1 and 3 (different targeting rules though)
#define SPELL_SW_PAIN           30854

//Extra attack chance during phase 2
#define SPELL_THRASH_PASSIVE    12787

//Sunder armor during phase 2
#define SPELL_SUNDER_ARMOR      30901

//Passive proc chance for thrash
#define SPELL_THRASH_AURA       3417

//Visual for axe equiping
#define SPELL_EQUIP_AXES        30857

//Amplifiy during phase 3
#define SPELL_AMPLIFY_DAMAGE    12738 
//Infenals' hellfire aura
#define SPELL_HELLFIRE          30859

//The netherspite infernal creature
#define NETHERSPITE_INFERNAL    17646

//Malchezar's axes (creatures), summoned during phase 3
#define MALCHEZARS_AXE          17650

//Infernal Effects
#define INFERNAL_MODEL_INVISIBLE 11686
#define SPELL_INFERNAL_RELAY     30834

//Axes info
#define AXE_EQUIP_MODEL          40066
#define AXE_EQUIP_INFO           33448898



//---------Infernal code first
struct MANGOS_DLL_DECL netherspite_infernalAI : public ScriptedAI
{
    netherspite_infernalAI(Creature *c) : ScriptedAI(c) ,
        malchezaar(0), HellfireTimer(0), CleanupTimer(0), point(NULL) {Reset();}

    uint32 HellfireTimer;
    uint32 CleanupTimer;
    uint32 malchezaar;
    InfernalPoint *point;

    void Reset() {}
    void Aggro(Unit *who) {}
    void MoveInLineOfSight(Unit *who) {}

    void UpdateAI(const uint32 diff)
    {
        if(HellfireTimer)
            if(HellfireTimer <= diff)
            {
                DoCast(m_creature, SPELL_HELLFIRE);
                HellfireTimer = 0;
            }
            else HellfireTimer -= diff;

        if(CleanupTimer)
            if(CleanupTimer <= diff)
            {
                Cleanup();
                CleanupTimer = 0;
            } else CleanupTimer -= diff;
    }

    void KilledUnit(Unit *who)
    {
        Unit *pMalchezaar = Unit::GetUnit(*m_creature, malchezaar);
        if(pMalchezaar)
            ((Creature*)pMalchezaar)->AI()->KilledUnit(who);
    }

    void SpellHit(Unit *who, const SpellEntry *spell)
    {
        if(spell->Id == SPELL_INFERNAL_RELAY)
        {
            m_creature->SetUInt32Value(UNIT_FIELD_DISPLAYID, m_creature->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            HellfireTimer = 4000;
            CleanupTimer = 170000;
        }
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if(done_by->GetGUID() != malchezaar)
            damage = 0;
    }

    void Cleanup(); //below ...
};


CreatureAI* GetAI_netherspite_infernal(Creature *_Creature)
{
    return new netherspite_infernalAI (_Creature);
}

void AddSC_netherspite_infernal()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="netherspite_infernal";
    newscript->GetAI = GetAI_netherspite_infernal;

    m_scripts[nrscripts++] = newscript;
}

struct MANGOS_DLL_DECL boss_malchezaarAI : public ScriptedAI
{
    boss_malchezaarAI(Creature *c) : ScriptedAI(c) {Reset();}

    uint32 EnfeebleTimer;
    uint32 EnfeebleResetTimer;
    uint32 ShadowNovaTimer;
    uint32 SWPainTimer;
    uint32 SunderArmorTimer;
    uint32 AmplifyDamageTimer;
    uint32 InfernalTimer;
    uint32 AxesTargetSwitchTimer;
    uint32 InfernalCleanupTimer;

    std::vector<uint64> infernals;
    std::vector<InfernalPoint*> positions;
    
    uint64 axes[2];
    uint64 enfeeble_targets[5];
    uint64 enfeeble_health[5];
    
    uint32 phase;

    void Reset()
    {
        AxesCleanup();
        ClearWeapons();
        InfernalCleanup();
        positions.clear();

        for(int i =0; i < 5; ++i)
            enfeeble_targets[i] = 0;

        for(int i = 0; i < TOTAL_INFERNAL_POINTS; ++i)
            positions.push_back(&InfernalPoints[i]);

        EnfeebleTimer = 30000;
        EnfeebleResetTimer = 38000;
        ShadowNovaTimer = 35000;
        SWPainTimer = 20000;
        AmplifyDamageTimer = 10000;
        InfernalTimer = 45000;
        InfernalCleanupTimer = 47000;
        AxesTargetSwitchTimer = 7500 + rand()%12500;
        phase = 1;
    }

    void KilledUnit(Unit *victim)
    {
        switch(rand()%3)
        {
        case 0:
            DoYell(SAY_PDEATH1, LANG_UNIVERSAL, NULL);
            DoPlaySoundToSet(victim, SOUND_PDEATH1);
            break;
        case 1:
            DoYell(SAY_PDEATH2, LANG_UNIVERSAL, NULL);
            DoPlaySoundToSet(victim, SOUND_PDEATH2);
            break;
        case 2:
            DoYell(SAY_PDEATH3, LANG_UNIVERSAL, NULL);
            DoPlaySoundToSet(victim, SOUND_PDEATH3);
            break;
        }
    }

    void JustDied(Unit *victim)
    {
        DoYell(SAY_DEATH, LANG_UNIVERSAL, NULL);
        DoPlaySoundToSet(m_creature, SOUND_DEATH);

        AxesCleanup();
        ClearWeapons();
        InfernalCleanup();
        positions.clear();

        for(int i = 0; i < TOTAL_INFERNAL_POINTS; ++i)
            positions.push_back(&InfernalPoints[i]);

    }

    void Aggro(Unit *who)
    {        
                DoYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
                DoPlaySoundToSet(m_creature, SOUND_AGGRO);
    }


    void InfernalCleanup()
    {
         //Infernal Cleanup
        for(std::vector<uint64>::iterator itr = infernals.begin(); itr!= infernals.end(); ++itr)
        {
            Unit *pInfernal = Unit::GetUnit(*m_creature, *itr);
            if(pInfernal && pInfernal->isAlive())
            {
                pInfernal->SetVisibility(VISIBILITY_OFF);
                pInfernal->DealDamage(pInfernal, pInfernal->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_NORMAL, NULL, false);
            }
        }
        infernals.clear();
    }

    void AxesCleanup()
    {
        for(int i=0; i<2;++i)
        {
            Unit *axe = Unit::GetUnit(*m_creature, axes[i]);
            if(axe && axe->isAlive())
                axe->DealDamage(axe, axe->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_NORMAL, NULL, false);
            axes[i] = 0;
        }
    }
            
    void ClearWeapons()
    {
        m_creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 0);
        m_creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO, 0);

        m_creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 0);
        m_creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+2, 0);

        //damage
        const CreatureInfo *cinfo = m_creature->GetCreatureInfo();
        m_creature->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, cinfo->mindmg);
        m_creature->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, cinfo->maxdmg);
        m_creature->UpdateDamagePhysical(BASE_ATTACK);
    }

    void EnfeebleHealthEffect()
    {
        const SpellEntry *info = GetSpellStore()->LookupEntry(SPELL_ENFEEBLE_EFFECT);
        if(!info)
            return;

        std::list<HostilReference *> t_list = m_creature->getThreatManager().getThreatList();
        std::vector<Unit *> targets;

        if(!t_list.size())
            return;

        //begin + 1 , so we don't target the one with the highest threat
        std::list<HostilReference *>::iterator itr = t_list.begin();
        std::advance(itr, 1);
        for( ; itr!= t_list.end(); ++itr) //store the threat list in a different container
        {
            Unit *target = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid());
            if(target && target->isAlive() && target->GetTypeId() == TYPEID_PLAYER ) //only on alive players
                targets.push_back( target);
        }
        
        while(targets.size() > 5)
            targets.erase(targets.begin()+rand()%targets.size()); //cut down to size if we have more than 5 targets

        int i = 0;
        for(std::vector<Unit *>::iterator itr = targets.begin(); itr!= targets.end(); ++itr, ++i)
        {
            Unit *target = *itr;
            if(target)
            {
                enfeeble_targets[i] = target->GetGUID();
                enfeeble_health[i] = target->GetHealth();

               // target->CastSpell(target, SPELL_ENFEEBLE, true, 0, 0, m_creature->GetGUID());
                target->SetHealth(1);
            }
        }

    }

    void EnfeebleResetHealth()
    {
        for(int i = 0; i < 5; ++i)
        {
            Unit *target = Unit::GetUnit(*m_creature, enfeeble_targets[i]);
            if(target && target->isAlive())
                target->SetHealth(enfeeble_health[i]);
            enfeeble_targets[i] = 0;
            enfeeble_health[i] = 0;
        }
    }

    void SummonInfernal(const uint32 diff)
    {
        InfernalPoint *point = NULL;
        float posX,posY,posZ;
        if( (m_creature->GetMapId() != 532) || positions.empty())
        {
            m_creature->GetRandomPoint(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 60, posX, posY, posZ);
        }
        else
        {
            std::vector<InfernalPoint*>::iterator itr = positions.begin()+rand()%positions.size();
            point = *itr;
            positions.erase(itr);

            posX = point->x;
            posY = point->y;
            posZ = INFERNAL_Z;
        }

        
        Creature *Infernal = m_creature->SummonCreature(NETHERSPITE_INFERNAL, posX, posY, posZ, 0, TEMPSUMMON_TIMED_DESPAWN, 180000);

        if (Infernal)
        {
            Infernal->SetUInt32Value(UNIT_FIELD_DISPLAYID, INFERNAL_MODEL_INVISIBLE);
            Infernal->setFaction(m_creature->getFaction());
            if(point)
                ((netherspite_infernalAI*)Infernal->AI())->point=point;
            ((netherspite_infernalAI*)Infernal->AI())->malchezaar=m_creature->GetGUID();

            infernals.push_back(Infernal->GetGUID());
            DoCast(Infernal, SPELL_INFERNAL_RELAY);
        }

        switch(rand()%2)
        {
        case 0:
            DoYell(SAY_SUMMON1, LANG_UNIVERSAL, NULL);
            DoPlaySoundToSet(m_creature, SOUND_SUMMON1);
            break;
        case 1:
            DoYell(SAY_SUMMON2, LANG_UNIVERSAL, NULL);
            DoPlaySoundToSet(m_creature, SOUND_SUMMON2);
            break;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim() )
            return;

        if(EnfeebleResetTimer)
            if(EnfeebleResetTimer <= diff) //Let's not forget to reset that
            {
                EnfeebleResetHealth();
                EnfeebleResetTimer=0;
            }else EnfeebleResetTimer -= diff;

        if(m_creature->hasUnitState(UNIT_STAT_STUNDED)) //While shifting to phase 2 malchezaar stuns himself
            return; 

        if(m_creature->GetUInt64Value(UNIT_FIELD_TARGET)!=m_creature->getVictim()->GetGUID())
            m_creature->SetUInt64Value(UNIT_FIELD_TARGET, m_creature->getVictim()->GetGUID());

        if(phase == 1)
        {
            if( (m_creature->GetHealth()*100) / m_creature->GetMaxHealth() < 60)
            {
                m_creature->InterruptNonMeleeSpells(false);

                phase = 2;

                //animation
                DoCast(m_creature, SPELL_EQUIP_AXES);
            
                //text
                DoYell(SAY_PHASE2, LANG_UNIVERSAL, NULL);
                DoPlaySoundToSet(m_creature, SOUND_PHASE2);

                //passive thrash aura
                m_creature->CastSpell(m_creature, SPELL_THRASH_AURA, true);
            
                //models
                m_creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, AXE_EQUIP_MODEL);
                m_creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO, AXE_EQUIP_INFO);

                m_creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, AXE_EQUIP_MODEL);
                m_creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+2, AXE_EQUIP_INFO);

                //damage
                const CreatureInfo *cinfo = m_creature->GetCreatureInfo();
                m_creature->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, 2*cinfo->mindmg);
                m_creature->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, 2*cinfo->maxdmg);
                m_creature->UpdateDamagePhysical(BASE_ATTACK);
                
                m_creature->SetBaseWeaponDamage(OFF_ATTACK, MINDAMAGE, cinfo->mindmg);
                m_creature->SetBaseWeaponDamage(OFF_ATTACK, MAXDAMAGE, cinfo->maxdmg);
                //Sigh, updating only works on main attack , do it manually ....
                m_creature->SetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE, cinfo->mindmg);
                m_creature->SetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE, cinfo->maxdmg);

                m_creature->SetAttackTime(OFF_ATTACK, (uint32)m_creature->GetAttackTime(BASE_ATTACK)/1.5);
                
            }

        }
        else if(phase == 2)
        {
            if( (m_creature->GetHealth()*100) / m_creature->GetMaxHealth() < 30)
            {
                InfernalTimer = 15000;
                
                phase = 3;

                ClearWeapons();

                //remove thrash
                m_creature->RemoveAurasDueToSpell(SPELL_THRASH_AURA);
                
                DoYell(SAY_PHASE3, LANG_UNIVERSAL, NULL);
                DoPlaySoundToSet(m_creature, SOUND_PHASE3);

                Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0);
                for(uint32 i=0; i<2; ++i)
                {
                    Creature *axe = m_creature->SummonCreature(MALCHEZARS_AXE, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
                    if(axe)
                    {
                        axe->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, AXE_EQUIP_MODEL);
                        axe->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO, AXE_EQUIP_INFO);

                        axe->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        axe->setFaction(m_creature->getFaction());
                        axes[i] = axe->GetGUID();
                        axe->AI()->AttackStart(target);
                        // axe->getThreatManager().tauntApply(target); //Taunt Apply and fade out does not work properly
                        axe->AddThreat(target, 10000000.0f); // So we'll use a hack to add a lot of threat to our target
                    }
                }

                if(ShadowNovaTimer > 35000)
                    ShadowNovaTimer = EnfeebleTimer + 5000;

                return;

            }
           
            if(SunderArmorTimer < diff)
            {
                DoCast(m_creature->getVictim(), SPELL_SUNDER_ARMOR);
                SunderArmorTimer = 15000;
                
            }else SunderArmorTimer -= diff;

        }
        else
        {

            if(AxesTargetSwitchTimer < diff)
            {
                AxesTargetSwitchTimer = 7500 + rand()%12500 ;

                Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0);
                if(target)
                {
                    for(int i = 0; i < 2; ++i)
                    {
                        Unit *axe = Unit::GetUnit(*m_creature, axes[i]);
                        if(axe)
                        {
                            float threat = axe->getThreatManager().getThreat(axe->getVictim());
                            axe->getThreatManager().modifyThreatPercent(axe->getVictim(), -100);
                            axe->AddThreat(target, threat);
                            //axe->getThreatManager().tauntFadeOut(axe->getVictim());
                            //axe->getThreatManager().tauntApply(target);
                        }
                    }
                }
            } else AxesTargetSwitchTimer -= diff;
        
            
            if(AmplifyDamageTimer < diff)
            {
                DoCast(SelectUnit(SELECT_TARGET_RANDOM, 0), SPELL_AMPLIFY_DAMAGE);
                AmplifyDamageTimer = 20000 + rand()%10000;                
            }else AmplifyDamageTimer -= diff;

        }


        //Time for global and double timers
        if(InfernalTimer < diff)
        {
            SummonInfernal(diff);
            InfernalTimer =  phase == 3 ? 15000 : 45000; //15 secs in phase 3, 45 otherwise
        }else InfernalTimer -= diff;

        if(ShadowNovaTimer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_SHADOWNOVA);
            ShadowNovaTimer = phase == 3 ? 35000 : -1;
        }else ShadowNovaTimer -= diff;

        if(phase != 2)
        {
            if(SWPainTimer < diff)
            {
                Unit *target;
                if(phase == 1)
                    target = m_creature->getVictim(); // the tank
                else
                    target = SelectUnit(SELECT_TARGET_RANDOM, 1); //anyone but the tank

                DoCast(target, SPELL_SW_PAIN);
                SWPainTimer = 20000;
                
            }else SWPainTimer -= diff;

        }

        if(phase != 3)
        {   
            if(EnfeebleTimer < diff)
            {
                EnfeebleHealthEffect();
                EnfeebleTimer = 30000;
                ShadowNovaTimer = 5000;
                EnfeebleResetTimer = 9000;
            }else EnfeebleTimer -= diff;
        }

        if(phase==2)
            DoMeleeAttacksIfReady();
        else
            DoMeleeAttackIfReady();
    }

    void DoMeleeAttacksIfReady()
    {
        if( m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE) && !m_creature->IsNonMeleeSpellCasted(false))
        {
            //Check for base attack
            if( m_creature->isAttackReady())
            {
                m_creature->AttackerStateUpdate(m_creature->getVictim());
                m_creature->resetAttackTimer();
            }
            //Check for offhand attack
            if( m_creature->isAttackReady(OFF_ATTACK))
            {
                m_creature->AttackerStateUpdate(m_creature->getVictim(), OFF_ATTACK);
                m_creature->resetAttackTimer(OFF_ATTACK);
            }
        }
    }

    void Cleanup(Creature *infernal, InfernalPoint *point)
    {
        for(std::vector<uint64>::iterator itr = infernals.begin(); itr!= infernals.end(); ++itr)
            if(*itr == infernal->GetGUID())
            {
                infernals.erase(itr);
                break;
            }

        positions.push_back(point);
    }

};

void netherspite_infernalAI::Cleanup()
{
    Unit *pMalchezaar = Unit::GetUnit(*m_creature, malchezaar);

    if(pMalchezaar && pMalchezaar->isAlive())
        ((boss_malchezaarAI*)((Creature*)pMalchezaar)->AI())->Cleanup(m_creature, point);
}

CreatureAI* GetAI_boss_malchezaar(Creature *_Creature)
{
    return new boss_malchezaarAI (_Creature);
}

void AddSC_boss_malchezaar()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="boss_malchezaar";
    newscript->GetAI = GetAI_boss_malchezaar;

    m_scripts[nrscripts++] = newscript;
}
