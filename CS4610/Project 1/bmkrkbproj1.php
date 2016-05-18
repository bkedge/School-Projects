<!DOCTYPE html>
<?php
if (isset($_GET['mn'])) {
    $mn = intval($_GET['mn']);
} else {
    $mn = 0;
}

$dbhost = "localhost";
$dbuser = "root";
$dbpassword = "";
$dbname = "mathdb";

$con = mysql_connect($dbhost, $dbuser, $dbpassword);

#print "Connection opened";
echo "<br>";

if (!$con) {
    die('Could not connect: ' . mysql_error());
}

$db_found = mysql_select_db($dbname, $con);

$BookTitleVal = $_POST['BookTitleForm'];
$SubtitleVal = $_POST['SubtitleForm'];
$AuthorsVal = $_POST['AuthorsForm'];
$IsbnVal = $_POST['IsbnForm'];
$PublisherVal = $_POST['PublisherForm'];
$EditionVal = $_POST['EditionForm'];
$YearVal = $_POST['YearForm'];
$ChaptersVal = $_POST['ChaptersForm'];

if(empty($BookTitleVal) || empty($AuthorsVal) || empty($IsbnVal) ||
   empty($PublisherVal) || empty($EditionVal) ||
   empty($YearVal) || empty($ChaptersVal))
   {
     echo "<h2> Data not sent. Please fill out all required fields </h2>";
   }

$matchResult = mysql_query("SELECT * FROM book WHERE isbn = '$IsbnVal'");
if(mysql_num_rows($matchResult) == 1)
{
  echo "<h2> This ISBN already exists in this table. Please enter a new value </h2>";
}



elseif($db_found){
  $SQL = "INSERT INTO book (book_title, subtitle, authors, isbn, edition_number, year_number, publisher, number_of_chapters)
          VALUES ('$BookTitleVal', '$SubtitleVal', '$AuthorsVal', '$IsbnVal', '$EditionVal', '$YearVal', '$PublisherVal', '$ChaptersVal')";
          $result = mysql_query($SQL);
          echo "<h2> Data Added Successfully! </h2>";

}

?>

<?php
  mysql_close($con);
?>
