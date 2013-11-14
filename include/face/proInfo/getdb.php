<?php
header('Content-Type: application/json; charset=utf-8');

$sql_query = $_GET['query'];

$conn = mysqli_connect("localhost","root","sodwkdrh","Fridge");

if (mysqli_connect_errno()) {
	echo "MySQL 연결 실패 : " . mysqli_connect_error();
}

$result = mysqli_query($conn, $sql_query);
//print_r($result);

$row_size = mysqli_num_rows($result);
//echo "size = " .$row_size ."\n";

echo "[";
while($row = mysqli_fetch_array($result)){
	echo json_encode($row);
	if($row_size != 1)
		echo ",";
	$row_size--;
}
echo "]";
mysqli_close($conn);



?>
