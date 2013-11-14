<?
include ('../SSHDB/start.php');
sshdb_connect('test','test');
sshdb_create_ele('secmem','async','test','');
sshdb_modify_ele('secmem','async','test','option',$_POST['q']);
?>