<?php
$ip = $_GET['ip'];
$date = $_GET['date'];
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

$sql="(select ip, avg(up) as up, avg(down) as up from traffic where ip = '".$ip."' and DATE(updateTime) between curdate() and DATE_ADD(curdate(),INTERVAL 3 DAY) order by updateTime desc) 
union all
(select ip, avg(up), avg(down) from traffic where ip = '".$ip."' and DATE(updateTime) between DATE_ADD(curdate(),INTERVAL 3 DAY) and DATE_ADD(curdate(),INTERVAL 6 DAY) order by updateTime desc)
union all
(select ip, avg(up), avg(down) from traffic where ip = '".$ip."' and DATE(updateTime) between DATE_ADD(curdate(),INTERVAL 6 DAY) and DATE_ADD(curdate(),INTERVAL 9 DAY) order by updateTime desc)
union all
(select ip, avg(up), avg(down) from traffic where ip = '".$ip."' and DATE(updateTime) between DATE_ADD(curdate(),INTERVAL 9 DAY) and DATE_ADD(curdate(),INTERVAL 12 DAY) order by updateTime desc)
union all
(select ip, avg(up), avg(down) from traffic where ip = '".$ip."' and DATE(updateTime) between DATE_ADD(curdate(),INTERVAL 12 DAY) and DATE_ADD(curdate(),INTERVAL 15 DAY) order by updateTime desc)
union all
(select ip, avg(up), avg(down) from traffic where ip = '".$ip."' and DATE(updateTime) between DATE_ADD(curdate(),INTERVAL 15 DAY) and DATE_ADD(curdate(),INTERVAL 18 DAY) order by updateTime desc)
union all
(select ip, avg(up), avg(down) from traffic where ip = '".$ip."' and DATE(updateTime) between DATE_ADD(curdate(),INTERVAL 18 DAY) and DATE_ADD(curdate(),INTERVAL 21 DAY) order by updateTime desc)
union all
(select ip, avg(up), avg(down) from traffic where ip = '".$ip."' and DATE(updateTime) between DATE_ADD(curdate(),INTERVAL 21 DAY) and DATE_ADD(curdate(),INTERVAL 24 DAY) order by updateTime desc)
union all
(select ip, avg(up), avg(down) from traffic where ip = '".$ip."' and DATE(updateTime) between DATE_ADD(curdate(),INTERVAL 24 DAY) and DATE_ADD(curdate(),INTERVAL 27 DAY) order by updateTime desc)
union all
(select ip, avg(up), avg(down) from traffic where ip = '".$ip."' and DATE(updateTime) between DATE_ADD(curdate(),INTERVAL 27 DAY) and DATE_ADD(curdate(),INTERVAL 30 DAY) order by updateTime desc)
union all
(select ip, avg(up), avg(down) from traffic where ip = '".$ip."' and DATE(updateTime) between DATE_ADD(curdate(),INTERVAL 30 DAY) and DATE_ADD(curdate(),INTERVAL 33 DAY) order by updateTime desc);";
$rs =  mysql_query($sql, $connect);   // sql문 실행

$i = 11;
while($info=mysql_fetch_array($rs)){
	if($i<=0){
		break;
	}
	echo $i.'/';
	if(!$info['up']){
		$info['up'] = '0';
	}
	if(!$info['down']){
		$info['down'] = '0';
	}
	echo $info['up'].'/';
	echo $info['down'].'|';
	$i--;
}	

mysql_close($connect);

?>
