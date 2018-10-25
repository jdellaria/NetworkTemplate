CREATE DATABASE  IF NOT EXISTS `Music` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `Music`;
-- MySQL dump 10.13  Distrib 5.5.47, for debian-linux-gnu (i686)
--
-- Host: 127.0.0.1    Database: Music
-- ------------------------------------------------------
-- Server version	5.5.47-0ubuntu0.14.04.1

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
-- Table structure for table `Albums`
--

DROP TABLE IF EXISTS `Albums`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Albums` (
  `Album` char(255) NOT NULL,
  `AlbumId` int(11) NOT NULL AUTO_INCREMENT,
  `refId` int(11) DEFAULT NULL,
  `DateAdded` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `LastSelected` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `Cover` char(255) DEFAULT NULL,
  `ArtistName` char(255) DEFAULT NULL,
  `SongYear` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`AlbumId`)
) ENGINE=MyISAM AUTO_INCREMENT=3727 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ArtistAlbum`
--

DROP TABLE IF EXISTS `ArtistAlbum`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ArtistAlbum` (
  `ArtistId` int(11) NOT NULL,
  `AlbumId` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `Artists`
--

DROP TABLE IF EXISTS `Artists`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Artists` (
  `Artist` char(150) NOT NULL,
  `ArtistId` int(11) NOT NULL AUTO_INCREMENT,
  `refId` int(11) DEFAULT NULL,
  PRIMARY KEY (`ArtistId`)
) ENGINE=MyISAM AUTO_INCREMENT=1588 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `AutoSongQuery`
--

DROP TABLE IF EXISTS `AutoSongQuery`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `AutoSongQuery` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Title` char(100) NOT NULL,
  `Status` char(20) NOT NULL,
  `SQLStatement` varchar(2000) NOT NULL,
  `rowOffset` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=16 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `DiffTime`
--

DROP TABLE IF EXISTS `DiffTime`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `DiffTime` (
  `Idy` bigint(20) NOT NULL AUTO_INCREMENT,
  `id` int(10) unsigned NOT NULL DEFAULT '0',
  `songID` int(10) unsigned NOT NULL DEFAULT '0',
  `diff` bigint(21) DEFAULT NULL,
  `Name` char(255) DEFAULT NULL,
  `Artist` char(150) DEFAULT NULL,
  `Album` char(255) DEFAULT NULL,
  `BeginPlayTime` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `Location` char(255) DEFAULT NULL,
  PRIMARY KEY (`Idy`)
) ENGINE=InnoDB AUTO_INCREMENT=763627 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `playq`
--

DROP TABLE IF EXISTS `playq`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `playq` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `songID` int(10) unsigned NOT NULL DEFAULT '0',
  `BeginPlayTime` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `EndPlayTime` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `Status` varchar(20) DEFAULT 'In Queue',
  `RequestType` varchar(20) DEFAULT 'Automatic',
  `RequestTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `Arrangement` int(10) unsigned NOT NULL DEFAULT '99999999',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=833489 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `presonglibrary`
--

DROP TABLE IF EXISTS `presonglibrary`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `presonglibrary` (
  `Name` char(255) DEFAULT NULL,
  `Artist` char(150) DEFAULT NULL,
  `Composer` char(100) DEFAULT NULL,
  `Album` char(255) DEFAULT NULL,
  `Grouping` char(100) DEFAULT NULL,
  `Genre` char(100) DEFAULT NULL,
  `Size` int(11) DEFAULT NULL,
  `SongTime` int(11) DEFAULT NULL,
  `DiscNumber` int(11) DEFAULT NULL,
  `DiscCount` int(11) DEFAULT NULL,
  `TrackNumber` int(11) DEFAULT NULL,
  `TrackCount` int(11) DEFAULT NULL,
  `SongYear` char(20) DEFAULT NULL,
  `DateModified` datetime DEFAULT NULL,
  `DateAdded` datetime DEFAULT NULL,
  `BitRate` int(11) DEFAULT NULL,
  `SampleRate` int(11) DEFAULT NULL,
  `VolumeAdjustment` int(11) DEFAULT NULL,
  `Kind` char(40) DEFAULT NULL,
  `Equalizer` char(20) DEFAULT NULL,
  `Comments` char(100) DEFAULT NULL,
  `PlayCount` int(11) DEFAULT '0',
  `LastPlayed` datetime DEFAULT NULL,
  `MyRating` int(11) DEFAULT NULL,
  `Location` char(255) DEFAULT NULL,
  `SongIndex` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Catalog` char(20) DEFAULT NULL,
  `ArtistId` int(11) NOT NULL,
  `AlbumId` int(11) NOT NULL,
  PRIMARY KEY (`SongIndex`)
) ENGINE=MyISAM AUTO_INCREMENT=73567 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `songlibrary`
--

DROP TABLE IF EXISTS `songlibrary`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `songlibrary` (
  `Name` char(255) DEFAULT NULL,
  `Artist` char(150) DEFAULT NULL,
  `Composer` char(100) DEFAULT NULL,
  `Album` char(255) DEFAULT NULL,
  `Grouping` char(100) DEFAULT NULL,
  `Genre` char(100) DEFAULT NULL,
  `Size` int(11) DEFAULT NULL,
  `SongTime` int(11) DEFAULT NULL,
  `DiscNumber` int(11) DEFAULT NULL,
  `DiscCount` int(11) DEFAULT NULL,
  `TrackNumber` int(11) DEFAULT NULL,
  `TrackCount` int(11) DEFAULT NULL,
  `SongYear` char(20) DEFAULT NULL,
  `DateModified` datetime DEFAULT NULL,
  `DateAdded` datetime DEFAULT NULL,
  `BitRate` int(11) DEFAULT NULL,
  `SampleRate` int(11) DEFAULT NULL,
  `VolumeAdjustment` int(11) DEFAULT NULL,
  `Kind` char(40) DEFAULT NULL,
  `Equalizer` char(20) DEFAULT NULL,
  `Comments` char(100) DEFAULT NULL,
  `PlayCount` int(11) DEFAULT '0',
  `LastPlayed` datetime DEFAULT NULL,
  `MyRating` int(11) DEFAULT NULL,
  `Location` char(255) DEFAULT NULL,
  `SongIndex` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Catalog` char(20) DEFAULT NULL,
  `ArtistId` int(11) NOT NULL,
  `AlbumId` int(11) NOT NULL,
  PRIMARY KEY (`SongIndex`)
) ENGINE=MyISAM AUTO_INCREMENT=68084 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-10-03 15:10:23
