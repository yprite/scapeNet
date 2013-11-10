<?php
$fdir = $dir;
$fopen = fopen($fdir, 'r');
$fcontent = fread($fopen, filesize($fdir));
$fcontent_split = explode('',$fcontent);
fclose($fopen);

print_r($fcontent_split);
?>