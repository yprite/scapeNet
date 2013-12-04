-- MySQL dump 10.13  Distrib 5.5.34, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: scapenet
-- ------------------------------------------------------
-- Server version	5.5.34-0ubuntu0.12.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `admin_info`
--

DROP TABLE IF EXISTS `admin_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `admin_info` (
  `pid` int(1) NOT NULL,
  `id` varchar(20) DEFAULT NULL,
  `passwd` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admin_info`
--

LOCK TABLES `admin_info` WRITE;
/*!40000 ALTER TABLE `admin_info` DISABLE KEYS */;
INSERT INTO `admin_info` VALUES (1,'admin','1234');
/*!40000 ALTER TABLE `admin_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ip_data`
--

DROP TABLE IF EXISTS `ip_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ip_data` (
  `pid` int(10) NOT NULL AUTO_INCREMENT,
  `ip` varchar(20) DEFAULT NULL,
  `mac` varchar(20) DEFAULT NULL,
  `up_traffic_cur` varchar(10) DEFAULT NULL,
  `down_traffic_cur` varchar(10) DEFAULT NULL,
  `up_traffic_limit` varchar(10) DEFAULT NULL,
  `down_traffic_limit` varchar(10) DEFAULT NULL,
  `isStatus` int(1) DEFAULT NULL,
  `name` varchar(10) DEFAULT NULL,
  `port` varchar(50) DEFAULT NULL,
  `qos` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`pid`)
) ENGINE=InnoDB AUTO_INCREMENT=255 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ip_data`
--

LOCK TABLES `ip_data` WRITE;
/*!40000 ALTER TABLE `ip_data` DISABLE KEYS */;
INSERT INTO `ip_data` VALUES (1,'210.118.34.1','60-A4-4C-B4-F9-B1','0','0','4000','4000',0,'Router',NULL,NULL),(2,'210.118.34.2','','0','0','4000','4000',0,NULL,NULL,NULL),(3,'210.118.34.3','','0','0','4000','4000',0,NULL,NULL,NULL),(4,'210.118.34.4','','0','0','4000','4000',0,NULL,NULL,NULL),(5,'210.118.34.5','','0','0','4000','4000',0,NULL,NULL,NULL),(6,'210.118.34.6','','0','0','4000','4000',0,NULL,NULL,NULL),(7,'210.118.34.7','','0','0','4000','4000',0,NULL,NULL,NULL),(8,'210.118.34.8','','0','0','4000','4000',0,NULL,NULL,NULL),(9,'210.118.34.9','','0','0','4000','4000',0,NULL,NULL,NULL),(10,'210.118.34.10','','0','0','4000','4000',0,NULL,NULL,NULL),(11,'210.118.34.11','e8-11-32-30-78-c0','0','0','4000','4000',1,'배기훈',NULL,NULL),(12,'210.118.34.12','','0','0','4000','4000',0,'배기훈',NULL,NULL),(13,'210.118.34.13','','0','0','4000','4000',0,'이지성',NULL,NULL),(14,'210.118.34.14','e8-03-9a-6e-14-fe','0','1','4000','4000',1,'이지성',NULL,NULL),(15,'210.118.34.15','','0','0','4000','4000',1,'박철준',NULL,NULL),(16,'210.118.34.16','','0','0','4000','4000',0,'박철준',NULL,NULL),(17,'210.118.34.17','e8-11-32-30-7c-47','40','42','4000','4000',1,'이귀로','135 ',NULL),(18,'210.118.34.18','','0','0','4000','4000',0,'이귀로',NULL,NULL),(19,'210.118.34.19','','0','0','4000','4000',0,'오병윤',NULL,NULL),(20,'210.118.34.20','','0','0','4000','4000',0,'오병윤',NULL,NULL),(21,'210.118.34.21','','0','0','4000','4000',0,'서준의',NULL,NULL),(22,'210.118.34.22','00-13-77-81-d3-65','0','0','4000','4000',0,'서준의',NULL,NULL),(23,'210.118.34.23','00-13-77-8e-9b-1c','0','0','4000','4000',1,'강미진',NULL,NULL),(24,'210.118.34.24','8c-89-a5-0b-c1-e0','0','0','4000','4000',0,'강미진',NULL,NULL),(25,'210.118.34.25','','0','0','4000','4000',1,'고관석',NULL,NULL),(26,'210.118.34.26','','0','0','4000','4000',0,'고관석',NULL,NULL),(27,'210.118.34.27','94-de-80-01-09-3d','68','163','4000','4000',1,'김경민','2869 3389 5357 ',NULL),(28,'210.118.34.28','','0','1','4000','4000',0,'김경민','139 445 5357 ',NULL),(29,'210.118.34.29','','0','0','4000','4000',1,'김도완','3389 6004 ',NULL),(30,'210.118.34.30','','0','0','4000','4000',0,'김도완',NULL,NULL),(31,'210.118.34.31','','0','0','4000','4000',0,'윤지환',NULL,NULL),(32,'210.118.34.32','','0','0','4000','4000',0,'윤지환',NULL,NULL),(33,'210.118.34.33','','0','2','4000','4000',1,'이가빈',NULL,NULL),(34,'210.118.34.34','','0','0','4000','4000',0,'이가빈',NULL,NULL),(35,'210.118.34.35','','0','0','4000','4000',1,'김서웅',NULL,NULL),(36,'210.118.34.36','','0','0','4000','4000',0,'김서웅',NULL,NULL),(37,'210.118.34.37','e8-03-9a-6e-4a-7b','0','0','4000','4000',1,'김재호',NULL,NULL),(38,'210.118.34.38','','0','0','4000','4000',0,'김재호',NULL,NULL),(39,'210.118.34.39','54-04-a6-a0-7f-0a','0','0','4000','4000',1,'황재엽',NULL,NULL),(40,'210.118.34.40','','0','0','4000','4000',0,'황재엽',NULL,NULL),(41,'210.118.34.41','','0','0','4000','4000',0,'박형진',NULL,NULL),(42,'210.118.34.42','e8-03-9a-6d-df-31','1','0','4000','4000',1,'박형진','80 445 3389 7019 51103 ',NULL),(43,'210.118.34.43','e8-03-9a-6e-13-7e','0','0','4000','4000',1,'조영록',NULL,NULL),(44,'210.118.34.44','60-A4-4C-B4-F9-B1','0','0','4000','4000',0,'조영록',NULL,NULL),(45,'210.118.34.45','e8-03-9a-63-56-26','0','0','4000','4000',1,'엄수용','445 3389 ',NULL),(46,'210.118.34.46','00-0c-29-10-50-6e','129','85','4000','4000',1,'엄수용',NULL,NULL),(47,'210.118.34.47','','0','0','4000','4000',0,NULL,NULL,NULL),(48,'210.118.34.48','00-24-54-27-3e-3a','44','5','4000','4000',1,NULL,'135 139 445 1935 2869 5357 49152 ',NULL),(49,'210.118.34.49','00-13-77-8e-9d-e0','0','0','4000','4000',1,'김경태',NULL,NULL),(50,'210.118.34.50','','0','0','4000','4000',0,'김경태',NULL,NULL),(51,'210.118.34.51','bc-5f-f4-20-ef-93','0','0','4000','4000',1,'강호민',NULL,NULL),(52,'210.118.34.52','','0','0','4000','4000',0,'강호민',NULL,NULL),(53,'210.118.34.53','00-13-77-8e-99-dd','72','87','4000','4000',1,'권회근','902 3389 ',NULL),(54,'210.118.34.54','','0','0','4000','4000',1,'권회근',NULL,NULL),(55,'210.118.34.55','00-13-77-cf-a0-0a','0','0','4000','4000',0,'김용훈',NULL,NULL),(56,'210.118.34.56','','183','0','4000','4000',1,'김용훈','135 139 445 912 2103 5357 10243 49157 ',NULL),(57,'210.118.34.57','00-13-77-8e-9a-7a','0','1','4000','4000',1,'남궁현',NULL,NULL),(58,'210.118.34.58','00-10-13-af-b8-c6','0','0','7000','7000',0,'남궁현',NULL,NULL),(59,'210.118.34.59','','0','0','4000','4000',0,'박경록',NULL,NULL),(60,'210.118.34.60','','0','0','4000','4000',0,'박경록',NULL,NULL),(61,'210.118.34.61','00-13-77-87-85-30','0','0','4000','4000',0,'이샛별',NULL,NULL),(62,'210.118.34.62','','0','0','4000','4000',1,'이샛별','3389 6004 7019 ',NULL),(63,'210.118.34.63','00-24-54-98-4f-e5','0','0','4000','4000',1,'이서영',NULL,NULL),(64,'210.118.34.64','','0','0','4000','4000',0,'이서영',NULL,NULL),(65,'210.118.34.65','','0','0','4000','4000',0,'이승현',NULL,NULL),(66,'210.118.34.66','','0','0','4000','4000',0,'이승현',NULL,NULL),(67,'210.118.34.67','','0','0','4000','4000',0,'임옥현',NULL,NULL),(68,'210.118.34.68','00-13-77-cf-a3-ca','0','0','4000','4000',1,'임옥현',NULL,NULL),(69,'210.118.34.69','','157','1','4000','4000',1,'주지현','3306 3389 ',NULL),(70,'210.118.34.70','','0','0','4000','4000',0,'주지현',NULL,NULL),(71,'210.118.34.71','00-13-77-83-0b-23','0','1','4000','4000',1,'최인수',NULL,NULL),(72,'210.118.34.72','','0','0','4000','4000',0,'최인수',NULL,NULL),(73,'210.118.34.73','e8-03-9a-63-56-35','0','0','4000','4000',1,'최주홍',NULL,NULL),(74,'210.118.34.74','','0','0','4000','4000',0,'최주홍',NULL,NULL),(75,'210.118.34.75','00-13-77-80-a7-4e','0','0','4000','4000',1,'황규하',NULL,NULL),(76,'210.118.34.76','','0','0','4000','4000',0,'황규하',NULL,NULL),(77,'210.118.34.77','90-2b-34-5d-87-2c','0','0','4000','4000',0,'정동환',NULL,NULL),(78,'210.118.34.78','00-13-77-8e-99-b0','0','0','4000','4000',1,'정동환',NULL,NULL),(79,'210.118.34.79','','0','0','4000','4000',1,'이의리',NULL,NULL),(80,'210.118.34.80','','0','0','4000','4000',0,'이의리',NULL,NULL),(81,'210.118.34.81','','0','0','4000','4000',0,'유성결',NULL,NULL),(82,'210.118.34.82','','0','0','4000','4000',0,'유성결',NULL,NULL),(83,'210.118.34.83','','0','0','4000','4000',1,'김민수','22 22 53 53 80 80 135 139 135 139 443 443 445 445 ',NULL),(84,'210.118.34.84','bc-5f-f4-55-80-ab','0','0','4000','4000',1,'김민수',NULL,NULL),(85,'210.118.34.85','','0','0','4000','4000',0,'서승현',NULL,NULL),(86,'210.118.34.86','','0','0','4000','4000',0,'서승현',NULL,NULL),(87,'210.118.34.87','','0','0','4000','4000',0,'김덕주',NULL,NULL),(88,'210.118.34.88','00-13-77-81-ea-5c','46','0','4000','4000',1,'김덕주',NULL,NULL),(89,'210.118.34.89','','0','1','4000','4000',1,NULL,NULL,NULL),(90,'210.118.34.90','','0','0','4000','4000',0,'운영실',NULL,NULL),(91,'210.118.34.91','','0','0','4000','4000',0,'운영실',NULL,NULL),(92,'210.118.34.92','','0','0','4000','4000',0,'운영실',NULL,NULL),(93,'210.118.34.93','','0','0','4000','4000',0,'운영실',NULL,NULL),(94,'210.118.34.94','','0','0','4000','4000',0,'운영실',NULL,NULL),(95,'210.118.34.95','00-13-77-cf-a9-11','0','0','4000','4000',1,'운영실',NULL,NULL),(96,'210.118.34.96','e8-03-9a-63-56-2f','0','0','4000','4000',1,'운영실',NULL,NULL),(97,'210.118.34.97','','0','0','4000','4000',0,'운영실',NULL,NULL),(98,'210.118.34.98','','0','0','4000','4000',0,'운영실',NULL,NULL),(99,'210.118.34.99','','0','0','4000','4000',1,'운영실',NULL,NULL),(100,'210.118.34.100','','0','0','4000','4000',0,NULL,NULL,NULL),(101,'210.118.34.101','00-13-77-87-84-66','0','0','4000','4000',1,'프린트서버',NULL,NULL),(102,'210.118.34.102','bc-5f-f4-63-32-2b','3','0','4000','4000',1,'파일서버','22 80 139 445 ',NULL),(103,'210.118.34.103','00-13-77-8f-81-bf','0','0','4000','4000',1,'아웃룩서버','25 88 445 464 587 808 3269 6002 ',NULL),(104,'210.118.34.104','','0','0','4000','4000',0,NULL,NULL,NULL),(105,'210.118.34.105','00-15-99-07-de-85','0','0','4000','4000',1,NULL,NULL,NULL),(106,'210.118.34.106','','0','0','4000','4000',0,NULL,NULL,NULL),(107,'210.118.34.107','','0','0','4000','4000',0,NULL,NULL,NULL),(108,'210.118.34.108','','0','0','4000','4000',0,NULL,NULL,NULL),(109,'210.118.34.109','','0','0','4000','4000',0,NULL,NULL,NULL),(110,'210.118.34.110','','0','0','4000','4000',0,NULL,NULL,NULL),(111,'210.118.34.111','','0','0','4000','4000',0,NULL,NULL,NULL),(112,'210.118.34.112','','0','0','4000','4000',0,NULL,NULL,NULL),(113,'210.118.34.113','','0','0','4000','4000',0,NULL,NULL,NULL),(114,'210.118.34.114','','0','0','4000','4000',0,NULL,NULL,NULL),(115,'210.118.34.115','','0','0','4000','4000',0,NULL,NULL,NULL),(116,'210.118.34.116','','0','0','4000','4000',0,NULL,NULL,NULL),(117,'210.118.34.117','','0','0','4000','4000',0,NULL,NULL,NULL),(118,'210.118.34.118','','0','0','4000','4000',0,NULL,NULL,NULL),(119,'210.118.34.119','','0','0','4000','4000',0,NULL,NULL,NULL),(120,'210.118.34.120','','0','0','4000','4000',0,NULL,NULL,NULL),(121,'210.118.34.121','','0','0','4000','4000',0,NULL,NULL,NULL),(122,'210.118.34.122','','0','0','4000','4000',0,NULL,NULL,NULL),(123,'210.118.34.123','','0','0','4000','4000',0,NULL,NULL,NULL),(124,'210.118.34.124','','0','0','4000','4000',0,NULL,NULL,NULL),(125,'210.118.34.125','','0','0','4000','4000',0,NULL,NULL,NULL),(126,'210.118.34.126','','0','0','4000','4000',0,NULL,NULL,NULL),(127,'210.118.34.127','','0','0','4000','4000',0,NULL,NULL,NULL),(128,'210.118.34.128','','0','0','4000','4000',0,NULL,NULL,NULL),(129,'210.118.34.129','','0','0','4000','4000',0,NULL,NULL,NULL),(130,'210.118.34.130','','0','0','4000','4000',0,NULL,NULL,NULL),(131,'210.118.34.131','','0','0','4000','4000',0,NULL,NULL,NULL),(132,'210.118.34.132','','0','0','4000','4000',0,NULL,NULL,NULL),(133,'210.118.34.133','','0','0','4000','4000',0,NULL,NULL,NULL),(134,'210.118.34.134','','0','0','4000','4000',0,NULL,NULL,NULL),(135,'210.118.34.135','','0','0','4000','4000',0,NULL,NULL,NULL),(136,'210.118.34.136','','0','0','4000','4000',0,NULL,NULL,NULL),(137,'210.118.34.137','','0','0','4000','4000',0,NULL,NULL,NULL),(138,'210.118.34.138','','0','0','4000','4000',0,NULL,NULL,NULL),(139,'210.118.34.139','','0','0','4000','4000',0,NULL,NULL,NULL),(140,'210.118.34.140','','0','0','4000','4000',0,NULL,NULL,NULL),(141,'210.118.34.141','','0','0','4000','4000',0,NULL,NULL,NULL),(142,'210.118.34.142','','0','0','4000','4000',0,NULL,NULL,NULL),(143,'210.118.34.143','','0','0','4000','4000',0,NULL,NULL,NULL),(144,'210.118.34.144','','0','0','4000','4000',0,NULL,NULL,NULL),(145,'210.118.34.145','','0','0','4000','4000',0,NULL,NULL,NULL),(146,'210.118.34.146','','0','0','4000','4000',0,NULL,NULL,NULL),(147,'210.118.34.147','','0','0','4000','4000',0,NULL,NULL,NULL),(148,'210.118.34.148','','0','0','4000','4000',0,NULL,NULL,NULL),(149,'210.118.34.149','','0','0','4000','4000',0,NULL,NULL,NULL),(150,'210.118.34.150','','0','0','4000','4000',1,NULL,NULL,NULL),(151,'210.118.34.151','','0','0','4000','4000',0,NULL,NULL,NULL),(152,'210.118.34.152','','0','0','4000','4000',1,NULL,NULL,NULL),(153,'210.118.34.153','','0','0','4000','4000',0,NULL,NULL,NULL),(154,'210.118.34.154','','0','33','4000','4000',0,NULL,NULL,NULL),(155,'210.118.34.155','','138','1','4000','4000',0,NULL,NULL,NULL),(156,'210.118.34.156','','0','0','4000','4000',0,NULL,NULL,NULL),(157,'210.118.34.157','','0','0','4000','4000',1,NULL,NULL,NULL),(158,'210.118.34.158','','0','0','4000','4000',0,NULL,NULL,NULL),(159,'210.118.34.159','','0','0','4000','4000',0,NULL,NULL,NULL),(160,'210.118.34.160','','0','1','4000','4000',0,NULL,NULL,NULL),(161,'210.118.34.161','','0','0','4000','4000',0,NULL,NULL,NULL),(162,'210.118.34.162','','0','0','4000','4000',0,NULL,NULL,NULL),(163,'210.118.34.163','','0','0','4000','4000',0,NULL,NULL,NULL),(164,'210.118.34.164','','0','0','4000','4000',0,NULL,NULL,NULL),(165,'210.118.34.165','','0','0','4000','4000',0,NULL,NULL,NULL),(166,'210.118.34.166','','0','0','4000','4000',0,NULL,NULL,NULL),(167,'210.118.34.167','','0','0','4000','4000',0,NULL,NULL,NULL),(168,'210.118.34.168','','0','1','4000','4000',0,NULL,NULL,NULL),(169,'210.118.34.169','','0','2','4000','4000',0,NULL,NULL,NULL),(170,'210.118.34.170','','0','0','4000','4000',0,NULL,NULL,NULL),(171,'210.118.34.171','','0','0','4000','4000',0,NULL,NULL,NULL),(172,'210.118.34.172','','0','0','4000','4000',0,NULL,NULL,NULL),(173,'210.118.34.173','','0','0','4000','4000',1,NULL,NULL,NULL),(174,'210.118.34.174','','0','0','4000','4000',0,NULL,NULL,NULL),(175,'210.118.34.175','','0','3','4000','4000',1,NULL,NULL,NULL),(176,'210.118.34.176','','0','0','4000','4000',0,NULL,NULL,NULL),(177,'210.118.34.177','','0','0','4000','4000',0,NULL,NULL,NULL),(178,'210.118.34.178','','0','0','4000','4000',0,NULL,NULL,NULL),(179,'210.118.34.179','60-A4-4C-B4-F9-B1','0','2','4000','4000',0,NULL,'5900 ',NULL),(180,'210.118.34.180','','0','1','4000','4000',0,NULL,'49153 ',NULL),(181,'210.118.34.181','','0','1','4000','4000',0,NULL,NULL,NULL),(182,'210.118.34.182','','56','3','4000','4000',0,NULL,NULL,NULL),(183,'210.118.34.183','','0','0','4000','4000',0,NULL,NULL,NULL),(184,'210.118.34.184','','0','0','4000','4000',0,NULL,NULL,NULL),(185,'210.118.34.185','','0','0','4000','4000',1,NULL,NULL,NULL),(186,'210.118.34.186','','0','2','4000','4000',0,NULL,NULL,NULL),(187,'210.118.34.187','','0','0','4000','4000',0,NULL,NULL,NULL),(188,'210.118.34.188','','0','1','4000','4000',0,NULL,NULL,NULL),(189,'210.118.34.189','','0','0','4000','4000',0,NULL,NULL,NULL),(190,'210.118.34.190','','0','0','4000','4000',0,NULL,NULL,NULL),(191,'210.118.34.191','','0','0','4000','4000',0,NULL,NULL,NULL),(192,'210.118.34.192','','0','0','4000','4000',1,NULL,NULL,NULL),(193,'210.118.34.193','','0','0','4000','4000',0,NULL,NULL,NULL),(194,'210.118.34.194','','0','0','4000','4000',0,NULL,NULL,NULL),(195,'210.118.34.195','','3','0','4000','4000',1,NULL,NULL,NULL),(196,'210.118.34.196','','0','0','4000','4000',0,NULL,NULL,NULL),(197,'210.118.34.197','','0','0','4000','4000',0,NULL,NULL,NULL),(198,'210.118.34.198','','0','0','4000','4000',1,NULL,NULL,NULL),(199,'210.118.34.199','','0','0','4000','4000',1,NULL,NULL,NULL),(200,'210.118.34.200','','0','0','4000','4000',1,NULL,NULL,NULL),(201,'210.118.34.201','','0','0','4000','4000',1,NULL,NULL,NULL),(202,'210.118.34.202','','22','0','4000','4000',1,NULL,'22 555 ',NULL),(203,'210.118.34.203','','0','0','4000','4000',0,NULL,NULL,NULL),(204,'210.118.34.204','','0','0','4000','4000',1,NULL,NULL,NULL),(205,'210.118.34.205','','0','0','4000','4000',0,NULL,NULL,NULL),(206,'210.118.34.206','','0','0','4000','4000',0,NULL,NULL,NULL),(207,'210.118.34.207','','0','0','4000','4000',0,NULL,NULL,NULL),(208,'210.118.34.208','','0','0','4000','4000',0,NULL,NULL,NULL),(209,'210.118.34.209','','0','0','4000','4000',0,NULL,NULL,NULL),(210,'210.118.34.210','','0','2','4000','4000',0,NULL,NULL,NULL),(211,'210.118.34.211','','0','0','4000','4000',0,NULL,NULL,NULL),(212,'210.118.34.212','','0','0','4000','4000',0,NULL,NULL,NULL),(213,'210.118.34.213','','0','0','4000','4000',1,NULL,NULL,NULL),(214,'210.118.34.214','','0','0','4000','4000',0,NULL,NULL,NULL),(215,'210.118.34.215','','0','0','4000','4000',0,NULL,NULL,NULL),(216,'210.118.34.216','','0','0','4000','4000',0,NULL,NULL,NULL),(217,'210.118.34.217','','0','0','4000','4000',0,NULL,NULL,NULL),(218,'210.118.34.218','','0','0','4000','4000',1,NULL,NULL,NULL),(219,'210.118.34.219','','0','0','4000','4000',0,NULL,NULL,NULL),(220,'210.118.34.220','','0','1','4000','4000',0,NULL,NULL,NULL),(221,'210.118.34.221','','0','0','4000','4000',0,NULL,NULL,NULL),(222,'210.118.34.222','','2','0','4000','4000',1,NULL,'21 80 3306 3389 ',NULL),(223,'210.118.34.223','','0','0','4000','4000',0,NULL,NULL,NULL),(224,'210.118.34.224','','0','5','4000','4000',0,NULL,NULL,NULL),(225,'210.118.34.225','','0','0','4000','4000',0,NULL,NULL,NULL),(226,'210.118.34.226','','0','0','4000','4000',0,NULL,NULL,NULL),(227,'210.118.34.227','','0','0','4000','4000',0,NULL,NULL,NULL),(228,'210.118.34.228','','22','0','4000','4000',1,NULL,NULL,NULL),(229,'210.118.34.229','','0','0','4000','4000',0,NULL,NULL,NULL),(230,'210.118.34.230','','0','0','4000','4000',0,NULL,NULL,NULL),(231,'210.118.34.231','','0','0','4000','4000',0,NULL,NULL,NULL),(232,'210.118.34.232','','10','15','4000','4000',1,NULL,'139 ',NULL),(233,'210.118.34.233','','90','186','4000','4000',1,NULL,'22 139 445 ',NULL),(234,'210.118.34.234','','0','0','4000','4000',0,NULL,NULL,NULL),(235,'210.118.34.235','','0','0','4000','4000',0,NULL,NULL,NULL),(236,'210.118.34.236','','0','0','4000','4000',0,NULL,NULL,NULL),(237,'210.118.34.237','','0','0','4000','4000',0,NULL,NULL,NULL),(238,'210.118.34.238','','0','0','4000','4000',0,NULL,NULL,NULL),(239,'210.118.34.239','','0','0','4000','4000',0,NULL,NULL,NULL),(240,'210.118.34.240','','0','0','4000','4000',0,NULL,NULL,NULL),(241,'210.118.34.241','','0','0','4000','4000',0,NULL,NULL,NULL),(242,'210.118.34.242','','0','0','4000','4000',0,NULL,NULL,NULL),(243,'210.118.34.243','','0','0','4000','4000',0,NULL,NULL,NULL),(244,'210.118.34.244','','0','0','4000','4000',0,NULL,NULL,NULL),(245,'210.118.34.245','','0','0','4000','4000',0,NULL,NULL,NULL),(246,'210.118.34.246','','0','0','4000','4000',0,NULL,NULL,NULL),(247,'210.118.34.247','','0','0','4000','4000',0,NULL,NULL,NULL),(248,'210.118.34.248','','0','0','4000','4000',0,NULL,NULL,NULL),(249,'210.118.34.249','','0','0','4000','4000',0,NULL,NULL,NULL),(250,'210.118.34.250','','0','0','4000','4000',0,NULL,NULL,NULL),(251,'210.118.34.251','','0','0','4000','4000',0,NULL,NULL,NULL),(252,'210.118.34.252','','0','0','4000','4000',0,NULL,'80 3306 3389 ',NULL),(253,'210.118.34.253','','0','0','4000','4000',0,NULL,NULL,NULL),(254,'210.118.34.254','','0','0','4000','4000',0,NULL,NULL,NULL);
/*!40000 ALTER TABLE `ip_data` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-12-02 13:37:12
