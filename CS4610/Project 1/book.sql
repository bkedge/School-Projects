DROP TABLE IF EXISTS `book`;
CREATE TABLE IF NOT EXISTS `book` (
`bid` int(10) unsigned NOT NULL,
  `book_title` varchar(150) NOT NULL,
  `subtitle` varchar(200) DEFAULT '',
  `authors` varchar(150) NOT NULL,
  `isbn` varchar(150) DEFAULT '',
  `edition_number` int(3) unsigned DEFAULT '1',
  `year_number` int(4) unsigned DEFAULT '0',
  `publisher` varchar(60) DEFAULT '',
  `number_of_chapters` int(2) unsigned DEFAULT '0',
  `problem_total` int(5) NOT NULL DEFAULT '0',
  `prob_ori_num` int(4) NOT NULL DEFAULT '0',
  `knowledge_total` int(4) NOT NULL DEFAULT '0',
  `book_type_id` int(1) unsigned DEFAULT '1',
  `old_book_id` int(10) NOT NULL DEFAULT '0',
  `member_id` int(10) unsigned DEFAULT '0',
  `create_time` datetime NOT NULL,
  `del` int(1) unsigned DEFAULT '0'
) ENGINE=MyISAM AUTO_INCREMENT=35 DEFAULT CHARSET=utf8;

