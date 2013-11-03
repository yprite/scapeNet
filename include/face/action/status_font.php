<?php
 $im = ImageCreateTrueColor(140, 140);
 $white = ImageColorAllocate($im, 0xFF,0xFF,0xFF);
 $black = ImageColorAllocate($im, 0x2b,0x6b,0x8f);
 $red = imagecolorallocate($im, 255, 0, 0);
imagealphablending($im, false);
$transparency = imagecolorallocatealpha($im, 0, 0, 0, 127);
imagefill($im, 0, 0, $transparency);
imagesavealpha($im, true);
 if(strlen($_GET['q']) ==1){
ImageTTFText ($im, 50, 0, 50, 90, $black, 'HelveticaNeueLight.ttf', $_GET['q']); 
 }else if(strlen($_GET['q']) ==2){
ImageTTFText ($im, 50, 0, 32, 90, $black, 'HelveticaNeueLight.ttf', $_GET['q']); 
 }else{
 ImageTTFText ($im, 50, 0, 13, 90, $black, 'HelveticaNeueLight.ttf', $_GET['q']);
 }
 header('Content-Type: image/png');
 ImagePNG($im);
?>