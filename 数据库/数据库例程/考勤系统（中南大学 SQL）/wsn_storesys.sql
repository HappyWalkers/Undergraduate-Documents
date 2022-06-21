/*
Navicat MySQL Data Transfer
Source Host     : 172.20.223.151:3306
Source Database : wsn_storesys
Target Host     : 172.20.223.151:3306
Target Database : wsn_storesys
Date: 2013-03-26 13:53:25
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for errorItem
-- ----------------------------
DROP TABLE IF EXISTS `errorItem`;
CREATE TABLE `errorItem` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `errorstatus` varchar(255) NOT NULL,
  `commodityName` int(11) NOT NULL,
  `commodityId` varchar(255) NOT NULL,
  `operatorId` int(11) NOT NULL,
  `operateTime` datetime NOT NULL,
  `commodityStatus` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=109 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of errorItem
-- ----------------------------
INSERT INTO `errorItem` VALUES ('1', '入库', '2', '1', '1', '2013-02-28 20:07:17', '2');
INSERT INTO `errorItem` VALUES ('2', '入库', '1', '1', '1', '2013-02-28 20:08:03', '2');
INSERT INTO `errorItem` VALUES ('3', '出库', '2', '1', '1', '0000-00-00 00:00:00', '2');
INSERT INTO `errorItem` VALUES ('4', '出库', '2', '1', '1', '2013-03-02 00:00:00', '3');
INSERT INTO `errorItem` VALUES ('5', '其他', '1', 'abc', '0', '2013-03-05 10:11:03', '3');
INSERT INTO `errorItem` VALUES ('6', '其他', '2', 'e2001071290e02200920bac0', '0', '2013-03-05 11:00:47', '2');
INSERT INTO `errorItem` VALUES ('7', '其他', '2', 'e20010187413016023901f55', '1', '2013-03-05 12:15:11', '2');
INSERT INTO `errorItem` VALUES ('8', '其他', '2', 'e20010187413016023901f55', '1', '2013-03-07 12:17:05', '2');
INSERT INTO `errorItem` VALUES ('24', '出库', '0', 'e20010018303022111300009', '1', '2013-03-14 11:58:52', '2');
INSERT INTO `errorItem` VALUES ('25', '出库', '2', 'e20010018303022111300009', '1', '2013-03-14 11:59:43', '2');
INSERT INTO `errorItem` VALUES ('26', 'ÆäËû', '0', '000000000000000000000000', '0', '2013-03-14 18:08:58', '3');
INSERT INTO `errorItem` VALUES ('27', 'ÆäËû', '0', '000000000000000000000000', '0', '2013-03-14 18:09:09', '3');
INSERT INTO `errorItem` VALUES ('28', 'ÆäËû', '0', '000000000000000000000000', '0', '2013-03-14 18:09:24', '3');
INSERT INTO `errorItem` VALUES ('29', 'ÆäËû', '0', '000000000000000000000000', '0', '2013-03-14 18:09:58', '3');
INSERT INTO `errorItem` VALUES ('30', 'ÆäËû', '0', '000000000000000000000000', '0', '2013-03-14 18:10:08', '3');
INSERT INTO `errorItem` VALUES ('31', 'ÆäËû', '0', '000000000000000000000000', '0', '2013-03-14 18:10:20', '3');
INSERT INTO `errorItem` VALUES ('32', 'ÆäËû', '0', '000000000000000000000000', '0', '2013-03-14 18:10:25', '3');
INSERT INTO `errorItem` VALUES ('33', 'ÆäËû', '0', '000000000000000000000000', '0', '2013-03-14 18:42:15', '3');
INSERT INTO `errorItem` VALUES ('34', 'ÆäËû', '0', '000000000000000000000000', '0', '2013-03-14 18:42:18', '3');
INSERT INTO `errorItem` VALUES ('35', 'ÆäËû', '0', 'e200107128140247141080fd', '0', '2013-03-15 09:30:42', '3');
INSERT INTO `errorItem` VALUES ('36', '开始', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('37', '开始', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('38', 'Èë¿â', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('39', 'Èë¿â', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('40', 'Èë¿â', '2', 'e200107128140247141080fd', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('41', 'Èë¿â', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('42', 'Èë¿â', '2', 'e200107128140247141080fd', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('43', 'Èë¿â', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('44', 'Èë¿â', '2', 'e200107128140247141080fd', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('45', 'Èë¿â', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('46', 'ÆäËû', '0', 'e200107128140247141080fd', '0', '2013-03-15 12:04:36', '3');
INSERT INTO `errorItem` VALUES ('47', '乱码', '2', 'e200107128140247141080fd', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('48', 'Èë¿â', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('49', '����', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('50', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('51', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('52', '下面', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('53', '其他', '0', '12341018741301622120000b', '0', '2013-03-15 14:10:35', '3');
INSERT INTO `errorItem` VALUES ('54', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('55', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('56', '下面', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('57', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('58', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('59', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('60', '下面', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('61', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('62', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('63', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('64', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('65', '~~~~~~', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('66', '```````````', '2', 'e200107128140247141080fd', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('67', '其他', '0', 'aa3593666613001617406083', '0', '2013-03-15 14:39:10', '3');
INSERT INTO `errorItem` VALUES ('68', '其他', '0', '12341018741301622120000b', '0', '2013-03-15 14:39:10', '3');
INSERT INTO `errorItem` VALUES ('69', '其他', '0', 'e200107128140247141080fd', '0', '2013-03-15 14:39:10', '3');
INSERT INTO `errorItem` VALUES ('70', '其他', '0', '12341018741301622120000b', '0', '2013-03-15 14:39:10', '3');
INSERT INTO `errorItem` VALUES ('71', '其他', '0', '12341018741301622120000b', '0', '2013-03-15 14:39:10', '3');
INSERT INTO `errorItem` VALUES ('72', '其他', '0', '12341018741301622120000b', '0', '2013-03-15 14:39:10', '3');
INSERT INTO `errorItem` VALUES ('73', '其11', '0', 'e200107128140247141080fd', '0', '2013-03-15 14:39:10', '3');
INSERT INTO `errorItem` VALUES ('74', '入库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('75', '1111111库', '1', '12341018741301622120000b', '2', '2013-03-13 11:23:20', '2');
INSERT INTO `errorItem` VALUES ('76', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-18 15:24:38', '2');
INSERT INTO `errorItem` VALUES ('77', '其他', '2', 'e2001071281401451060a932', '0', '2013-03-18 15:24:38', '2');
INSERT INTO `errorItem` VALUES ('78', '其他', '1', '12341018741301622120000b', '0', '2013-03-18 15:24:38', '2');
INSERT INTO `errorItem` VALUES ('79', '其他', '2', 'e200107128140247141080fd', '0', '2013-03-18 15:24:38', '2');
INSERT INTO `errorItem` VALUES ('80', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-18 15:27:11', '2');
INSERT INTO `errorItem` VALUES ('81', '其他', '2', 'e2001071281401451060a932', '0', '2013-03-18 15:27:11', '2');
INSERT INTO `errorItem` VALUES ('82', '其他', '1', '12341018741301622120000b', '0', '2013-03-18 15:27:11', '2');
INSERT INTO `errorItem` VALUES ('83', '其他', '2', 'e200107128140247141080fd', '0', '2013-03-18 15:27:11', '2');
INSERT INTO `errorItem` VALUES ('84', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-18 15:32:11', '2');
INSERT INTO `errorItem` VALUES ('85', '其他', '2', 'e2001071281401451060a932', '0', '2013-03-18 15:32:11', '2');
INSERT INTO `errorItem` VALUES ('86', '其他', '1', '12341018741301622120000b', '0', '2013-03-18 15:32:11', '2');
INSERT INTO `errorItem` VALUES ('87', '其他', '2', 'e200107128140247141080fd', '0', '2013-03-18 15:32:11', '2');
INSERT INTO `errorItem` VALUES ('88', '其他', '2', 'e2001071281401451060a932', '0', '2013-03-18 15:42:40', '2');
INSERT INTO `errorItem` VALUES ('89', '其他', '1', '12341018741301622120000b', '0', '2013-03-18 15:42:40', '2');
INSERT INTO `errorItem` VALUES ('90', '其他', '2', 'e200107128140247141080fd', '0', '2013-03-18 15:42:40', '2');
INSERT INTO `errorItem` VALUES ('91', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-18 15:42:40', '2');
INSERT INTO `errorItem` VALUES ('92', '其他', '2', 'e2001071281401451060a932', '0', '2013-03-19 15:38:49', '2');
INSERT INTO `errorItem` VALUES ('93', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-19 15:38:49', '2');
INSERT INTO `errorItem` VALUES ('94', '其他', '2', 'e2001071281401451060a932', '0', '2013-03-19 15:44:40', '2');
INSERT INTO `errorItem` VALUES ('95', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-19 15:44:40', '2');
INSERT INTO `errorItem` VALUES ('96', '其他', '2', 'e2001071281401451060a932', '0', '2013-03-19 18:05:36', '2');
INSERT INTO `errorItem` VALUES ('97', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-19 18:05:36', '2');
INSERT INTO `errorItem` VALUES ('98', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-19 20:32:50', '2');
INSERT INTO `errorItem` VALUES ('99', '其他', '2', 'e2001071281401451060a932', '0', '2013-03-19 20:32:50', '2');
INSERT INTO `errorItem` VALUES ('100', '其他', '3', 'e200107128140247141080fd', '0', '2013-03-19 20:32:51', '2');
INSERT INTO `errorItem` VALUES ('101', '其他', '2', 'e2001071281401451060a932', '0', '2013-03-19 20:36:34', '2');
INSERT INTO `errorItem` VALUES ('102', '其他', '2', 'e2001071281401451060a932', '0', '2013-03-26 11:32:43', '2');
INSERT INTO `errorItem` VALUES ('103', '其他', '3', 'e200107128140247141080fd', '0', '2013-03-26 11:32:44', '2');
INSERT INTO `errorItem` VALUES ('104', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-26 11:38:17', '2');
INSERT INTO `errorItem` VALUES ('105', '其他', '3', 'e200107128140247141080fd', '0', '2013-03-26 11:38:17', '2');
INSERT INTO `errorItem` VALUES ('106', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-26 11:42:14', '2');
INSERT INTO `errorItem` VALUES ('107', '其他', '1', 'e2001071281401890820000b', '0', '2013-03-26 11:56:54', '2');
INSERT INTO `errorItem` VALUES ('108', '其他', '1', '12341018741301622120000b', '0', '2013-03-26 12:00:34', '2');

-- ----------------------------
-- Table structure for inputBatch
-- ----------------------------
DROP TABLE IF EXISTS `inputBatch`;
CREATE TABLE `inputBatch` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `commodityAmount` int(11) NOT NULL,
  `inputTime` datetime DEFAULT NULL,
  `operatorId` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of inputBatch
-- ----------------------------
INSERT INTO `inputBatch` VALUES ('1', '1', '2013-02-19 09:45:52', '1');
INSERT INTO `inputBatch` VALUES ('2', '1', '2013-02-19 09:46:16', '1');
INSERT INTO `inputBatch` VALUES ('3', '1', '2013-02-19 09:46:27', '1');
INSERT INTO `inputBatch` VALUES ('9', '3', '2013-03-05 15:08:40', '2');
INSERT INTO `inputBatch` VALUES ('10', '3', '2013-03-05 15:30:54', '2');
INSERT INTO `inputBatch` VALUES ('11', '29', '2013-03-07 11:11:56', '1');
INSERT INTO `inputBatch` VALUES ('12', '29', '2013-03-05 15:35:38', '2');
INSERT INTO `inputBatch` VALUES ('13', '29', '2013-03-05 15:37:32', '2');
INSERT INTO `inputBatch` VALUES ('14', '29', '2013-03-05 15:37:33', '2');
INSERT INTO `inputBatch` VALUES ('15', '29', '2013-03-05 15:40:02', '2');
INSERT INTO `inputBatch` VALUES ('16', '29', '2013-03-05 15:40:04', '2');
INSERT INTO `inputBatch` VALUES ('17', '29', '2013-03-05 15:40:18', '2');
INSERT INTO `inputBatch` VALUES ('18', '29', '2013-03-05 15:40:19', '2');
INSERT INTO `inputBatch` VALUES ('19', '29', '2013-03-05 15:41:55', '2');
INSERT INTO `inputBatch` VALUES ('20', '29', '2013-03-05 15:43:11', '2');
INSERT INTO `inputBatch` VALUES ('21', '2', '2013-03-05 16:24:24', '2');
INSERT INTO `inputBatch` VALUES ('22', '2', '2013-03-12 15:47:01', '1');
INSERT INTO `inputBatch` VALUES ('23', '2', '2013-03-12 16:00:38', '1');
INSERT INTO `inputBatch` VALUES ('24', '2', '2013-03-13 10:02:33', '1');
INSERT INTO `inputBatch` VALUES ('25', '2', '2013-03-13 10:07:08', '1');
INSERT INTO `inputBatch` VALUES ('26', '2', '2013-03-13 11:17:10', '1');
INSERT INTO `inputBatch` VALUES ('27', '2', '2013-03-13 11:23:20', '1');
INSERT INTO `inputBatch` VALUES ('28', '2', '2013-03-19 16:32:08', '1');
INSERT INTO `inputBatch` VALUES ('29', '3', '2013-03-19 17:28:18', '1');
INSERT INTO `inputBatch` VALUES ('30', '3', '2013-03-19 19:12:55', '1');
INSERT INTO `inputBatch` VALUES ('31', '3', '2013-03-19 19:55:06', '1');
INSERT INTO `inputBatch` VALUES ('32', '3', '2013-03-20 10:55:28', '1');
INSERT INTO `inputBatch` VALUES ('33', '2', '2013-03-26 11:20:48', '1');
INSERT INTO `inputBatch` VALUES ('34', '3', '2013-03-26 12:09:01', '1');

-- ----------------------------
-- Table structure for inputCache
-- ----------------------------
DROP TABLE IF EXISTS `inputCache`;
CREATE TABLE `inputCache` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `commodityName` int(11) NOT NULL,
  `commodityId` varchar(255) NOT NULL,
  `operatorId` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=298 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of inputCache
-- ----------------------------

-- ----------------------------
-- Table structure for inputHistory
-- ----------------------------
DROP TABLE IF EXISTS `inputHistory`;
CREATE TABLE `inputHistory` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `commodityName` int(11) NOT NULL,
  `commodityId` varchar(255) NOT NULL,
  `inputBatch` int(11) NOT NULL,
  `inputStatus` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=67 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of inputHistory
-- ----------------------------
INSERT INTO `inputHistory` VALUES ('1', '1', 'adsfjka', '1', '1');
INSERT INTO `inputHistory` VALUES ('2', '2', 'bdsfjkb', '2', '2');
INSERT INTO `inputHistory` VALUES ('3', '3', 'cdsfjkc', '3', '1');
INSERT INTO `inputHistory` VALUES ('4', '1', 'dadfafa', '1', '1');
INSERT INTO `inputHistory` VALUES ('5', '2', 'dadfafa', '1', '3');
INSERT INTO `inputHistory` VALUES ('6', '1', 'e200107128140247141080fd', '11', '1');
INSERT INTO `inputHistory` VALUES ('7', '1', '12341018741301622120000b', '0', '1');
INSERT INTO `inputHistory` VALUES ('8', '2', 'e2001071281401451060a932', '0', '1');
INSERT INTO `inputHistory` VALUES ('9', '1', '12341018741301622120000b', '27', '1');
INSERT INTO `inputHistory` VALUES ('10', '2', 'e2001071281401451060a932', '27', '1');
INSERT INTO `inputHistory` VALUES ('13', '2', 'e200107128140247141080fd', '27', '1');
INSERT INTO `inputHistory` VALUES ('14', '1', '12341018741301622120000b', '27', '1');
INSERT INTO `inputHistory` VALUES ('15', '2', 'e200107128140247141080fd', '27', '1');
INSERT INTO `inputHistory` VALUES ('16', '2', '', '27', '1');
INSERT INTO `inputHistory` VALUES ('17', '1', '12341018741301622120000b', '27', '1');
INSERT INTO `inputHistory` VALUES ('18', '2', '开始', '27', '1');
INSERT INTO `inputHistory` VALUES ('19', '2', 'e200107128140247141080fd', '27', '1');
INSERT INTO `inputHistory` VALUES ('20', '1', '~~~~~~~~~~~~~~~~~~~', '27', '1');
INSERT INTO `inputHistory` VALUES ('21', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('22', '2', '~~~~~~~~~~', '27', '1');
INSERT INTO `inputHistory` VALUES ('23', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('24', '2', 'e200107128140247141080fd', '27', '1');
INSERT INTO `inputHistory` VALUES ('25', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('26', '2', 'e200107128140247141080fd', '27', '1');
INSERT INTO `inputHistory` VALUES ('27', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('28', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('29', '2', 'next', '27', '1');
INSERT INTO `inputHistory` VALUES ('30', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('31', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('32', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('33', '2', 'next', '27', '1');
INSERT INTO `inputHistory` VALUES ('34', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('35', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('36', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('37', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('38', '2', 'next', '27', '1');
INSERT INTO `inputHistory` VALUES ('39', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('40', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('41', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('42', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('43', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('44', '2', '======================', '27', '1');
INSERT INTO `inputHistory` VALUES ('45', '2', 'e200107128140247141080fd', '27', '2');
INSERT INTO `inputHistory` VALUES ('46', '1', '111111111111111111111111111', '27', '1');
INSERT INTO `inputHistory` VALUES ('47', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('48', '2', '11', '27', '1');
INSERT INTO `inputHistory` VALUES ('49', '1', '12341018741301622120000b', '27', '2');
INSERT INTO `inputHistory` VALUES ('50', '2', '2222222222222222', '27', '1');
INSERT INTO `inputHistory` VALUES ('51', '1', '12341018741301622120000b', '27', '1');
INSERT INTO `inputHistory` VALUES ('52', '2', 'e200107128140247141080fd', '27', '1');
INSERT INTO `inputHistory` VALUES ('53', '1', '12341018741301622120000b', '27', '1');
INSERT INTO `inputHistory` VALUES ('54', '2', 'e200107128140247141080fd', '27', '1');
INSERT INTO `inputHistory` VALUES ('55', '2', 'e2001071281401451060a932', '28', '1');
INSERT INTO `inputHistory` VALUES ('56', '1', 'e2001071281401890820000b', '28', '1');
INSERT INTO `inputHistory` VALUES ('57', '2', 'e2001071281401451060a932', '29', '1');
INSERT INTO `inputHistory` VALUES ('58', '1', 'e2001071281401890820000b', '29', '1');
INSERT INTO `inputHistory` VALUES ('59', '3', 'e200107128140247141080fd', '30', '1');
INSERT INTO `inputHistory` VALUES ('60', '3', 'e200107128140247141080fd', '31', '1');
INSERT INTO `inputHistory` VALUES ('61', '3', 'e200107128140247141080fd', '32', '1');
INSERT INTO `inputHistory` VALUES ('62', '2', 'e2001071281401451060a932', '33', '1');
INSERT INTO `inputHistory` VALUES ('63', '3', 'e200107128140247141080fd', '33', '1');
INSERT INTO `inputHistory` VALUES ('64', '1', '12341018741301622120000b', '34', '1');
INSERT INTO `inputHistory` VALUES ('65', '2', 'e2001071281401451060a932', '34', '1');
INSERT INTO `inputHistory` VALUES ('66', '3', 'e200107128140247141080fd', '34', '1');

-- ----------------------------
-- Table structure for inputOutputStatus
-- ----------------------------
DROP TABLE IF EXISTS `inputOutputStatus`;
CREATE TABLE `inputOutputStatus` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `inputOutputStatus` varchar(255) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of inputOutputStatus
-- ----------------------------
INSERT INTO `inputOutputStatus` VALUES ('1', '正常');
INSERT INTO `inputOutputStatus` VALUES ('2', '缺少');
INSERT INTO `inputOutputStatus` VALUES ('3', '增加');

-- ----------------------------
-- Table structure for operators
-- ----------------------------
DROP TABLE IF EXISTS `operators`;
CREATE TABLE `operators` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `password` varchar(255) DEFAULT NULL,
  `operatorName` varchar(255) NOT NULL,
  `createTime` datetime DEFAULT NULL,
  `lastLoginTime` datetime NOT NULL,
  `status` tinyint(2) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of operators
-- ----------------------------
INSERT INTO `operators` VALUES ('1', '111111', 'root', '2013-02-03 00:00:00', '2013-03-26 05:49:31', '0');
INSERT INTO `operators` VALUES ('2', '1', '1', '2013-02-26 18:44:43', '2013-03-20 12:22:41', '0');
INSERT INTO `operators` VALUES ('3', 'admin', 'admin', '2013-02-26 18:45:49', '2013-03-11 10:21:45', '1');

-- ----------------------------
-- Table structure for outputBatch
-- ----------------------------
DROP TABLE IF EXISTS `outputBatch`;
CREATE TABLE `outputBatch` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `commodityAmount` int(11) NOT NULL,
  `outputTime` datetime NOT NULL,
  `operatorId` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of outputBatch
-- ----------------------------
INSERT INTO `outputBatch` VALUES ('1', '2', '2013-02-19 16:21:37', '1');
INSERT INTO `outputBatch` VALUES ('2', '1', '2013-02-20 10:58:15', '1');
INSERT INTO `outputBatch` VALUES ('3', '3', '2013-02-20 10:58:28', '1');
INSERT INTO `outputBatch` VALUES ('4', '2', '2013-03-12 11:54:50', '1');
INSERT INTO `outputBatch` VALUES ('5', '2', '2013-03-12 12:00:02', '1');
INSERT INTO `outputBatch` VALUES ('6', '2', '2013-03-12 12:18:47', '1');
INSERT INTO `outputBatch` VALUES ('7', '0', '2013-03-12 12:27:24', '1');
INSERT INTO `outputBatch` VALUES ('8', '2', '2013-03-12 14:44:33', '1');
INSERT INTO `outputBatch` VALUES ('9', '0', '2013-03-12 14:50:16', '1');
INSERT INTO `outputBatch` VALUES ('10', '0', '2013-03-12 14:51:25', '1');
INSERT INTO `outputBatch` VALUES ('11', '2', '2013-03-12 15:10:25', '1');
INSERT INTO `outputBatch` VALUES ('12', '2', '2013-03-12 15:12:17', '1');
INSERT INTO `outputBatch` VALUES ('13', '2', '2013-03-12 15:23:28', '1');
INSERT INTO `outputBatch` VALUES ('14', '2', '2013-03-19 10:44:32', '1');
INSERT INTO `outputBatch` VALUES ('15', '2', '2013-03-19 15:52:33', '1');
INSERT INTO `outputBatch` VALUES ('16', '2', '2013-03-19 16:34:07', '1');
INSERT INTO `outputBatch` VALUES ('17', '3', '2013-03-19 20:41:30', '1');
INSERT INTO `outputBatch` VALUES ('18', '0', '2013-03-19 20:48:06', '1');
INSERT INTO `outputBatch` VALUES ('19', '3', '2013-03-19 20:50:36', '1');
INSERT INTO `outputBatch` VALUES ('20', '3', '2013-03-20 11:02:31', '1');
INSERT INTO `outputBatch` VALUES ('21', '3', '2013-03-26 12:06:01', '1');
INSERT INTO `outputBatch` VALUES ('22', '3', '2013-03-26 12:11:34', '1');

-- ----------------------------
-- Table structure for outputCache
-- ----------------------------
DROP TABLE IF EXISTS `outputCache`;
CREATE TABLE `outputCache` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `commodityName` int(11) NOT NULL,
  `commodityId` varchar(255) NOT NULL,
  `operatorId` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=116 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of outputCache
-- ----------------------------

-- ----------------------------
-- Table structure for outputHistory
-- ----------------------------
DROP TABLE IF EXISTS `outputHistory`;
CREATE TABLE `outputHistory` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `commodityName` int(11) NOT NULL,
  `commodityId` varchar(255) NOT NULL,
  `outputBatch` int(11) NOT NULL,
  `outputStatus` int(11) DEFAULT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of outputHistory
-- ----------------------------
INSERT INTO `outputHistory` VALUES ('1', '1', 'abcdefg', '1', '1');
INSERT INTO `outputHistory` VALUES ('2', '1', 'bbcedefg', '1', '1');
INSERT INTO `outputHistory` VALUES ('3', '2', 'cbcedefg', '2', '1');
INSERT INTO `outputHistory` VALUES ('4', '1', 'dbcedefg', '3', '1');
INSERT INTO `outputHistory` VALUES ('5', '1', 'ebcedefg', '3', '1');
INSERT INTO `outputHistory` VALUES ('6', '1', 'fbcedefg', '3', '1');
INSERT INTO `outputHistory` VALUES ('7', '0', 'e2001071281401451060a932', '5', '1');
INSERT INTO `outputHistory` VALUES ('8', '0', 'e2001071281401890820000b', '5', '1');
INSERT INTO `outputHistory` VALUES ('9', '0', 'e2001071281401890820000b', '6', '1');
INSERT INTO `outputHistory` VALUES ('10', '0', 'e2001071281401451060a932', '6', '1');
INSERT INTO `outputHistory` VALUES ('11', '0', 'e2001071281401890820000b', '8', '1');
INSERT INTO `outputHistory` VALUES ('12', '0', 'e2001071281401451060a932', '8', '1');
INSERT INTO `outputHistory` VALUES ('13', '0', 'e2001071281401890820000b', '11', '1');
INSERT INTO `outputHistory` VALUES ('14', '0', 'e2001071281401451060a932', '11', '1');
INSERT INTO `outputHistory` VALUES ('15', '0', 'e2001071281401451060a932', '12', '1');
INSERT INTO `outputHistory` VALUES ('16', '0', 'e2001071281401890820000b', '12', '1');
INSERT INTO `outputHistory` VALUES ('17', '0', 'e2001071281401451060a932', '13', '1');
INSERT INTO `outputHistory` VALUES ('18', '0', 'e2001071281401890820000b', '13', '1');
INSERT INTO `outputHistory` VALUES ('19', '0', 'e2001071281401451060a932', '14', '1');
INSERT INTO `outputHistory` VALUES ('20', '0', 'e2001071281401890820000b', '14', '1');
INSERT INTO `outputHistory` VALUES ('21', '0', 'e2001071281401451060a932', '15', '1');
INSERT INTO `outputHistory` VALUES ('22', '0', 'e2001071281401890820000b', '15', '1');
INSERT INTO `outputHistory` VALUES ('23', '2', 'e2001071281401451060a932', '16', '1');
INSERT INTO `outputHistory` VALUES ('24', '1', 'e2001071281401890820000b', '16', '1');
INSERT INTO `outputHistory` VALUES ('25', '1', 'e2001071281401890820000b', '17', '1');
INSERT INTO `outputHistory` VALUES ('26', '2', 'e2001071281401451060a932', '17', '1');
INSERT INTO `outputHistory` VALUES ('27', '3', 'e200107128140247141080fd', '17', '1');
INSERT INTO `outputHistory` VALUES ('28', '2', 'e2001071281401451060a932', '19', '1');
INSERT INTO `outputHistory` VALUES ('29', '1', 'e2001071281401890820000b', '19', '1');
INSERT INTO `outputHistory` VALUES ('30', '3', 'e200107128140247141080fd', '19', '1');
INSERT INTO `outputHistory` VALUES ('31', '1', 'e2001071281401890820000b', '20', '1');
INSERT INTO `outputHistory` VALUES ('32', '2', 'e2001071281401451060a932', '20', '1');
INSERT INTO `outputHistory` VALUES ('33', '3', 'e200107128140247141080fd', '20', '1');
INSERT INTO `outputHistory` VALUES ('34', '1', '12341018741301622120000b', '21', '1');
INSERT INTO `outputHistory` VALUES ('35', '2', 'e2001071281401451060a932', '21', '1');
INSERT INTO `outputHistory` VALUES ('36', '3', 'e200107128140247141080fd', '21', '1');
INSERT INTO `outputHistory` VALUES ('37', '1', '12341018741301622120000b', '22', '1');
INSERT INTO `outputHistory` VALUES ('38', '2', 'e2001071281401451060a932', '22', '1');
INSERT INTO `outputHistory` VALUES ('39', '3', 'e200107128140247141080fd', '22', '1');

-- ----------------------------
-- Table structure for storedCommodity
-- ----------------------------
DROP TABLE IF EXISTS `storedCommodity`;
CREATE TABLE `storedCommodity` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `commodityName` int(11) NOT NULL,
  `commodityId` varchar(255) NOT NULL,
  `inputBatch` int(11) NOT NULL,
  PRIMARY KEY (`Id`),
  KEY `index1` (`commodityId`)
) ENGINE=InnoDB AUTO_INCREMENT=109 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of storedCommodity
-- ----------------------------

-- ----------------------------
-- Table structure for type
-- ----------------------------
DROP TABLE IF EXISTS `type`;
CREATE TABLE `type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `commodityName` varchar(255) NOT NULL,
  `zone` int(11) DEFAULT NULL,
  `sum` int(11) NOT NULL,
  `addtime` datetime NOT NULL,
  `operatorId` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idx_zone` (`zone`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of type
-- ----------------------------
INSERT INTO `type` VALUES ('1', '背包', '1', '1', '2013-02-19 14:45:20', '1');
INSERT INTO `type` VALUES ('2', '笔记本', '1', '1', '2013-02-19 14:45:41', '0');
INSERT INTO `type` VALUES ('3', '宠物', '2', '1', '2013-02-19 14:45:47', '0');
INSERT INTO `type` VALUES ('4', '大容量充电宝', '3', '2', '2013-02-19 14:45:53', '0');


-- ----------------------------
-- Table structure for zone
-- ----------------------------
DROP TABLE IF EXISTS `zone`;
CREATE TABLE `zone` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `zoneName` varchar(255) NOT NULL,
  `zoneIP` varchar(255) DEFAULT NULL,
  `zoneId` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Id`),
  KEY `idx_name` (`zoneName`)
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of zone
-- ----------------------------
INSERT INTO `zone` VALUES ('1', '常规行李区', '172.20.223.111', 'aa3593666613001617406083');
INSERT INTO `zone` VALUES ('2', '贵重行李区', '172.20.223.111', 'e20010187413015921200006');
INSERT INTO `zone` VALUES ('3', '特殊行李区', '172.20.223.111', 'e20010187413016023901f55');
INSERT INTO `zone` VALUES ('4', '危险物品区', '172.20.223.111', 'e2001071281400810950b6af');
