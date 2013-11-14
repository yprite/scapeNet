<?

$c = str_ireplace('Scapenet > ', '', $_POST['q']);

$co = explode(' ', $c);
switch($co[0]){
	case 'kill':?>alert("\"<?=$co[1]?>\" IP를 종료합니다.");<?;break;
	case 'on':?>alert("\"<?=$co[1]?>\" IP를 종료합니다.");<?;break;
	case 'planet':?>location.href = "planet.php"<?;break;
	default :?>alert("잘못된 명령어 입니다.");<?break;
}
?>