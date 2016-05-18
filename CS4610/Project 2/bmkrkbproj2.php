<!DOCTYPE html>
<html>
  <body>

<?php
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

?>

<?php
  $bookQuery = mysql_query("SELECT book_title FROM book");
?>

<?php
  if(!isset($_POST['EnterButton'])){

?>

      <form action = "bmkrkbproj2.php" id="proj2form" method = "post">
         <!--<input type = "text" name="QuestionForm" placeholder="Enter a problem"><br><br>-->
         <textarea name="QuestionForm" form="proj2form" rows="5" cols="100" placeholder="Enter a problem"></textarea></br></br>
         <select name="book_title_form">
           <option value="">--Select a book--</option>
           <?php
              while($row = mysql_fetch_array($bookQuery)){
                echo "<option value='" . $row['book_title'] . "'>" . $row['book_title'] . "</option>";
              }
            ?>

         </select>
         <br><br>
         <input type = "text" name="PageForm" style="width: 100px; text-align: center;" placeholder="page number">
         <input type="text" name="ProblemNumberForm" style="width: 100px; text-align: center;" placeholder="prob-number">
         <input type="text" name="SubcodeForm" style="width: 100px; text-align: center;" placeholder="subcode">
       <br>
       <br>
         <input type="submit" value="Enter" name="EnterButton"/>

       </form>
       <br>


       <?php

        #echo "<br>";
        echo "<h2> Questions </h2>";
        echo "<br>";

        $displayQuery1 = "SELECT * FROM questions ORDER BY DateTime DESC";
        $displayRes1 = mysql_query($displayQuery1);

        echo "<table border = '1'>";
        echo "<tr><th>Question</th><th>Book</th><th>Page Number</th><th>Question Number</th><th>Data / Time</th></tr>";

        while($row = mysql_fetch_array($displayRes1))
        {
          echo "<tr><td>" . $row['Content'] . "</td><td>" . $row['BookID'] . "</td><td>" . $row['PageNum'] . "</td><td>" . $row['QuestionNum'] . "</td><td>" . $row['DateTime'] . "</td></tr>";
        }

        echo "</table>";


      }

       #Conditional Statements
       else{
            $QuestionVal = $_POST['QuestionForm'];
            $BookTitleVal = $_POST['book_title_form'];
            $PageVal = $_POST['PageForm'];
            $ProblemNumberVal = $_POST['ProblemNumberForm'];
            $SubcodeVal = $_POST['SubcodeForm'];


         ?>

         <form action = "bmkrkbproj2.php" id="proj2form" method = "post">
            <!--<input type = "text" name="QuestionForm" placeholder="Enter a problem"><br><br>-->
            <textarea name="QuestionForm" form="proj2form" rows="5" cols="100" placeholder="Enter a problem"></textarea></br></br>
            <select name="book_title_form">
              <option value="">--Select a book--</option>
              <?php
                 while($row = mysql_fetch_array($bookQuery)){
                   echo "<option value='" . $row['book_title'] . "'>" . $row['book_title'] . "</option>";
                 }
               ?>

            </select>
            <br><br>
            <input type = "text" name="PageForm" style="width: 100px; text-align: center;" placeholder="page number">
            <input type="text" name="ProblemNumberForm" style="width: 100px; text-align: center;" placeholder="prob-number">
            <input type="text" name="SubcodeForm" style="width: 100px; text-align: center;" placeholder="subcode">
          <br>
          <br>
            <input type="submit" value="Enter" name="EnterButton"/>

          </form>

         <?php


         echo "<br>";

         #Content field is empty
         if(empty($QuestionVal))
         {
           echo "<h1> Content field is empty, please enter a value </h1>";
         }
         else
         {
           #Value in dropdown is selected
           if(!empty($BookTitleVal))
           {
             #echo "Value selected is " . $BookTitleVal;
             if(empty($PageVal) || empty($ProblemNumberVal))
             {
               echo "<h1> A book is selected, therefore Page number and Poblem number must be filled out </h1>";
             }
             #All book information provided. Check if question exists
             else
             {
               $query1 = "SELECT * FROM questions WHERE Content = '$QuestionVal' AND PageNum = '$PageVal' AND QuestionNum = '$ProblemNumberVal'";
               $res1 = mysql_query($query1);

               if(mysql_num_rows($res1) == 1)
               {
                 echo "<h1> This question already exists in this table. Please enter a new value </h1>";
               }
               elseif($db_found)
               {
                 $query2 = "INSERT INTO questions (Content, BookID, PageNum, QuestionNum, DateTime) VALUES ('$QuestionVal', '$BookTitleVal', '$PageVal', '$ProblemNumberVal', NOW())";
                 $res2 = mysql_query($query2);
                 echo "<h1> Question added! </h1>";

                 echo "<h2> Questions </h2>";
                 echo "<br>";

                 $displayQuery2 = "SELECT * FROM questions ORDER BY DateTime DESC";
                 $displayRes2 = mysql_query($displayQuery2);

                 echo "<table border = '1'>";
                 echo "<tr><th>Question</th><th>Book</th><th>Page Number</th><th>Question Number</th><th>Data / Time</th></tr>";

                 while($row = mysql_fetch_array($displayRes2))
                 {
                   echo "<tr><td>" . $row['Content'] . "</td><td>" . $row['BookID'] . "</td><td>" . $row['PageNum'] . "</td><td>" . $row['QuestionNum'] . "</td><td>" . $row['DateTime'] . "</td></tr>";
                 }

                 echo "</table>";


               }

             }
           }
           #Value is not selected in dropdown
           else {
             #echo "Empty";
             $query3 = "INSERT INTO questions (Content, PageNum, QuestionNum, DateTime) VALUES ('$QuestionVal', '$PageVal', '$ProblemNumberVal', NOW())";
             $res3 = mysql_query($query3);
             echo "<h1> Question added! </h1>";

             echo "<h2> Questions </h2>";
             echo "<br>";

             $displayQuery3 = "SELECT * FROM questions ORDER BY DateTime DESC";
             $displayRes3 = mysql_query($displayQuery3);

             echo "<table border = '1'>";
             echo "<tr><th>Question</th><th>Book</th><th>Page Number</th><th>Question Number</th><th>Data / Time</th></tr>";

             while($row = mysql_fetch_array($displayRes3))
             {
               echo "<tr><td>" . $row['Content'] . "</td><td>" . $row['BookID'] . "</td><td>" . $row['PageNum'] . "</td><td>" . $row['QuestionNum'] . "</td><td>" . $row['DateTime'] . "</td></tr>";
             }

             echo "</table>";
           }
         }



         #echo "Submitted";

         #echo "<br>";
         #echo $QuestionVal;
         #echo "<br>";
         #echo $BookTitleVal;
        }
       ?>

    </body>
</html>



<?php
  mysql_close($con);
?>
