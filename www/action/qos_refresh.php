<?php

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

$sql="UPDATE ip_data SET qos=".$_POST['lv']." WHERE ip='".$_POST['ip']."';";

$retval = mysql_query( $sql, $connect );
mysql_close($connect);

if($_POST['lv'] == '6'){
	$way = 'del';	
}else{
	$way = 'add';
}

	$content = 'tc filter '.$way.' dev eth0 protocol ip parent 1:0 prio 1 u32 match ip src '.$_POST['ip'].'/32 flowid 1:'.$_POST['lv'];
	//$content = $_POST['way'].'_'.$_POST['ip'].'_'.$_POST['lv'];
	$fdir = '../bin/read_face2';
	$fopen = fopen($fdir, 'w');
	flock($fopen, LOCK_EX);
	fwrite($fopen,$content);
	flock($fopen, LOCK_UN);
	fclose($fopen);
	echo $ip;
?>