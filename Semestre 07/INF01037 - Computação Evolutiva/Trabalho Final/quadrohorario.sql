-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tempo de Geração: 17/04/2013 às 23h13min
-- Versão do Servidor: 5.5.29
-- Versão do PHP: 5.3.10-1ubuntu3.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Banco de Dados: `quadrohorario`
--

DELIMITER $$
--
-- Procedimentos
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `cruzamento`( db CHAR(64), tbl CHAR(64), col CHAR(64) )
BEGIN
  DECLARE datadelim CHAR(1) DEFAULT '"';
  DECLARE singlequote CHAR(1) DEFAULT CHAR(39);
  DECLARE comma CHAR(1) DEFAULT ',';
  SET @sqlmode = (SELECT @@sql_mode);
  SET @@sql_mode='';
  SET @sql = CONCAT( 'SELECT DISTINCT CONCAT(', singlequote,
                     ',SUM(IF(', col, ' = ', datadelim, singlequote, comma,
                     col, comma, singlequote, datadelim, comma, '1,0)) AS `', 
                     singlequote, comma, col, comma, singlequote, '`', singlequote, 
                     ') AS Turmas FROM ', db, '.', tbl,
                     ' WHERE ', col, ' IS NOT NULL' );
  -- UNCOMMENT TO SEE THE MIDLEVEL CODE:
  -- SELECT @sql; 
  PREPARE stmt FROM @sql;
  EXECUTE stmt;
  DROP PREPARE stmt;
  SET @@sql_mode=@sqlmode;
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Estrutura da tabela `disciplinas`
--

