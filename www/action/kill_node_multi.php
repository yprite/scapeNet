<?php
	$ip = $_POST['ip'];
	$fdir = '../bin/read_face';
	$fopen = fopen($fdir, 'w');
	flock($fopen, LOCK_EX);
	$content = '';
	$arr = explode(',', $ip);
	for($i=0;$i<count($arr)-1;$i++){
	$content += 'k '.$arr[$i].'
';
	echo $arr[$i].'[**]';
	}

	fwrite($fopen,$content);
	flock($fopen, LOCK_UN);
	fclose($fopen);
	echo $ip;
?>