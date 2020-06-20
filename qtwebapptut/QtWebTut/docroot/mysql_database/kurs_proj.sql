-- MySQL dump 10.13  Distrib 8.0.20, for Win64 (x86_64)
--
-- Host: localhost    Database: users
-- ------------------------------------------------------
-- Server version	8.0.20

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `accounts`
--

DROP TABLE IF EXISTS `accounts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `accounts` (
  `id` int NOT NULL AUTO_INCREMENT,
  `f_name` char(32) DEFAULT NULL,
  `surname` char(32) DEFAULT NULL,
  `login` char(32) DEFAULT NULL,
  `email` char(32) DEFAULT NULL,
  `pwd` char(128) DEFAULT NULL,
  `pwd_repeat` char(128) DEFAULT NULL,
  `prof_type` int DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `accounts`
--

LOCK TABLES `accounts` WRITE;
/*!40000 ALTER TABLE `accounts` DISABLE KEYS */;
INSERT INTO `accounts` VALUES (1,'andi','handsome','handsomeandi','mymail%40mail.ru','123123','123123',1),(2,'andi','handsome','handsomeandifgfd','gooroochanel3%40gmail.com','123123','123123',1),(3,'fdgdfg','gfdgdfg','evrdsgr','dbsrvre%40mail.ru','123123','123123',1),(4,'andi','handsome','bgfbsfgb','aghanim%40mail.com','123123','123123',1),(5,'andi','handsome','bgfbd','aghanim%40magbfil.com','123123kurs','123123',1),(6,'andi','handsome','gfdgfdg','gfdgd%40gfngf.ru','f744b8f05191ace9f079b615446ff14e09887ec40707f5d97cf126c96b755ed6','123123',1),(7,'andi','handsome','fdgdfgdfg','fdhbfdbfd%40fds.ru','f744b8f05191ace9f079b615446ff14e09887ec40707f5d97cf126c96b755ed6','f744b8f05191ace9f079b615446ff14e09887ec40707f5d97cf126c96b755ed6',1),(8,'andi','handsome','hgfhfgh','dfghfdh%40mail.ru','f744b8f05191ace9f079b615446ff14e09887ec40707f5d97cf126c96b755ed6','f744b8f05191ace9f079b615446ff14e09887ec40707f5d97cf126c96b755ed6',1),(9,'andi','handsome','artur','artur%40mail.ru','f744b8f05191ace9f079b615446ff14e09887ec40707f5d97cf126c96b755ed6','f744b8f05191ace9f079b615446ff14e09887ec40707f5d97cf126c96b755ed6',1),(10,'andi','candy','andicandy','andicandy@mail.ri','123123','123123',1),(11,'jacob','lame','jacoblame','jacob@lame.com','123123','123123',1),(12,'handsomich','andivich','handand','handand@mail.ru','313233313233','313233313233',1),(13,'test','user','testuser','test@mail.ru','313233313233','313233313233',1),(14,'kek','lol','keklol','kek@mail.ru','313233313233','313233313233',1),(15,'newuser','new','usery','new@user.ru','313233313233','313233313233',2),(16,'nik','bal','nikbal','nikbal@mail.ru','313233313233','313233313233',2),(17,'artem','fedorov','arfed','mr.fedorov@mail.ru','313233313233','313233313233',1),(18,'testing','username','testtest','test@test.test','313233313233','313233313233',1),(19,'test','test','test1','test@mailff.ru','313233313233','313233313233',1),(20,'aba','aba','ababa','ababa@aba.ru','313233313233','313233313233',1),(21,'haha','hahaha','hahaclas','haha@clas.ru','313233313233','313233313233',1),(22,'haha','haha','hahaclassic','haha@haha.ru','313233313233','313233313233',1),(23,'papa','mama','papama','pa@ma.ru','313233313233','313233313233',1),(24,'mama','papa','mamapa','mamapa@ma.ru','313233313233','313233313233',1),(25,'imya','familiya','namename','name@name.ru','313233313233','313233313233',1),(26,'ffffff','fffffff','nanana','nanana@nanr.ru','313233313233','313233313233',1),(27,'aaaaa','aaaaa','sasasa','sasa@dmd.ru','313233313233','313233313233',1),(28,'privat','check','privchk','prk@mail.ru','313233313233','313233313233',2),(29,'user','test','front','front@end.ru','313233313233','313233313233',1),(30,'htttp','response','htres','htrrp@mail.ru','313233313233','313233313233',1),(31,'pam','param','pamparam','pam@para.mr','313233313233','313233313233',1),(32,'zdarova','privet','hihihi','hi@hi.hi','313233313233','313233313233',1);
/*!40000 ALTER TABLE `accounts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `categories`
--

