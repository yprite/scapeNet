<?php
function MobileCheck() { 
    global $HTTP_USER_AGENT; 
    $MobileArray  = array("iphone","lgtelecom","skt","mobile","samsung","nokia","blackberry","android","android","sony","phone");

    $checkCount = 0; 
        for($i=0; $i<sizeof($MobileArray); $i++){ 
            if(preg_match("/$MobileArray[$i]/", strtolower($HTTP_USER_AGENT))){ $checkCount++; break; } 
        } 
   return ($checkCount >= 1) ? "Mobile" : "Computer"; 
}
?>
<html>

<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8"></head>
<body>
<?php
if(MobileCheck() == "Mobile"){ 
    echo"현재 휴대폰으로 접속했습니다.<br> PC환경만을 제공합니다."; 
}else{ 
    echo"현재 컴퓨터로 접속했습니다.";
}
?>
</body>
