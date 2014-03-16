-- phpMyAdmin SQL Dump
-- version 4.0.4.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Mar 16, 2014 at 03:41 AM
-- Server version: 5.5.32
-- PHP Version: 5.4.16

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `dttt_game`
--
CREATE DATABASE IF NOT EXISTS `dttt_game` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `dttt_game`;

-- --------------------------------------------------------

--
-- Table structure for table `multiresult`
--

CREATE TABLE IF NOT EXISTS `multiresult` (
  `multiresultid` varchar(20) NOT NULL,
  `wins` int(11) NOT NULL,
  `loses` int(11) NOT NULL,
  `score` int(11) NOT NULL,
  PRIMARY KEY (`multiresultid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `multiresult`
--

INSERT INTO `multiresult` (`multiresultid`, `wins`, `loses`, `score`) VALUES
('Fb1[B@10fb7fb', 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `singleresult`
--

CREATE TABLE IF NOT EXISTS `singleresult` (
  `singleresultid` varchar(20) NOT NULL,
  `wins` int(11) NOT NULL,
  `loses` int(11) NOT NULL,
  `score` int(11) NOT NULL,
  PRIMARY KEY (`singleresultid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `singleresult`
--

INSERT INTO `singleresult` (`singleresultid`, `wins`, `loses`, `score`) VALUES
('Fb1[B@1e34235', 0, 0, 2222);

-- --------------------------------------------------------

--
-- Table structure for table `subject`
--

CREATE TABLE IF NOT EXISTS `subject` (
  `subjectid` varchar(20) NOT NULL,
  `name` varchar(50) NOT NULL,
  `active` tinyint(1) NOT NULL,
  `numbersentence` int(11) NOT NULL,
  `prefix` varchar(20) NOT NULL,
  PRIMARY KEY (`subjectid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `subject`
--

INSERT INTO `subject` (`subjectid`, `name`, `active`, `numbersentence`, `prefix`) VALUES
('1', 'lich su', 1, 10, 'lic'),
('2', 'van hoc', 1, 20, 'van'),
('3', 'toan hoc', 1, 30, 'toa'),
('4', 'hoa hoc', 1, 40, 'hoa');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE IF NOT EXISTS `user` (
  `userid` varchar(50) NOT NULL,
  `name` varchar(50) DEFAULT NULL,
  `avatar` varchar(100) DEFAULT NULL,
  `singleresultid` varchar(20) NOT NULL,
  `multiresultid` varchar(20) NOT NULL,
  `jewelry` int(11) NOT NULL,
  PRIMARY KEY (`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`userid`, `name`, `avatar`, `singleresultid`, `multiresultid`, `jewelry`) VALUES
('Fb1', 'PhamLong', '', 'Fb1[B@1e34235', 'Fb1[B@10fb7fb', 200);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
