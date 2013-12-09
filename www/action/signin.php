<?
session_start();

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

$sql="SELECT * FROM admin_info;";
$rs =  mysql_query($sql, $connect);   // sql문 실행

while($info=mysql_fetch_array($rs)){
	$id= $info['id'];
	$passwd = $info['passwd'];
}
mysql_close($connect);

if($id != $_POST['id']){
	echo '관리자 아이디가 다릅니다.';
	exit();
}


if($passwd != $_POST['passwd']){
	echo '관리자 비밀번호가 다릅니다.';
	exit();
}

$_SESSION['scapenet_id'] = $id;
$_SESSION['scapenet_sign'] = 'sign';
echo '1';
?>