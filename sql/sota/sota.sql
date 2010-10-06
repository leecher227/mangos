-- --------------------------------------
-- Strand of the Ancients - battleground
-- --------------------------------------

-- ====================================== CREATURE
DELETE FROM `creature` WHERE `map` = '607' AND `id` BETWEEN '13012720' AND '13012744';
INSERT INTO `creature` (`guid` ,`id` ,`map` ,`spawnMask` ,`phaseMask` ,`modelid` ,`equipment_id` ,`position_x` ,`position_y` ,`position_z` ,`orientation` ,`spawntimesecs` ,`spawndist` ,`currentwaypoint` ,`curhealth` ,`curmana` ,`DeathState` ,`MovementType` )
VALUES 
-- Antipersonnel Cannon
(13012720, '27894', '607', '1', '1', '0', '0', '1436.429', '110.05', '41.407', '5.4', '120', '0', '0', '60000', '0', '0', '0'),
(13012721, '27894', '607', '1', '1', '0', '0', '1404.9023', '84.758', '41.183', '5.46', '120', '0', '0', '60000', '0', '0', '0'),
(13012722, '27894', '607', '1', '1', '0', '0', '1068.693', '-86.951', '93.81', '0.02', '120', '0', '0', '60000', '0', '0', '0'),
(13012723, '27894', '607', '1', '1', '0', '0', '1068.83', '-127.56', '96.45', '0.0912', '120', '0', '0', '60000', '0', '0', '0'),
(13012724, '27894', '607', '1', '1', '0', '0', '1422.115', '-196.433', '42.1825', '1.0222', '120', '0', '0', '60000', '0', '0', '0'),
(13012725, '27894', '607', '1', '1', '0', '0', '1454.887', '-220.454', '41.956', '0.9627', '120', '0', '0', '60000', '0', '0', '0'),
(13012726, '27894', '607', '1', '1', '0', '0', '1232.345', '-187.517', '66.945', '0.45', '120', '0', '0', '60000', '0', '0', '0'),
(13012727, '27894', '607', '1', '1', '0', '0', '1249.634', '-224.189', '66.72', '0.635', '120', '0', '0', '60000', '0', '0', '0'),
(13012728, '27894', '607', '1', '1', '0', '0', '1236.213', '92.287', '64.965', '5.751', '120', '0', '0', '60000', '0', '0', '0'),
(13012729, '27894', '607', '1', '1', '0', '0', '1215.11', '57.772', '64.739', '5.78', '120', '0', '0', '60000', '0', '0', '0'),
-- Battleground Demolisher
(13012730, '28781', '607', '1', '1', '0', '0', '1611.597656', '-117.270073', '8.719355', '2.513274', '120', '0', '0', '171600', '0', '0', '0'),
(13012731, '28781', '607', '1', '1', '0', '0', '1575.562500', '-158.421875', '5.024450', '2.129302', '120', '0', '0', '171600', '0', '0', '0'),
(13012732, '28781', '607', '1', '1', '0', '0', '1618.047729', '61.424641', '7.248210', '3.979351', '120', '0', '0', '171600', '0', '0', '0'),
(13012733, '28781', '607', '1', '1', '0', '0', '1575.103149', '98.873344', '2.830360', '3.752458', '120', '0', '0', '171600', '0', '0', '0'),
(13012734, '28781', '607', '1', '1', '0', '0', '1371.055786', '-317.071136', '35.007359', '1.947460', '120', '0', '0', '171600', '0', '0', '0'),
(13012735, '28781', '607', '1', '1', '0', '0', '1424.034912', '-260.195190', '31.084425', '2.820013', '120', '0', '0', '171600', '0', '0', '0'),
(13012736, '28781', '607', '1', '1', '0', '0', '1353.139893', '223.745438', '35.265411', '4.343684', '120', '0', '0', '171600', '0', '0', '0'),
(13012737, '28781', '607', '1', '1', '0', '0', '1404.809570', '197.027237', '32.046032', '3.605401', '120', '0', '0', '171600', '0', '0', '0'),
-- World Trigger
(13012738, '23472', '607', '1', '1', '0', '0', '1453.49', '-250.453', '30.896', '4.2883', '120', '0', '0', '1', '0', '0', '0'),
(13012739, '23472', '607', '1', '1', '0', '0', '1377.05', '97.036', '30.8605', '2.46539', '120', '0', '0', '1', '0', '0', '0'),
(13012740, '23472', '607', '1', '1', '0', '0', '1186.05', '58.8048', '56.5491', '2.75992', '120', '0', '0', '1', '0', '0', '0'),
(13012741, '23472', '607', '1', '1', '0', '0', '1042.83', '-72.839', '84.8145', '3.58615', '120', '0', '0', '1', '0', '0', '0'),
(13012742, '23472', '607', '1', '1', '0', '0', '1233.62', '-250.49', '55.4036', '3.7016', '120', '0', '0', '1', '0', '0', '0'),
-- Rigger Sparklight 
(13012743, '29260', '607', '1', '1', '0', '0', '1348.644165', '-298.786469', '31.080130', '1.710423', '120', '0', '0', '6986', '0', '0', '0'),
-- Gorgril Rigspark
(13012744, '29262', '607', '1', '1', '0', '0', '1358.191040', '195.527786', '31.018187', '4.171337', '120', '0', '0', '6986', '0', '0', '0');

