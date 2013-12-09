<?php
	$ip = $_POST['ip'];
	$fdir = '../bin/read_face';
	$fopen = fopen($fdir, 'w');
	flock($fopen, LOCK_EX);
	fwrite($fopen,'s '.$ip.'
');
	flock($fopen, LOCK_UN);
	fclose($fopen);
	echo $ip;
?>