DROP TABLE IF EXISTS `categories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `categories` (
  `user_id` int DEFAULT NULL,
  `category_id` int DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL,
  `privacy` int DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `categories`
--

LOCK TABLES `categories` WRITE;
/*!40000 ALTER TABLE `categories` DISABLE KEYS */;
INSERT INTO `categories` VALUES (26,1,'Одежда',1),(26,2,'Электроника',1),(26,3,'Автомобили',1),(26,4,'Недвижимость',1),(26,5,'Другое',1),(27,1,'Одежда',1),(27,2,'Электроника',1),(27,3,'Автомобили',1),(27,4,'Недвижимость',1),(27,5,'Другое',1),(26,6,'Часы',2),(26,7,'Кроссовки',2),(26,8,'Тестовая',1),(28,1,'Одежда',1),(28,2,'Электроника',1),(28,3,'Автомобили',1),(28,4,'Недвижимость',1),(28,5,'Другое',1),(29,1,'Одежда',1),(29,2,'Электроника',1),(29,3,'Автомобили',1),(29,4,'Недвижимость',1),(29,5,'Другое',1),(30,1,'Одежда',1),(30,2,'Электроника',1),(30,3,'Автомобили',1),(30,4,'Недвижимость',1),(30,5,'Другое',1),(31,1,'Одежда',1),(31,2,'Электроника',1),(31,3,'Автомобили',1),(31,4,'Недвижимость',1),(31,5,'Другое',1),(32,1,'Одежда',1),(32,2,'Электроника',1),(32,3,'Автомобили',1),(32,4,'Недвижимость',1),(32,5,'Другое',1),(26,9,'e_boy',1);
/*!40000 ALTER TABLE `categories` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `items`
--

DROP TABLE IF EXISTS `items`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `items` (
  `id` int NOT NULL AUTO_INCREMENT,
  `title` varchar(255) DEFAULT NULL,
  `descript` text,
  `photo` varchar(255) DEFAULT NULL,
  `price` int DEFAULT NULL,
  `link` varchar(500) DEFAULT NULL,
  `category` int DEFAULT NULL,
  `user_id` int DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `items`
--

LOCK TABLES `items` WRITE;
/*!40000 ALTER TABLE `items` DISABLE KEYS */;
INSERT INTO `items` VALUES (14,'First Item(Updated)','First Description(Updated)','1592328145649Programming-Wallpapers-26-2560-x-1600.png',123,'link_update.com',1,14),(22,'Clothes','I love this clothes','1592604624420421743-svetik.jpg',399,'my-clother.com',1,26),(23,'New Item','New Description','1592477812942271136.jpg',199,'teeeest.com',4,26),(25,'fdgjdkfg','rdgdfgdf','1592494418355272588.jpg',432423,'gfdgdfg',8,26),(26,'check privacy','check prvcy','1592495029678272588.jpg',300,'ll.ru',1,28),(27,'not_privat','not private desc','1592604355556272588.jpg',199,'notpriv.link',2,26),(28,'Kora','avatar','1592600385076legendofkorra-e1588738276111.jpg',9999,'korra.ru',9,26),(29,'hahhahah','hahahaha','1592600760458legendofkorra-e1588738276111.jpg',929292,'hahaha',9,26),(30,'check','mate','1592600800823focus.jpg',333,'wow',9,26);
/*!40000 ALTER TABLE `items` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-06-20  2:10:21
