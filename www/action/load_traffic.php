<?php
$ip = $_POST['ip'];
$date = $_POST['date'];
$hostname = "127.0.0.1";
$username = "root";
$password = "1234";
$dbname = "scapenet";

$connect = mysql_connect($hostname, $username, $password) or die("MySQL Server 연결에 실패했습니다");
$result = mysql_select_db($dbname,$connect);

if($result) {

}
else {
 echo("MySQL Server Connect 실패");
}

mysql_query("set names utf8");     // 결과값이 한글인 경우 사용

$sql="select * from traffic where ip = '".$ip."' and DATE(updateTime) between CURDATE() and DATE_ADD(CURDATE(),INTERVAL ".$date." DAY) order by updateTime desc;";
$rs =  mysql_query($sql, $connect);   // sql문 실행

$i = 11;
while($info=mysql_fetch_array($rs)){
	if($i<=0){
		break;
	}
	echo $i.'/';
	echo $info['up'].'/';
	echo $info['down'].'|';
	$i--;
}	

mysql_close($connect);

?>
