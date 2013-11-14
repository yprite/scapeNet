<?php

$fdir = $dir;
        $fopen = fopen($fdir, 'w');
        $secure = '<?php exit;?>';
        flock($fopen, LOCK_EX);
        fwrite($fopen,'');
        flock($fopen, LOCK_UN);
        fclose($fopen)

?>