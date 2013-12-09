<?
	session_start();
	if(!$_SESSION['scapenet_sign'] || $_SESSION['scapenet_sign'] != 'sign'){
		
	}else{
		header('Location: dashboard.php');	
	}
	
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<meta name="Generator" content="SeoSeungHyun WebKit">
<title>Scapenet Signin</title>
<script type="text/javascript" src="js/jquery-1.10.1.min.js"></script>
<script type="text/javascript" src="js/curve_ani.js"></script>
<style>
#black_wrap{position:absolute;width: 100%;height: 580px;background: black;text-align: center; }
#copyright {position:absolute;  width: 100%; margin-right: 50px; bottom: 20px; text-align: center;z-index: 25; opacity: 0}
body {margin: 0 auto; text-align: center; background: black;}
#content_wrap {margin: 0 auto; text-align: center; width: 300px; height:150px; color: white}
.input_account{border: none;border-radius: 25px;-moz-border-radius: 25px;-webkit-border-radius: 25px; outline: none; width: 70%; text-align: center; height: 25px; margin-bottom: 10px; opacity:.3; font-size: 20px}
#btn_sign{cursor: pointer;}
#img_logo{opacity: .7; margin-left: -10px}
</style>
<script>
$(document).ready(function(){

	var width = parseInt($('#canvas').width()), height =  parseInt($(window).height() - $('#content_wrap').offset().top);
	$('#content_wrap').css('margin-top',$(window).height()/2-$('#content_wrap').height()/2+'px');

	$( window ).resize(function() {
	$('#content_wrap').css('margin-top',$(window).height()/2-$('#content_wrap').height()/2+'px');
	});
	
	$('.input_account').focus(function(){
		$(this).css('opacity',.7);
	})
	.blur(function(){
		$(this).css('opacity',.3);
	})
	.keypress(function(e) {if (e.keyCode == 13) {$('#btn_signin').click();}});
	
	
	$('#input_id').focus();
	
	$('#btn_signin').click(function(){
		$.ajax({
	            type: 'POST',
	            url: 'action/signin.php',
	            data: {
	                id : $('#input_id').val(),
	                passwd : $('#input_passwd').val()
	            },
	            success: function(result) {
		            if(result != 1){
			            alert(result);
		            }else{
						location.reload();
		            }
	            },
	            error: function(result) {
	                alert("오류가 발생했습니다.");
	            }
	        });
	});
	function animate_opacity(){
		$('#img_logo').animate({'opacity':.25},1000,function(){
			$(this).animate({'opacity':.7},1000,function(){
				animate_opacity();
			})
			
		})
	}
	animate_opacity();

});
</script>
</head>

<body>

<div id="content_wrap">
<img id="img_logo" src="img/logo.png" width="243" height="74" href="code.org.mp4"/><br /><br />
	<input id="input_id" class="input_account" /><br />
	<input id="input_passwd" class="input_account" type="password" /><br /><br />
	<span id="btn_signin"><font color="#868686">NEXT</font></span>
</div>
</body>
