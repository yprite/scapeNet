<?
session_start();
unset($_SESSION['scapenet_id'],$_SESSION['scapenet_sign']);
header('Location: index.php');	
?>