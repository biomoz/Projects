-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Dec 12, 2023 at 11:24 PM
-- Server version: 10.4.27-MariaDB
-- PHP Version: 8.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `oc_webshop`
--
CREATE DATABASE IF NOT EXISTS `oc_webshop` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `oc_webshop`;

-- --------------------------------------------------------

--
-- Table structure for table `orderitems`
--

CREATE TABLE `orderitems` (
  `OrderItemID` int(11) NOT NULL,
  `ProductID` int(11) DEFAULT NULL,
  `OrderID` int(11) DEFAULT NULL,
  `Quantity` int(11) NOT NULL,
  `TotalPrice` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `orderitems`
--

INSERT INTO `orderitems` (`OrderItemID`, `ProductID`, `OrderID`, `Quantity`, `TotalPrice`) VALUES
(1, 1, 1, 2, '119.98'),
(2, 4, 1, 1, '39.99'),
(3, 8, 1, 3, '209.97'),
(4, 4, 2, 1, '39.99'),
(5, 3, 2, 2, '139.98'),
(6, 7, 2, 3, '14.97'),
(7, 8, 3, 2, '139.98'),
(8, 6, 3, 2, '119.98'),
(9, 7, 3, 1, '4.99');

-- --------------------------------------------------------

--
-- Table structure for table `orders`
--

CREATE TABLE `orders` (
  `OrderID` int(11) NOT NULL,
  `UserID` int(11) DEFAULT NULL,
  `OrderDate` date DEFAULT NULL,
  `OrderPrice` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `orders`
--

INSERT INTO `orders` (`OrderID`, `UserID`, `OrderDate`, `OrderPrice`) VALUES
(1, 1, '2023-12-12', '369.94'),
(2, 2, '2023-12-12', '194.94'),
(3, 3, '2023-12-12', '264.95');

-- --------------------------------------------------------

--
-- Table structure for table `products`
--

CREATE TABLE `products` (
  `ProductID` int(11) NOT NULL,
  `ProductName` varchar(255) NOT NULL,
  `ProductImage` varchar(255) DEFAULT NULL,
  `UnitPrice` decimal(10,2) NOT NULL,
  `Description` text DEFAULT NULL,
  `Active` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `products`
--

INSERT INTO `products` (`ProductID`, `ProductName`, `ProductImage`, `UnitPrice`, `Description`, `Active`) VALUES
(1, 'The Legend of Zelda: Breath of the Wild', 'https://upload.wikimedia.org/wikipedia/en/c/c6/The_Legend_of_Zelda_Breath_of_the_Wild.jpg', '59.99', 'Embark on an epic adventure in Hyrule. Solve puzzles, defeat enemies, and explore stunning landscapes.', 1),
(3, 'Assassin\'s Creed Valhalla', 'https://m.media-amazon.com/images/I/91lmTAVXgHL._AC_UF1000,1000_QL80_.jpg', '69.99', 'Lead your Viking clan to glory. Explore the stunning world of Norway and England during the Dark Ages.', 1),
(4, 'Overwatch', 'https://upload.wikimedia.org/wikipedia/en/5/51/Overwatch_cover_art.jpg', '39.99', 'Join the fight for the future in this team-based shooter. Choose from a diverse cast of heroes and engage in intense battles.', 1),
(5, 'Minecraft', 'https://upload.wikimedia.org/wikipedia/en/5/51/Minecraft_cover.png', '29.99', 'Build, explore, and survive in an open-world sandbox. Create your own adventures in this pixelated universe.', 0),
(6, 'Cyberpunk 2077', 'https://upload.wikimedia.org/wikipedia/en/9/9f/Cyberpunk_2077_box_art.jpg', '59.99', 'Enter the dystopian future of Night City. Customize your character and navigate a world filled with intrigue.', 1),
(7, 'Among Us', 'https://upload.wikimedia.org/wikipedia/en/9/9a/Among_Us_cover_art.jpg', '4.99', 'Join your crewmates for an online multiplayer game of teamwork and betrayal. Can you identify the impostors before it\'s too late?', 1),
(8, 'Elden Ring', 'https://upload.wikimedia.org/wikipedia/en/thumb/b/b9/Elden_Ring_Box_art.jpg/220px-Elden_Ring_Box_art.jpg', '69.99', 'Immerse yourself in a dark fantasy world created by Hidetaka Miyazaki and George R. R. Martin. Explore vast landscapes and encounter mythical creatures.', 1);

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `UserID` int(11) NOT NULL,
  `Username` varchar(255) NOT NULL,
  `Password` varchar(255) NOT NULL,
  `UserType` varchar(20) NOT NULL,
  `Email` varchar(255) NOT NULL,
  `FirstName` varchar(255) DEFAULT NULL,
  `LastName` varchar(255) DEFAULT NULL,
  `Active` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`UserID`, `Username`, `Password`, `UserType`, `Email`, `FirstName`, `LastName`, `Active`) VALUES
(1, 'admin', '$2y$10$iV1H02BLnrMJDo/0HUmNo.uNzgd/dE.JblNW0xRggWUSwG5845lq6', 'Administrator', 'admin@gmail.com', 'Omer', 'Celebi', 1),
(2, 'employee', '$2y$10$1zqBOn8.t.zxXmmMQsG8reqfiqmgi5MI.uz6YCfC6ow33hwYryj7W', 'Employee', 'emp@gmail.com', 'Robert', 'Duck', 1),
(3, 'user', '$2y$10$17Whdoz3YwGM0wxBLIM3s.fQNhkR5cXPmb1JFilbamD.tDiNPKISO', 'Registered', 'user@gmail.com', 'Daniel', 'Smith', 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `orderitems`
--
ALTER TABLE `orderitems`
  ADD PRIMARY KEY (`OrderItemID`),
  ADD KEY `ProductID` (`ProductID`),
  ADD KEY `OrderID` (`OrderID`);

--
-- Indexes for table `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`OrderID`),
  ADD KEY `UserID` (`UserID`);

--
-- Indexes for table `products`
--
ALTER TABLE `products`
  ADD PRIMARY KEY (`ProductID`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`UserID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `orderitems`
--
ALTER TABLE `orderitems`
  MODIFY `OrderItemID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=19;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `orderitems`
--
ALTER TABLE `orderitems`
  ADD CONSTRAINT `orderitems_ibfk_1` FOREIGN KEY (`ProductID`) REFERENCES `products` (`ProductID`),
  ADD CONSTRAINT `orderitems_ibfk_2` FOREIGN KEY (`OrderID`) REFERENCES `orders` (`OrderID`);

--
-- Constraints for table `orders`
--
ALTER TABLE `orders`
  ADD CONSTRAINT `orders_ibfk_1` FOREIGN KEY (`UserID`) REFERENCES `users` (`UserID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
