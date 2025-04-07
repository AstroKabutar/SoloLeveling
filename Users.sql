-- MySQL dump 10.13  Distrib 9.1.0, for Linux (aarch64)
--
-- Host: localhost    Database: Users
-- ------------------------------------------------------
-- Server version	9.1.0

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
-- Table structure for table `importance`
--

DROP TABLE IF EXISTS `importance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `importance` (
  `class` varchar(1) NOT NULL,
  `xp_gain` double NOT NULL,
  PRIMARY KEY (`class`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `importance`
--

LOCK TABLES `importance` WRITE;
/*!40000 ALTER TABLE `importance` DISABLE KEYS */;
INSERT INTO `importance` VALUES ('A',8),('B',6),('C',4),('D',2),('E',1),('S',10);
/*!40000 ALTER TABLE `importance` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `levels`
--

DROP TABLE IF EXISTS `levels`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `levels` (
  `player_id` int DEFAULT NULL,
  `level` int NOT NULL,
  `xp_required` double DEFAULT NULL,
  KEY `player_id` (`player_id`),
  CONSTRAINT `levels_ibfk_1` FOREIGN KEY (`player_id`) REFERENCES `players` (`player_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `levels`
--

LOCK TABLES `levels` WRITE;
/*!40000 ALTER TABLE `levels` DISABLE KEYS */;
INSERT INTO `levels` VALUES (1,2,30),(2,2,30),(3,2,30),(4,3,60),(5,2,30),(6,2,30);
/*!40000 ALTER TABLE `levels` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player_progression`
--

DROP TABLE IF EXISTS `player_progression`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `player_progression` (
  `player_id` int DEFAULT NULL,
  `current_level` int DEFAULT NULL,
  `current_xp` double DEFAULT NULL,
  KEY `player_id` (`player_id`),
  CONSTRAINT `player_progression_ibfk_1` FOREIGN KEY (`player_id`) REFERENCES `players` (`player_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player_progression`
--

LOCK TABLES `player_progression` WRITE;
/*!40000 ALTER TABLE `player_progression` DISABLE KEYS */;
INSERT INTO `player_progression` VALUES (1,1,3.48),(2,1,3.48),(3,1,3.48),(4,1,3.48),(5,1,3.48),(6,1,3.48);
/*!40000 ALTER TABLE `player_progression` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `players`
--

DROP TABLE IF EXISTS `players`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `players` (
  `player_id` int NOT NULL AUTO_INCREMENT,
  `player_name` varchar(200) DEFAULT NULL,
  `dob` date DEFAULT NULL,
  `created_at` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`player_id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `players`
--

LOCK TABLES `players` WRITE;
/*!40000 ALTER TABLE `players` DISABLE KEYS */;
INSERT INTO `players` VALUES (1,'dd evil','5268-02-03','Mon 10 Mar 21:30:26 PDT 2025'),(2,'Shahin','1999-06-06','Mon 10 Mar 21:45:05 PDT 2025'),(3,'jj evil','8745-09-09','Mon 10 Mar 21:47:27 PDT 2025'),(4,'ii','8523-09-05','Mon 10 Mar 21:48:48 PDT 2025'),(5,'kk','5555-09-09','Mon 10 Mar 21:50:35 PDT 2025'),(6,'jjkk','7852-09-08','Tue 11 Mar 00:47:07 PDT 2025');
/*!40000 ALTER TABLE `players` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tasks`
--

DROP TABLE IF EXISTS `tasks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tasks` (
  `player_id` int DEFAULT NULL,
  `task_id` int NOT NULL AUTO_INCREMENT,
  `tasks` varchar(5000) DEFAULT NULL,
  `importance` varchar(1) DEFAULT NULL,
  `status` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`task_id`),
  KEY `player_id` (`player_id`),
  KEY `importance` (`importance`),
  CONSTRAINT `tasks_ibfk_1` FOREIGN KEY (`player_id`) REFERENCES `players` (`player_id`),
  CONSTRAINT `tasks_ibfk_2` FOREIGN KEY (`importance`) REFERENCES `importance` (`class`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tasks`
--

LOCK TABLES `tasks` WRITE;
/*!40000 ALTER TABLE `tasks` DISABLE KEYS */;
INSERT INTO `tasks` VALUES (1,1,'i want to go home home','E','INCOMPLETE'),(1,2,'ulala','A','INCOMPLETE'),(1,3,'This is a change of task buddy','S','INCOMPLETE'),(1,4,'d','S','INCOMPLETE'),(1,5,'fgg','A','INCOMPLETE'),(4,6,'i want to go home 1','A','INCOMPLETE'),(4,7,'i want to go home 2','S','INCOMPLETE'),(4,8,'i want to go home 3','E','INCOMPLETE'),(4,9,'I want to go home 4','C','INCOMPLETE'),(4,10,'chichi ko bhagana hai','S','COMPLETED'),(4,11,'ab nai bhagana','A','INCOMPLETE'),(4,12,'i want to sleep','S','INCOMPLETE'),(6,13,'age piche upar neeche','S','INCOMPLETE'),(6,14,'chalte chala mai ye dunia me','B','COMPLETED'),(6,15,'Ye dunia hai baddi zalim','E','INCOMPLETE');
/*!40000 ALTER TABLE `tasks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `xp_transactions`
--

DROP TABLE IF EXISTS `xp_transactions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `xp_transactions` (
  `player_id` int DEFAULT NULL,
  `xp_gained` double DEFAULT NULL,
  `transaction_date` varchar(50) DEFAULT NULL,
  `tasks_completed` varchar(5000) DEFAULT NULL,
  KEY `player_id` (`player_id`),
  CONSTRAINT `xp_transactions_ibfk_1` FOREIGN KEY (`player_id`) REFERENCES `players` (`player_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `xp_transactions`
--

LOCK TABLES `xp_transactions` WRITE;
/*!40000 ALTER TABLE `xp_transactions` DISABLE KEYS */;
INSERT INTO `xp_transactions` VALUES (1,3.48,'Mon 10 Mar 21:30:26 PDT 2025','Welcome Player'),(2,3.48,'Mon 10 Mar 21:45:05 PDT 2025','Welcome Player'),(3,3.48,'Mon 10 Mar 21:47:27 PDT 2025','Welcome Player'),(4,3.48,'Mon 10 Mar 21:48:48 PDT 2025','Welcome Player'),(5,3.48,'Mon 10 Mar 21:50:35 PDT 2025','Welcome Player'),(4,52.66,'dsfsdf dsfsdf','done'),(4,52.66,'dsfsdf dsfsdf','done'),(6,3.48,'Tue 11 Mar 00:47:07 PDT 2025','Welcome Player'),(6,3.6888,'Tue 11 Mar 00:47:50 PDT 2025','chalte');
/*!40000 ALTER TABLE `xp_transactions` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-03-11  8:05:23