INSERT INTO `book` (`bid`, `book_title`, `subtitle`, `authors`, `isbn`, `edition_number`, `year_number`, `publisher`, `number_of_chapters`, `problem_total`, `prob_ori_num`, `knowledge_total`, `book_type_id`, `old_book_id`, `member_id`, `create_time`, `del`) VALUES
(1, 'The IMO Compendium', 'A Collection of Problems Suggested for the International Mathematical Olympiads: 1959-2004', 'Dusan Djukic, Vladimir Jankovic, Ivan Matic, Nikola Petrovic', '0-387-24299-6, 978-0387-24299-6', 1, 2006, 'Springer', 4, 162, 162, 72, 1, 11, 1, '2016-01-04 04:55:09', 0),
(2, 'Problem-Solving Strategies', '', 'Arthur Engel', '0-387-98219-1', 1, 1997, 'Springer', 14, 297, 296, 76, 1, 5, 1, '2016-01-04 06:50:50', 0),
(3, 'The William Lowell Putnam Mathematical Competition Problems and Solutions (1965 - 1984)', '', 'Gerald L. Alexanderson, Leonard F. Klosinski, Loren C. Larson', '0-88385-463-5', 1, 1985, 'The Mathematical Association of America', 20, 4, 4, 0, 1, 78, 1, '2016-01-04 13:00:33', 0),
(4, 'Geometry Revisited', '', 'H. S. M. Coxeter, S. L. Greitzer', '978-0-88385-619-2', 1, 1967, 'The Mathematical Association of America', 6, 51, 46, 10, 1, 6, 1, '2016-01-13 23:53:11', 0),
(5, 'Barron&prime;s E-Z Geometry', '', 'Lawrence S. Leff', '978-0-7641-3918-5, 0-7641-3918-5', 1, 2009, 'Barron&prime;s', 17, 40, 0, 153, 1, 62, 1, '2016-01-14 03:57:32', 0),
(6, 'Discrete Mathematics and Its Applications', '', 'Kenneth H. Rosen', '978-0-07-288008-3, 0-07-288008-2', 6, 2007, 'McGraw Hill', 12, 0, 0, 88, 1, 61, 1, '2016-01-14 06:34:48', 0),
(7, 'An Introduction To Analysis', '', 'William R. Wade', '0-13-093089-X', 1, 1995, 'Prentice Hall, Inc.', 10, 11, 0, 56, 1, 55, 1, '2016-01-14 10:23:53', 0),
(8, 'Kaplan SAT: Strategies, Practice, and Review', '', 'Kaplan , Inc.', '978-1-4195-4995-3', 1, 2011, 'Kaplan', 15, 0, 0, 1, 1, 53, 1, '2016-01-14 10:52:45', 0),
(9, 'Solid Geometry', '', 'Joseph P. McCormack', '4116', 1, 1931, 'D. Appleton-Century Company', 4, 0, 0, 16, 1, 48, 1, '2016-01-14 10:52:55', 0),
(10, 'Inequalities', 'Theorems, Techniques and Selected Problems', 'Zdravko Cvetkovski', '978-3-642-23791-1, 978-3-642-23792-8', 1, 2012, 'Springer', 20, 85, 41, 101, 1, 47, 1, '2016-01-14 10:53:07', 0),
(11, 'Analytic Inequalities', '', 'D. S. Mitrinovic', '76-116492', 1, 1970, 'Springer-Verlag', 3, 1, 0, 2, 1, 46, 1, '2016-01-15 18:42:06', 0),
(12, 'Discrete Mathematics with Graph Theory', '', 'Edgar G. Goodaire, Michael M. Parmenter', '0-13-167995-3', 3, 2006, 'Pearson Education, Inc.', 15, 0, 0, 9, 1, 35, 1, '2016-01-15 18:42:37', 0),
(13, 'Geometry', '', 'Joseph Verdina', '0-675-08738-4', 1, 1975, 'Charles E. Merrill Publishing Company', 12, 36, 0, 118, 1, 22, 1, '2016-01-15 18:44:29', 0),
(14, 'Advanced Calculus', '', 'David V. Widder', '0-486-66103-2', 2, 1989, 'Dover Publications, Inc.', 14, 0, 0, 1, 1, 21, 1, '2016-01-19 03:12:01', 0),
(15, 'Advanced Calculus', '', 'Cronin-Scanlon', '66-21729', 1, 1967, 'D. C. Heath and Company', 5, 0, 0, 2, 1, 20, 1, '2016-01-19 03:12:17', 0),
(16, 'Introduction To Number Theory', '', 'James E. Shockley', '0-03-059760-9', 1, 1967, 'Holt, Rinehart and Winston, Inc.', 12, 11, 0, 26, 1, 18, 1, '2016-01-21 10:04:50', 0),
(17, 'The Art of Problem Solving Volume 2: and Beyond', '', 'Richard Rusczyk, Sandor Lehoczky', '978-0-9773045-8-5', 7, 2008, 'AoPS Incorporated', 26, 3, 0, 3, 1, 16, 1, '2016-01-21 10:26:35', 0),
(18, 'Advanced Euclidean Geometry', '', 'Roger A. Johnson', '978-0-486-46273-0, 0-486-46237-4', 1, 1960, 'Dover Publications, Inc.', 18, 2, 0, 5, 1, 15, 1, '2016-01-21 10:27:48', 0),
(19, 'Calculus', 'Early Transcendentals', 'James Stewart', '978-0538497817, 0538497815', 7, 2011, 'Brooks/Cole, Cengage Learning', 17, 46, 0, 133, 1, 10, 1, '2016-01-21 10:28:46', 0),
(20, 'USA Mathematical Olympiads 1972-1986', '', 'Murray S. Klamkin', '0-88385-634-4', 1, 1988, 'The Mathematical Association of America', 2, 5, 3, 0, 1, 13, 1, '2016-01-31 14:26:11', 0),
(21, 'The William Lowell Putnam Mathematical Competition Problems and Solutions 1938 - 1964', '', 'A.M. Gleason, R.E. Greenwood, L.M. Kelly', '978-0-88385-462-4', 1, 1980, 'The Mathematical Association of America', 25, 0, 0, 0, 1, 0, 0, '2016-01-31 15:40:35', 0),
(22, 'The William Lowell Putnam Mathematical Competition 1985 - 2000', 'Problems, Solutions and Commentary', 'Kiran S. Kedlaya, Bjorn Poonen, Ravi Vakil', '978-0-88385-827-1', 1, 2000, 'The Mathematical Association of America', 7, 0, 0, 0, 1, 0, 0, '2016-01-31 15:48:45', 0),
(23, 'Elementary Number Theory', '', 'Underwood Dudley', '978-0-486-46931-7, 0-486-46931-X', 2, 1978, 'Dover Publications, Inc.', 22, 35, 0, 47, 1, 4, 1, '2016-02-04 07:39:51', 0),
(24, 'Elementary Number Theory', '', 'Gareth A. Jones and J. Mary Jones', '3-540-76197-7', 1, 1998, 'Springer', 11, 14, 0, 20, 1, 3, 1, '2016-02-04 17:31:20', 0),
(25, 'Inequalities', '', 'G. H. Hardy, J. E. Littlewood, G. Polya', '0-521-05206-8, 0-521-35880-9', 2, 1952, 'Cambridge University Press', 10, 0, 0, 7, 1, 1, 1, '2016-02-04 17:37:34', 0),
(26, 'Calculus', '', 'James Stewart', '978-0-495-01160-6', 6, 2008, 'Thomson Learning, Inc.', 18, 40, 0, 52, 1, 9, 1, '2016-02-04 17:46:50', 0),
(27, 'Geometric Inequalities', '', 'Nicholas D. Kasarinoff', '0-88385-600-X', 1, 1967, 'Yale University', 3, 4, 0, 10, 1, 7, 1, '2016-02-04 18:03:22', 0),
(28, 'Calculus', '', 'Jon Rogawski', '978-0-7167-6911-8, 0-7167-6911-5', 1, 2008, 'Freeman', 18, 4, 0, 9, 1, 8, 1, '2016-02-04 18:05:53', 0),
(29, 'The College Board SAT: 10 Real SATs', '', 'Cathy Claman', '0-87447-705-0', 3, 2003, 'The College Board', 17, 0, 0, 6, 1, 52, 1, '2016-02-04 18:08:59', 0),
(30, 'College Geometry', '', 'Leslie H. Miller', '57-5574', 1, 1957, 'Appleton-Century-Crofts, Inc.', 12, 1, 0, 3, 1, 12, 1, '2016-02-04 18:58:50', 0),
(31, 'Matrix Mathematics', 'Theory, Facts, and Formulas', 'Dennis S. Bernstain', '978-0-691-13287-7, 978-0-691-14039-1', 2, 2009, 'Princeton University Press', 12, 63, 0, 65, 1, 97, 1, '2016-02-08 07:30:03', 0),
(32, 'Intruduction To Matrices And Linear Transformations', '', 'Daniel T. Finkbeiner II', '0-7167-0084-0', 3, 1978, 'Freeman and Company', 11, 0, 0, 4, 1, 102, 1, '2016-02-09 08:02:50', 0),
(33, 'A First Course in Real Analysis', '', 'M. H. Protter, C. B. Morrey', '0-387-90215-5, 3-540-90215-5', 1, 1977, 'Springer-Verlag', 16, 19, 0, 32, 1, 100, 1, '2016-02-09 08:23:48', 0),
(34, 'Inequalities: Theory of Majorization and Its Applications', '', 'Albert W. Marshall, Ingram Olkin, Barry C. Arnold', '978-0-387-40087-7, 978-0-387-68276-1', 2, 2011, 'Springer', 20, 2, 0, 8, 1, 79, 1, '2016-02-09 18:20:24', 0);

ALTER TABLE `book`
 ADD PRIMARY KEY (`bid`);

ALTER TABLE `book`
MODIFY `bid` int(10) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=35;