UPDATE `creature` SET `spawnMask` = 15 WHERE `guid`  BETWEEN '13012720' AND '13012744';

-- ====================================== GOBJECT
DELETE FROM `gameobject` WHERE `map` = '607' AND `guid`  BETWEEN '797659' AND '797755';
INSERT INTO `gameobject` (`guid` ,`id` ,`map` ,`spawnMask` ,`phaseMask` ,`position_x` ,`position_y` ,`position_z` ,`orientation` ,`rotation0` ,`rotation1` ,`rotation2` ,`rotation3` ,`spawntimesecs` ,`animprogress` ,`state` )
VALUES 
-- Doors
(797659, '190722', '607', '15', '1', '1411.57', '108.163', '28.692', '5.441', '0', '0', '0', '0', '120', '100', '1'),
(797660, '190727', '607', '15', '1', '1055.452', '-108.1', '82.134', '0.034', '0', '0', '0', '0', '120', '100', '1'),
(797661, '190724', '607', '15', '1', '1431.3413', '-219.437', '30.893', '0.9736', '0', '0', '0', '0', '120', '100', '1'),
(797663, '190726', '607', '15', '1', '1227.667', '-212.555', '55.372', '0.5023', '0', '0', '0', '0', '120', '100', '1'),
(797664, '190723', '607', '15', '1', '1214.681', '81.21', '53.413', '5.745', '0', '0', '0', '0', '120', '100', '1'),
(797665, '192549', '607', '15', '1', '878.555', '-108.2', '117.845', '0.0', '0', '0', '0', '0', '120', '100', '1'),
(797666, '192834', '607', '15', '1', '836.5', '-108.8', '120.219', '0.0', '0', '0', '0', '0', '120', '100', '1'),
-- Ships
(797749, '193182', '607', '15', '1', '2679.696777', '-826.891235', '3.712860', '5.78367', '0', '0', '0', '0', '120', '100', '1'),
(797750, '193185', '607', '15', '1', '2574.003662', '981.261475', '2.603424', '0.807696', '0', '0', '0', '0', '120', '100', '1'),
-- Moon Sigil
(797751, '192687', '607', '15', '1', '1414.054', '106.72', '41.442', '5.441', '0', '0', '0', '0', '120', '100', '1'),
(797752, '192685', '607', '15', '1', '1060.63', '-107.8', '94.7', '0.034', '0', '0', '0', '0', '120', '100', '1'),
(797753, '192689', '607', '15', '1', '1433.383', '-216.4', '43.642', '0.9736', '0', '0', '0', '0', '120', '100', '1'),
(797754, '192690', '607', '15', '1', '1230.75', '-210.724', '67.611', '0.5023', '0', '0', '0', '0', '120', '100', '1'),
(797755, '192691', '607', '15', '1', '1217.8', '79.532', '66.58', '5.745', '0', '0', '0', '0', '120', '100', '1'),
-- Flagpole
(797670, '191311', '607', '15', '1', '1215.114258', '-65.711861', '70.084267', '-3.124123', '0', '0', '0', '0', '120', '100', '1'),
(797671, '191311', '607', '15', '1', '1338.863892', '-153.336533', '30.895121', '-2.530723', '0', '0', '0', '0', '120', '100', '1'),
(797672, '191311', '607', '15', '1', '1309.124268', '9.410645', '30.893402', '-1.623156', '0', '0', '0', '0', '120', '100', '1'),
-- Flags
(797673, '191310', '607', '15', '1', '1215.108032', '-65.715767', '70.084267', '-3.124123', '0', '0', '0', '0', '120', '100', '1'),
(797674, '191306', '607', '15', '1', '1338.859253', '-153.327316', '30.895077', '-2.530723', '0', '0', '0', '0', '120', '100', '1'),
(797675, '191308', '607', '15', '1', '1309.192017', '9.416233', '30.893402', '1.518436', '0', '0', '0', '0', '120', '100', '1'),
-- Portal
(797676, '192819', '607', '15', '1', '1468.380005', '-225.798996', '30.896200', '0.0', '0', '0', '0', '0', '120', '100', '1'),
(797677, '192819', '607', '15', '1', '1394.270020', '72.551399', '31.054300', '0.0', '0', '0', '0', '0', '120', '100', '1'),
(797678, '192819', '607', '15', '1', '1065.260010', '-89.79501', '81.073402', '0.0', '0', '0', '0', '0', '120', '100', '1'),
(797679, '192819', '607', '15', '1', '1216.069946', '47.904301', '54.278198', '0.0', '0', '0', '0', '0', '120', '100', '1'),
(797680, '192819', '607', '15', '1', '1255.569946', '-233.548996', '56.43699', '0.0', '0', '0', '0', '0', '120', '100', '1'),
-- Bombs
(797681, '190753', '607', '15', '1', '1333.45f', '211.354f', '31.0538f', '5.03666f', '0', '0', '0', '0', '120', '100', '1'),
(797682, '190753', '607', '15', '1', '1334.29f', '209.582f', '31.0532f', '1.28088f', '0', '0', '0', '0', '120', '100', '1'),
(797683, '190753', '607', '15', '1', '1332.72f', '210.049f', '31.0532f', '1.28088f', '0', '0', '0', '0', '120', '100', '1'),
(797684, '190753', '607', '15', '1', '1334.28f', '210.78f', '31.0538f', '3.85856f', '0', '0', '0', '0', '120', '100', '1'),
(797685, '190753', '607', '15', '1', '1332.64f', '211.39f', '31.0532f', '1.29266f', '0', '0', '0', '0', '120', '100', '1'),
(797686, '190753', '607', '15', '1', '1371.41f', '194.028f', '31.5107f', '0.753095f', '0', '0', '0', '0', '120', '100', '1'),
(797687, '190753', '607', '15', '1', '1372.39f', '194.951f', '31.4679f', '0.753095f', '0', '0', '0', '0', '120', '100', '1'),
(797688, '190753', '607', '15', '1', '1371.58f', '196.942f', '30.9349f', '1.01777f', '0', '0', '0', '0', '120', '100', '1'),
(797689, '190753', '607', '15', '1', '1370.43f', '196.614f', '30.9349f', '0.957299f', '0', '0', '0', '0', '120', '100', '1'),
(797690, '190753', '607', '15', '1', '1369.46f', '196.877f', '30.9351f', '2.45348f', '0', '0', '0', '0', '120', '100', '1'),
(797691, '190753', '607', '15', '1', '1370.35f', '197.361f', '30.9349f', '1.08689f', '0', '0', '0', '0', '120', '100', '1'),
(797692, '190753', '607', '15', '1', '1369.47f', '197.941f', '30.9349f', '0.984787f', '0', '0', '0', '0', '120', '100', '1'),
(797693, '190753', '607', '15', '1', '1592.49f', '47.5969f', '7.52271f', '4.63218f', '0', '0', '0', '0', '120', '100', '1'),
(797694, '190753', '607', '15', '1', '1593.91f', '47.8036f', '7.65856f', '4.63218f', '0', '0', '0', '0', '120', '100', '1'),
(797695, '190753', '607', '15', '1', '1593.13f', '46.8106f', '7.54073f', '4.63218f', '0', '0', '0', '0', '120', '100', '1'),
(797696, '190753', '607', '15', '1', '1589.22f', '36.3616f', '7.45975f', '4.64396f', '0', '0', '0', '0', '120', '100', '1'),
(797697, '190753', '607', '15', '1', '1588.24f', '35.5842f', '7.55613f', '4.79564f', '0', '0', '0', '0', '120', '100', '1'),
(797698, '190753', '607', '15', '1', '1588.14f', '36.7611f', '7.49675f', '4.79564f', '0', '0', '0', '0', '120', '100', '1'),
(797699, '190753', '607', '15', '1', '1595.74f', '35.5278f', '7.46602f', '4.90246f', '0', '0', '0', '0', '120', '100', '1'),
(797700, '190753', '607', '15', '1', '1596', '36.6475f', '7.47991f', '4.90246f', '0', '0', '0', '0', '120', '100', '1'),
(797701, '190753', '607', '15', '1', '1597.03f', '36.2356f', '7.48631f', '4.90246f', '0', '0', '0', '0', '120', '100', '1'),
(797702, '190753', '607', '15', '1', '1597.93f', '37.1214f', '7.51725f', '4.90246f', '0', '0', '0', '0', '120', '100', '1'),
(797703, '190753', '607', '15', '1', '1598.16f', '35.888f', '7.50018f', '4.90246f', '0', '0', '0', '0', '120', '100', '1'),
(797704, '190753', '607', '15', '1', '1579.6f', '-98.0917f', '8.48478f', '1.37996f', '0', '0', '0', '0', '120', '100', '1'),
(797705, '190753', '607', '15', '1', '1581.2f', '-98.401f', '8.47483f', '1.37996f', '0', '0', '0', '0', '120', '100', '1'),
(797706, '190753', '607', '15', '1', '1580.38f', '-98.9556f', '8.4772f', '1.38781f', '0', '0', '0', '0', '120', '100', '1'),
(797707, '190753', '607', '15', '1', '1585.68f', '-104.966f', '8.88551f', '0.493246f', '0', '0', '0', '0', '120', '100', '1'),
(797708, '190753', '607', '15', '1', '1586.15f', '-106.033f', '9.10616f', '0.493246f', '0', '0', '0', '0', '120', '100', '1'),
(797709, '190753', '607', '15', '1', '1584.88f', '-105.394f', '8.82985f', '0.493246f', '0', '0', '0', '0', '120', '100', '1'),
(797710, '190753', '607', '15', '1', '1581.87f', '-100.899f', '8.46164f', '0.929142f', '0', '0', '0', '0', '120', '100', '1'),
(797711, '190753', '607', '15', '1', '1581.48f', '-99.4657f', '8.46926f', '0.929142f', '0', '0', '0', '0', '120', '100', '1'),
(797712, '190753', '607', '15', '1', '1583.2f', '-91.2291f', '8.49227f', '1.40038f', '0', '0', '0', '0', '120', '100', '1'),
(797713, '190753', '607', '15', '1', '1581.94f', '-91.0119f', '8.49977f', '1.40038f', '0', '0', '0', '0', '120', '100', '1'),
(797714, '190753', '607', '15', '1', '1582.33f', '-91.951f', '8.49353f', '1.1844f', '0', '0', '0', '0', '120', '100', '1'),
(797715, '190753', '607', '15', '1', '1342.06f', '-304.049f', '30.9532f', '5.59507f', '0', '0', '0', '0', '120', '100', '1'),
(797716, '190753', '607', '15', '1', '1340.96f', '-304.536f', '30.9458f', '1.28323f', '0', '0', '0', '0', '120', '100', '1'),
(797717, '190753', '607', '15', '1', '1341.22f', '-303.316f', '30.9413f', '0.486051f', '0', '0', '0', '0', '120', '100', '1'),
(797718, '190753', '607', '15', '1', '1342.22f', '-302.939f', '30.986f', '4.87643f', '0', '0', '0', '0', '120', '100', '1'),
(797719, '190753', '607', '15', '1', '1382.16f', '-287.466f', '32.3063f', '4.80968f', '0', '0', '0', '0', '120', '100', '1'),
(797720, '190753', '607', '15', '1', '1381', '-287.58f', '32.2805f', '4.80968f', '0', '0', '0', '0', '120', '100', '1'),
(797721, '190753', '607', '15', '1', '1381.55f', '-286.536f', '32.3929f', '2.84225f', '0', '0', '0', '0', '120', '100', '1'),
(797722, '190753', '607', '15', '1', '1382.75f', '-286.354f', '32.4099f', '1.00442f', '0', '0', '0', '0', '120', '100', '1'),
(797723, '190753', '607', '15', '1', '1379.92f', '-287.34f', '32.2872f', '3.81615f', '0', '0', '0', '0', '120', '100', '1'),
(797724, '190753', '607', '15', '1', '1100.52f', '-2.41391f', '70.2984f', '0.131054f', '0', '0', '0', '0', '120', '100', '1'),
(797725, '190753', '607', '15', '1', '1099.35f', '-2.13851f', '70.3375f', '4.4586f', '0', '0', '0', '0', '120', '100', '1'),
(797726, '190753', '607', '15', '1', '1099.59f', '-1.00329f', '70.238f', '2.49903f', '0', '0', '0', '0', '120', '100', '1'),
(797727, '190753', '607', '15', '1', '1097.79f', '0.571316f', '70.159f', '4.00307f', '0', '0', '0', '0', '120', '100', '1'),
(797728, '190753', '607', '15', '1', '1098.74f', '-7.23252f', '70.7972f', '4.1523f', '0', '0', '0', '0', '120', '100', '1'),
(797729, '190753', '607', '15', '1', '1098.46f', '-5.91443f', '70.6715f', '4.1523f', '0', '0', '0', '0', '120', '100', '1'),
(797730, '190753', '607', '15', '1', '1097.53f', '-7.39704f', '70.7959f', '4.1523f', '0', '0', '0', '0', '120', '100', '1'),
(797731, '190753', '607', '15', '1', '1097.32f', '-6.64233f', '70.7424f', '4.1523f', '0', '0', '0', '0', '120', '100', '1'),
(797732, '190753', '607', '15', '1', '1096.45f', '-5.96664f', '70.7242f', '4.1523f', '0', '0', '0', '0', '120', '100', '1'),
(797733, '190753', '607', '15', '1', '971.725f', '0.496763f', '86.8467f', '2.09233f', '0', '0', '0', '0', '120', '100', '1'),
(797734, '190753', '607', '15', '1', '973.589f', '0.119518f', '86.7985f', '3.17225f', '0', '0', '0', '0', '120', '100', '1'),
(797735, '190753', '607', '15', '1', '972.524f', '1.25333f', '86.8351f', '5.28497f', '0', '0', '0', '0', '120', '100', '1'),
(797736, '190753', '607', '15', '1', '971.993f', '2.05668f', '86.8584f', '5.28497f', '0', '0', '0', '0', '120', '100', '1'),
(797737, '190753', '607', '15', '1', '973.635f', '2.11805f', '86.8197f', '2.36722f', '0', '0', '0', '0', '120', '100', '1'),
(797738, '190753', '607', '15', '1', '974.791f', '1.74679f', '86.7942f', '1.5936f', '0', '0', '0', '0', '120', '100', '1'),
(797739, '190753', '607', '15', '1', '974.771f', '3.0445f', '86.8125f', '0.647199f', '0', '0', '0', '0', '120', '100', '1'),
(797740, '190753', '607', '15', '1', '979.554f', '3.6037f', '86.7923f', '1.69178f', '0', '0', '0', '0', '120', '100', '1'),
(797741, '190753', '607', '15', '1', '979.758f', '2.57519f', '86.7748f', '1.76639f', '0', '0', '0', '0', '120', '100', '1'),
(797742, '190753', '607', '15', '1', '980.769f', '3.48904f', '86.7939f', '1.76639f', '0', '0', '0', '0', '120', '100', '1'),
(797743, '190753', '607', '15', '1', '979.122f', '2.87109f', '86.7794f', '1.76639f', '0', '0', '0', '0', '120', '100', '1'),
(797744, '190753', '607', '15', '1', '986.167f', '4.85363f', '86.8439f', '1.5779f', '0', '0', '0', '0', '120', '100', '1'),
(797745, '190753', '607', '15', '1', '986.176f', '3.50367f', '86.8217f', '1.5779f', '0', '0', '0', '0', '120', '100', '1'),
(797746, '190753', '607', '15', '1', '987.33f', '4.67389f', '86.8486f', '1.5779f', '0', '0', '0', '0', '120', '100', '1'),
(797747, '190753', '607', '15', '1', '985.23f', '4.65898f', '86.8368f', '1.5779f', '0', '0', '0', '0', '120', '100', '1'),
(797748, '190753', '607', '15', '1', '984.556f', '3.54097f', '86.8137f', '1.5779f', '0', '0', '0', '0', '120', '100', '1');

UPDATE `gameobject` SET `spawnMask` = 15 WHERE `guid` BETWEEN '797659' AND '797755';
