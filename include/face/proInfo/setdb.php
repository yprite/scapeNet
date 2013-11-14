<?php
header('Content-Type: application/json; charset=utf-8');

$sql_query = $_GET['query'];

$conn = mysqli_connect("localhost","root","sodwkdrh","Fridge");

if (mysqli_connect_errno()) {
	echo "MySQL 연결 실패 : " . mysqli_connect_error();
}

$result = mysqli_query($conn, $sql_query);
mysqli_close($conn);
?>
