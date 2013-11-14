<?php
header('Content-Type: application/json; charset=utf-8');

$id = $_GET['id'];
$category = $_GET['category'];
$name = $_GET['name'];
$life = $_GET['life'];
$date = $_GET['date'];


$conn = mysqli_connect("localhost","root","sodwkdrh","Fridge");

if (mysqli_connect_errno()) {
	echo "MySQL 연결 실패 : " . mysqli_connect_error();
}

$sql_query = "insert into myfood(ID, categoryname, 항목, 유통기한, 구입날) values(";
$mid = ",";
//$sql_query .= .$id .',' .$category .',' .$name .',' .$life .',' .$date .')';
$sql_query .= $id;
$sql_query .= $mid;
$sql_query .= $category;
$sql_query .= $mid;
$sql_query .= $name;
$sql_query .= $mid;
$sql_query .= $life;
$sql_query .= $mid;
$sql_query .= $date;
$sql_query .= ")";

echo $sql_query ;
mysqli_query($conn, $sql_query);


mysqli_close($conn);
?>