CREATE TABLE IF NOT EXISTS `disciplinas` (
  `ID_DISC` int(11) NOT NULL AUTO_INCREMENT,
  `disciplina` varchar(100) NOT NULL,
  `abreviacao` varchar(10) DEFAULT NULL,
  `observacao` varchar(255) DEFAULT NULL,
  `ID_INST` int(11) NOT NULL,
  PRIMARY KEY (`ID_DISC`),
  KEY `PK_INSTITUICAO` (`ID_INST`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=18 ;

--
-- Extraindo dados da tabela `disciplinas`
--

INSERT INTO `disciplinas` (`ID_DISC`, `disciplina`, `abreviacao`, `observacao`, `ID_INST`) VALUES
(1, 'Biologia', 'BIO', NULL, 1),
(2, 'Ciências', 'CIE', NULL, 1),
(3, 'Educação Artística', 'EDART', NULL, 1),
(4, 'Educação Física', 'EDFIS', NULL, 1),
(5, 'Espanhol', 'ESP', NULL, 1),
(6, 'Filosofia', 'FILO', NULL, 1),
(7, 'Física', 'FIS', NULL, 1),
(8, 'Geografia', 'GEO', NULL, 1),
(9, 'História', 'HIS', NULL, 1),
(10, 'Inglês', 'ING', NULL, 1),
(11, 'Literatura', 'LIT', NULL, 1),
(12, 'Matemática', 'MAT', NULL, 1),
(13, 'Português', 'PORT', NULL, 1),
(14, 'Química', 'QUI', NULL, 1),
(15, 'Redação', 'RED', NULL, 1),
(16, 'Ensino Religioso', 'ENSREL', NULL, 1),
(17, 'Sociologia', 'SOC', NULL, 1);

-- --------------------------------------------------------

--
-- Estrutura da tabela `disponibilidade`
--

CREATE TABLE IF NOT EXISTS `disponibilidade` (
  `ID_DISPO` int(11) NOT NULL AUTO_INCREMENT,
  `ID_PROFESSOR` int(11) NOT NULL,
  `diaok` int(11) NOT NULL,
  `periodook` int(11) NOT NULL,
  PRIMARY KEY (`ID_DISPO`),
  KEY `ID_PROFESSOR` (`ID_PROFESSOR`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=180 ;

--
-- Extraindo dados da tabela `disponibilidade`
--

INSERT INTO `disponibilidade` (`ID_DISPO`, `ID_PROFESSOR`, `diaok`, `periodook`) VALUES
(1, 15, 1, 0),
(2, 15, 1, 1),
(3, 15, 1, 2),
(4, 15, 1, 3),
(5, 15, 1, 4),
(6, 15, 3, 0),
(7, 15, 3, 1),
(8, 15, 3, 2),
(9, 15, 3, 3),
(10, 15, 3, 4),
(11, 15, 4, 3),
(12, 15, 4, 4),
(13, 1, 2, 0),
(14, 1, 2, 1),
(15, 1, 2, 2),
(16, 1, 2, 3),
(17, 1, 2, 4),
(18, 1, 4, 0),
(19, 1, 4, 1),
(20, 1, 4, 2),
(21, 1, 4, 3),
(22, 1, 4, 4),
(23, 2, 0, 0),
(24, 2, 0, 1),
(25, 2, 0, 2),
(26, 2, 0, 3),
(27, 2, 0, 4),
(28, 2, 1, 0),
(29, 2, 1, 1),
(30, 2, 1, 2),
(31, 2, 1, 3),
(32, 2, 1, 4),
(33, 2, 2, 0),
(34, 2, 2, 1),
(35, 2, 2, 2),
(36, 2, 2, 3),
(37, 2, 2, 4),
(38, 3, 0, 0),
(39, 3, 0, 1),
(40, 3, 0, 2),
(41, 3, 0, 3),
(42, 3, 0, 4),
(43, 3, 3, 0),
(44, 3, 3, 1),
(45, 3, 3, 2),
(46, 3, 3, 3),
(47, 3, 3, 4),
(48, 3, 4, 0),
(49, 3, 4, 1),
(50, 3, 4, 2),
(51, 3, 4, 3),
(52, 3, 4, 4),
(53, 4, 0, 0),
(54, 4, 0, 1),
(55, 4, 0, 2),
(56, 4, 0, 3),
(57, 4, 0, 4),
(58, 4, 2, 0),
(59, 4, 2, 1),
(60, 4, 2, 2),
(61, 4, 2, 3),
(62, 4, 2, 4),
(63, 4, 3, 0),
(64, 4, 3, 1),
(65, 4, 3, 2),
(66, 4, 3, 3),
(67, 4, 3, 4),
(68, 4, 4, 0),
(69, 4, 4, 1),
(70, 4, 4, 2),
(71, 5, 1, 0),
(72, 5, 1, 1),
(73, 5, 1, 2),
(74, 5, 1, 3),
(75, 5, 1, 4),
(76, 5, 3, 0),
(77, 5, 3, 1),
(78, 5, 3, 2),
(79, 5, 3, 3),
(80, 5, 3, 4),
(81, 6, 0, 0),
(82, 6, 0, 1),
(83, 6, 0, 2),
(84, 6, 0, 3),
(85, 6, 0, 4),
(86, 6, 1, 0),
(87, 6, 1, 1),
(88, 6, 1, 2),
(89, 6, 1, 3),
(90, 6, 1, 4),
(91, 6, 2, 0),
(92, 6, 2, 1),
(93, 6, 2, 2),
(94, 6, 2, 3),
(95, 6, 2, 4),
(96, 6, 4, 0),
(97, 6, 4, 1),
(98, 6, 4, 2),
(99, 6, 4, 3),
(100, 6, 4, 4),
(101, 7, 0, 0),
(102, 7, 0, 1),
(103, 7, 0, 2),
(104, 7, 0, 3),
(105, 7, 0, 4),
(106, 7, 1, 0),
(107, 7, 1, 1),
(108, 7, 1, 2),
(109, 7, 1, 3),
(110, 7, 1, 4),
(111, 7, 3, 2),
(112, 7, 3, 3),
(113, 7, 3, 4),
(114, 8, 0, 0),
(115, 8, 0, 1),
(116, 8, 0, 2),
(117, 8, 0, 3),
(118, 8, 0, 4),
(119, 8, 2, 0),
(120, 8, 2, 1),
(121, 8, 2, 2),
(122, 8, 2, 3),
(123, 8, 2, 4),
(124, 9, 1, 0),
(125, 9, 1, 1),
(126, 9, 1, 2),
(127, 9, 1, 3),
(128, 9, 1, 4),
(129, 9, 3, 0),
(130, 9, 3, 1),
(131, 9, 3, 2),
(132, 9, 3, 3),
(133, 9, 3, 4),
(134, 10, 1, 0),
(135, 10, 1, 1),
(136, 10, 1, 2),
(137, 10, 1, 3),
(138, 10, 1, 4),
(139, 10, 4, 0),
(140, 10, 4, 1),
(141, 10, 4, 2),
(142, 11, 0, 0),
(143, 11, 0, 1),
(144, 11, 0, 2),
(145, 11, 0, 3),
(146, 11, 0, 4),
(147, 11, 2, 0),
(148, 11, 2, 1),
(149, 11, 2, 2),
(150, 11, 2, 3),
(151, 11, 2, 4),
(152, 11, 4, 1),
(153, 11, 4, 2),
(154, 11, 4, 3),
(155, 11, 4, 4),
(156, 12, 2, 4),
(157, 12, 4, 0),
(158, 12, 4, 1),
(159, 12, 4, 2),
(160, 12, 4, 3),
(161, 12, 4, 4),
(162, 13, 3, 0),
(163, 13, 3, 1),
(164, 13, 3, 2),
(165, 13, 3, 3),
(166, 13, 3, 4),
(167, 13, 4, 0),
(168, 13, 4, 1),
(169, 13, 4, 2),
(170, 13, 4, 3),
(171, 13, 4, 4),
(172, 14, 2, 0),
(173, 14, 2, 1),
(174, 14, 2, 2),
(175, 14, 2, 3),
(176, 14, 2, 4),
(177, 14, 3, 0),
(178, 14, 3, 1),
(179, 14, 3, 2);

--
-- Gatilhos `disponibilidade`
--
DROP TRIGGER IF EXISTS `Soma_Disc_Prof_Insert`;
DELIMITER //
CREATE TRIGGER `Soma_Disc_Prof_Insert` AFTER INSERT ON `disponibilidade`
 FOR EACH ROW BEGIN
    UPDATE professores SET somadisp =  (SELECT count(*)  FROM disponibilidade WHERE disponibilidade.ID_PROFESSOR = ID_PROF)
    WHERE ID_PROF = NEW.ID_PROFESSOR;
END
//
DELIMITER ;
DROP TRIGGER IF EXISTS `Soma_Disc_Prof_Update`;
DELIMITER //
CREATE TRIGGER `Soma_Disc_Prof_Update` AFTER UPDATE ON `disponibilidade`
 FOR EACH ROW BEGIN
    UPDATE professores SET somadisp =  (SELECT count(*)  FROM disponibilidade WHERE disponibilidade.ID_PROFESSOR = ID_PROF)
    WHERE ID_PROF = NEW.ID_PROFESSOR;
END
//
DELIMITER ;
DROP TRIGGER IF EXISTS `Soma_Disc_Prof_Delete`;
DELIMITER //
CREATE TRIGGER `Soma_Disc_Prof_Delete` AFTER DELETE ON `disponibilidade`
 FOR EACH ROW BEGIN
    UPDATE professores SET somadisp =  (SELECT count(*)  FROM disponibilidade WHERE disponibilidade.ID_PROFESSOR = ID_PROF)
    WHERE ID_PROF = OLD.ID_PROFESSOR;
END
//
DELIMITER ;

-- --------------------------------------------------------

--
-- Estrutura da tabela `grade`
--

CREATE TABLE IF NOT EXISTS `grade` (
  `ID_GRADE` int(11) NOT NULL AUTO_INCREMENT,
  `ID_TUR` int(11) NOT NULL,
  `ID_DISC` int(11) NOT NULL,
  `ID_PROF` int(11) DEFAULT NULL,
  `nr_periodos` int(11) NOT NULL DEFAULT '0',
  `geminar` int(11) DEFAULT '1',
  PRIMARY KEY (`ID_GRADE`),
  KEY `ID_PROF` (`ID_PROF`),
  KEY `ID_DISC` (`ID_DISC`),
  KEY `ID_TURMA` (`ID_TUR`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=56 ;

--
-- Extraindo dados da tabela `grade`
--

INSERT INTO `grade` (`ID_GRADE`, `ID_TUR`, `ID_DISC`, `ID_PROF`, `nr_periodos`, `geminar`) VALUES
(1, 20, 1, 1, 3, 2),
(2, 16, 2, 3, 2, 1),
(3, 17, 2, 1, 2, 1),
(4, 18, 2, 1, 2, 1),
(5, 19, 2, 9, 2, 1),
(6, 16, 3, 13, 2, 1),
(7, 17, 3, 13, 2, 1),
(8, 18, 3, 13, 2, 1),
(9, 19, 3, 13, 2, 1),
(10, 20, 3, 13, 1, 1),
(11, 16, 4, 11, 2, 1),
(12, 17, 4, 11, 2, 1),
(13, 18, 4, 11, 2, 1),
(14, 19, 4, 11, 2, 1),
(15, 20, 4, 11, 2, 1),
(16, 16, 5, 15, 2, 1),
(17, 17, 5, 15, 2, 1),
(18, 18, 5, 15, 2, 1),
(19, 19, 5, 15, 2, 1),
(20, 20, 5, 15, 1, 1),
(21, 20, 6, 10, 1, 1),
(22, 20, 7, 9, 3, 2),
(23, 16, 8, 4, 2, 1),
(24, 17, 8, 4, 2, 1),
(25, 18, 8, 4, 2, 1),
(26, 19, 8, 4, 2, 1),
(27, 20, 8, 4, 2, 1),
(28, 16, 9, 12, 2, 1),
(29, 17, 9, 12, 2, 1),
(30, 18, 9, 12, 2, 1),
(31, 19, 9, 4, 2, 1),
(32, 20, 9, 10, 2, 1),
(33, 16, 10, 7, 2, 1),
(34, 17, 10, 7, 2, 1),
(35, 18, 10, 7, 2, 1),
(36, 19, 10, 7, 2, 1),
(37, 20, 10, 7, 1, 1),
(38, 20, 11, 8, 1, 1),
(39, 16, 12, 5, 5, 3),
(40, 17, 12, 5, 5, 3),
(41, 18, 12, 3, 5, 3),
(42, 19, 12, 2, 5, 3),
(43, 20, 12, 2, 4, 2),
(44, 20, 14, 3, 2, 1),
(45, 16, 13, 6, 5, 3),
(46, 17, 13, 6, 5, 3),
(47, 18, 13, 6, 5, 3),
(48, 19, 13, 6, 5, 3),
(49, 20, 13, 8, 3, 2),
(50, 16, 16, 14, 1, 1),
(51, 17, 16, 14, 1, 1),
(52, 18, 16, 14, 1, 1),
(53, 19, 16, 14, 1, 1),
(54, 20, 16, 14, 1, 1),
(55, 20, 17, 4, 1, 1);

--
-- Gatilhos `grade`
--
DROP TRIGGER IF EXISTS `Soma_Per_Tur_Insert`;
DELIMITER //
CREATE TRIGGER `Soma_Per_Tur_Insert` AFTER INSERT ON `grade`
 FOR EACH ROW BEGIN
    UPDATE turmas SET soma_periodos =  (SELECT sum(nr_periodos)  FROM grade WHERE turmas.ID_TURMA = ID_TUR)
    WHERE ID_TURMA = NEW.ID_TUR;
END
//
DELIMITER ;
DROP TRIGGER IF EXISTS `Soma_Per_Tur_Update`;
DELIMITER //
CREATE TRIGGER `Soma_Per_Tur_Update` AFTER UPDATE ON `grade`
 FOR EACH ROW BEGIN
    UPDATE turmas SET soma_periodos =  (SELECT sum(nr_periodos)  FROM grade WHERE turmas.ID_TURMA = ID_TUR)
    WHERE ID_TURMA = NEW.ID_TUR;
END
//
DELIMITER ;
DROP TRIGGER IF EXISTS `Soma_Per_Tur_Delete`;
DELIMITER //
CREATE TRIGGER `Soma_Per_Tur_Delete` AFTER DELETE ON `grade`
 FOR EACH ROW BEGIN
    UPDATE turmas SET soma_periodos =  (SELECT sum(nr_periodos)  FROM grade WHERE turmas.ID_TURMA = ID_TUR)
    WHERE ID_TURMA = OLD.ID_TUR;
END
//
DELIMITER ;

-- --------------------------------------------------------

--
-- Estrutura da tabela `instituicao`
--

CREATE TABLE IF NOT EXISTS `instituicao` (
  `ID_INST` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(200) DEFAULT NULL,
  `nr_dias` int(11) NOT NULL DEFAULT '0',
  `nr_periodos` int(11) NOT NULL DEFAULT '0',
  `total_periodos` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID_INST`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Extraindo dados da tabela `instituicao`
--

INSERT INTO `instituicao` (`ID_INST`, `nome`, `nr_dias`, `nr_periodos`, `total_periodos`) VALUES
(1, 'Escola Modelo', 5, 5, 25);

--
-- Gatilhos `instituicao`
--
DROP TRIGGER IF EXISTS `total_periodos_ins`;
DELIMITER //
CREATE TRIGGER `total_periodos_ins` BEFORE INSERT ON `instituicao`
 FOR EACH ROW begin
    set NEW.total_periodos = (NEW.nr_dias * NEW.nr_periodos);
end
//
DELIMITER ;
DROP TRIGGER IF EXISTS `total_periodos_upd`;
DELIMITER //
CREATE TRIGGER `total_periodos_upd` BEFORE UPDATE ON `instituicao`
 FOR EACH ROW begin
    set NEW.total_periodos = (NEW.nr_dias * NEW.nr_periodos);
end
//
DELIMITER ;

-- --------------------------------------------------------

--
-- Estrutura da tabela `professores`
--

CREATE TABLE IF NOT EXISTS `professores` (
  `ID_PROF` int(11) NOT NULL AUTO_INCREMENT,
  `nome` varchar(200) NOT NULL,
  `sexo` char(1) DEFAULT NULL,
  `endereco` varchar(200) DEFAULT NULL,
  `fone` varchar(150) DEFAULT NULL,
  `data_nasc` date DEFAULT NULL,
  `somadisp` int(11) DEFAULT NULL,
  `ID_INSTITUICAO` int(11) NOT NULL,
  PRIMARY KEY (`ID_PROF`),
  KEY `ID_INSTITUICAO` (`ID_INSTITUICAO`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=16 ;

--
-- Extraindo dados da tabela `professores`
--

INSERT INTO `professores` (`ID_PROF`, `nome`, `sexo`, `endereco`, `fone`, `data_nasc`, `somadisp`, `ID_INSTITUICAO`) VALUES
(1, 'Adir', 'M', NULL, NULL, '1983-01-12', 10, 1),
(2, 'André', 'M', NULL, NULL, NULL, 15, 1),
(3, 'Daniel', NULL, NULL, NULL, NULL, 15, 1),
(4, 'Edilcia', 'F', NULL, NULL, NULL, 18, 1),
(5, 'Fabiana', NULL, NULL, NULL, NULL, 10, 1),
(6, 'Fernanda', NULL, NULL, NULL, NULL, 20, 1),
(7, 'Gabriela', NULL, NULL, NULL, NULL, 13, 1),
(8, 'Geferson', NULL, NULL, NULL, NULL, 10, 1),
(9, 'Gislaine', NULL, NULL, NULL, NULL, 10, 1),
(10, 'Henrique', NULL, NULL, NULL, NULL, 8, 1),
(11, 'Jefferson', NULL, NULL, NULL, NULL, 14, 1),
(12, 'Marcelo', NULL, NULL, NULL, NULL, 6, 1),
(13, 'Maria', NULL, NULL, NULL, NULL, 10, 1),
(14, 'Renato', NULL, NULL, NULL, NULL, 8, 1),
(15, 'Virginia', NULL, NULL, NULL, NULL, 12, 1);

-- --------------------------------------------------------

--
-- Estrutura da tabela `turmas`
--

CREATE TABLE IF NOT EXISTS `turmas` (
  `ID_TURMA` int(11) NOT NULL AUTO_INCREMENT,
  `turma` varchar(50) NOT NULL,
  `observacao` varchar(250) DEFAULT NULL,
  `soma_periodos` int(11) NOT NULL DEFAULT '0',
  `ID_INSTITUICAO` int(11) NOT NULL,
  PRIMARY KEY (`ID_TURMA`),
  KEY `PK_INSTITUICAO` (`ID_INSTITUICAO`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=21 ;

--
-- Extraindo dados da tabela `turmas`
--

INSERT INTO `turmas` (`ID_TURMA`, `turma`, `observacao`, `soma_periodos`, `ID_INSTITUICAO`) VALUES
(16, '51', NULL, 25, 1),
(17, '61', NULL, 25, 1),
(18, '71', NULL, 25, 1),
(19, '81', NULL, 25, 1),
(20, '101', NULL, 28, 1);

-- --------------------------------------------------------

--
-- Estrutura stand-in para visualizar `viewdiscturmas`
--
CREATE TABLE IF NOT EXISTS `viewdiscturmas` (
`disciplina` varchar(100)
,`51` decimal(32,0)
,`61` decimal(32,0)
,`71` decimal(32,0)
,`81` decimal(32,0)
,`101` decimal(32,0)
);
-- --------------------------------------------------------

--
-- Estrutura stand-in para visualizar `viewprofdisc`
--
CREATE TABLE IF NOT EXISTS `viewprofdisc` (
`disciplina` varchar(100)
,`51` varchar(200)
,`61` varchar(200)
,`71` varchar(200)
,`81` varchar(200)
,`101` varchar(200)
);
-- --------------------------------------------------------

--
-- Estrutura para visualizar `viewdiscturmas`
--
DROP TABLE IF EXISTS `viewdiscturmas`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `viewdiscturmas` AS select `disciplinas`.`disciplina` AS `disciplina`,sum(if((`turmas`.`turma` = '51'),`grade`.`nr_periodos`,0)) AS `51`,sum(if((`turmas`.`turma` = '61'),`grade`.`nr_periodos`,0)) AS `61`,sum(if((`turmas`.`turma` = '71'),`grade`.`nr_periodos`,0)) AS `71`,sum(if((`turmas`.`turma` = '81'),`grade`.`nr_periodos`,0)) AS `81`,sum(if((`turmas`.`turma` = '101'),`grade`.`nr_periodos`,0)) AS `101` from ((`grade` join `turmas`) join `disciplinas`) where ((`grade`.`ID_DISC` = `disciplinas`.`ID_DISC`) and (`grade`.`ID_TUR` = `turmas`.`ID_TURMA`)) group by `disciplinas`.`disciplina`;

-- --------------------------------------------------------

--
-- Estrutura para visualizar `viewprofdisc`
--
DROP TABLE IF EXISTS `viewprofdisc`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `viewprofdisc` AS select `disciplinas`.`disciplina` AS `disciplina`,if((`turmas`.`turma` = '51'),`professores`.`nome`,'-') AS `51`,if((`turmas`.`turma` = '61'),`professores`.`nome`,'-') AS `61`,if((`turmas`.`turma` = '71'),`professores`.`nome`,'-') AS `71`,if((`turmas`.`turma` = '81'),`professores`.`nome`,'-') AS `81`,if((`turmas`.`turma` = '101'),`professores`.`nome`,'-') AS `101` from (((`turmas` join `disciplinas`) join `grade`) join `professores`) where ((`grade`.`ID_DISC` = `disciplinas`.`ID_DISC`) and (`grade`.`ID_TUR` = `turmas`.`ID_TURMA`) and (`grade`.`ID_PROF` = `professores`.`ID_PROF`));

--
-- Restrições para as tabelas dumpadas
--

--
-- Restrições para a tabela `disciplinas`
--
ALTER TABLE `disciplinas`
  ADD CONSTRAINT `fk_disciplinas` FOREIGN KEY (`ID_INST`) REFERENCES `instituicao` (`ID_INST`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Restrições para a tabela `disponibilidade`
--
ALTER TABLE `disponibilidade`
  ADD CONSTRAINT `disponibilidade_ibfk_1` FOREIGN KEY (`ID_PROFESSOR`) REFERENCES `professores` (`ID_PROF`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Restrições para a tabela `grade`
--
ALTER TABLE `grade`
  ADD CONSTRAINT `grade_ibfk_1` FOREIGN KEY (`ID_TUR`) REFERENCES `turmas` (`ID_TURMA`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `grade_ibfk_2` FOREIGN KEY (`ID_PROF`) REFERENCES `professores` (`ID_PROF`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `grade_ibfk_3` FOREIGN KEY (`ID_DISC`) REFERENCES `disciplinas` (`ID_DISC`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Restrições para a tabela `professores`
--
ALTER TABLE `professores`
  ADD CONSTRAINT `professores_ibfk_1` FOREIGN KEY (`ID_INSTITUICAO`) REFERENCES `instituicao` (`ID_INST`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Restrições para a tabela `turmas`
--
ALTER TABLE `turmas`
  ADD CONSTRAINT `turmas_ibfk_1` FOREIGN KEY (`ID_INSTITUICAO`) REFERENCES `instituicao` (`ID_INST`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
