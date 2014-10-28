-- MySQL dump 10.14  Distrib 5.5.32-MariaDB, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32-MariaDB

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
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(11) NOT NULL,
  `type` varchar(1) COLLATE utf8_unicode_ci NOT NULL,
  `symbol` varchar(5) COLLATE utf8_unicode_ci NOT NULL,
  `amount` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (14,'B','DIS',10,69,'2013-11-06 04:09:38'),(14,'B','DIS',10,69,'2013-11-06 04:10:07'),(14,'B','DIS',10,69,'2013-11-06 04:23:26'),(14,'B','DIS',2,69,'2013-11-06 04:39:27'),(14,'B','GE',15,27,'2013-11-06 22:07:41'),(14,'B','GE',15,27,'2013-11-06 22:08:23'),(14,'S','DIS',10,69,'2013-11-06 22:46:53'),(14,'S','DIS',1,69,'2013-11-06 22:47:36'),(14,'B','GOOG',1,1023,'2013-11-06 22:47:56'),(14,'S','DIS',4,69,'2013-11-06 22:57:41'),(14,'S','GE',5,27,'2013-11-07 04:20:38'),(14,'S','GOOG',5,1023,'2013-11-07 04:23:10'),(14,'S','GOOG',5,1023,'2013-11-07 04:24:25'),(14,'S','GOOG',5,1023,'2013-11-07 04:24:58'),(14,'S','GOOG',5,1023,'2013-11-07 04:25:42'),(14,'B','DIS',1,69,'2013-11-07 04:49:06'),(14,'B','DIS',0,69,'2013-11-07 04:49:15'),(14,'S','DIS',0,69,'2013-11-07 04:51:51'),(14,'S','DIS',1,69,'2013-11-07 04:55:41'),(14,'S','GOOG',25,1023,'2013-11-07 05:00:06'),(14,'B','GOOG',1,1008,'2013-11-08 02:44:39'),(14,'S','GOOG',5,1008,'2013-11-08 03:05:41'),(14,'B','GOOG ',5,1008,'2013-11-08 03:06:36'),(14,'S','GOOG',5,1008,'2013-11-08 03:07:04'),(14,'S','GOOG',5,1008,'2013-11-08 03:09:16'),(14,'B','GOOG',15,1008,'2013-11-08 03:12:03');
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolios`
--

DROP TABLE IF EXISTS `portfolios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolios` (
  `id` int(11) NOT NULL,
  `symbol` varchar(5) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id`,`symbol`),
  KEY `shares` (`shares`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolios`
--

LOCK TABLES `portfolios` WRITE;
/*!40000 ALTER TABLE `portfolios` DISABLE KEYS */;
INSERT INTO `portfolios` VALUES (2,'KSU',3),(1,'DIS',5),(14,'GOOG',7),(1,'KSU',21),(14,'DIS',58),(14,'GE',130);
/*!40000 ALTER TABLE `portfolios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$yoWuimUO$Y7fqisPvz6VHHryMzLc6i0',10000.0000),(2,'hirschhorn','$1$yoWuimUO$Y7fqisPvz6VHHryMzLc6i0',10000.0000),(3,'jharvard','$1$yoWuimUO$Y7fqisPvz6VHHryMzLc6i0',10000.0000),(4,'malan','$1$yoWuimUO$Y7fqisPvz6VHHryMzLc6i0',10000.0000),(5,'milo','$1$yoWuimUO$Y7fqisPvz6VHHryMzLc6i0',10000.0000),(6,'skroob','$1$yoWuimUO$Y7fqisPvz6VHHryMzLc6i0',10000.0000),(7,'zamyla','$1$yoWuimUO$Y7fqisPvz6VHHryMzLc6i0',10000.0000),(14,'jake','$1$yoWuimUO$Y7fqisPvz6VHHryMzLc6i0',42182.8000);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-11-07 22:40:20
