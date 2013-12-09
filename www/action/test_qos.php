<?php
$q = $_GET['q'];
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

$sql="SELECT * FROM ip_data;";
$rs =  mysql_query($sql, $connect);   // sql문 실행

while($info=mysql_fetch_array($rs)){
	$arr[$info['pid']]['pid'] = $info['pid'];
	$arr[$info['pid']]['ip'] = $info['ip'];
	$arr[$info['pid']]['mac'] = $info['mac'];
	$arr[$info['pid']]['up_traffic_cur'] = $info['up_traffic_cur'];
	$arr[$info['pid']]['down_traffic_cur'] = $info['down_traffic_cur'];
	$arr[$info['pid']]['up_traffic_limit'] = $info['up_traffic_limit'];
	$arr[$info['pid']]['down_traffic_limit'] = $info['down_traffic_limit'];
	$arr[$info['pid']]['isStatus'] = $info['isStatus'];
	$arr[$info['pid']]['name'] = $info['name'];
	$arr[$info['pid']]['port'] = $info['port'];
}
mysql_close($connect);

?>