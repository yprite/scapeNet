<?
include ('../SSHDB/start.php');
sshdb_connect('test','test');
sshdb_create_ele('secmem','async','test','');
sshdb_get_ele('secmem','async','test','option');
echo $sshdb_get['secmem']['async']['test']['option'];
?>