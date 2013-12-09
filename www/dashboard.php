<?
	session_start();
	if(!$_SESSION['scapenet_sign'] || $_SESSION['scapenet_sign'] != 'sign'){
		header('Location: index.php');	
	}
	
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<meta name="Generator" content="SeoSeungHyun WebKit">
<title>ScapeNet</title>
<style>
/*Style*/
html {overflow: hidden;}
body{margin: 0 auto; background:black;}
#canvas{width: 100%;height: 580px;}
#black_wrap{position:absolute;width: 100%;height: 580px;background: black;text-align: center; }

#info{position: absolute; width: 200px; height: 100px; bottom:40px; left: 50px; background: white;border-radius: 15px;-moz-border-radius: 15px;-webkit-border-radius: 15px;-webkit-filter: blur(5px);filter: blur(5px); opacity: .5; display: none;}
#dashboard{position: absolute; width: 200px; top:30px; height: 200px; right: 30px; float: right; background: white;border-radius: 15px;-moz-border-radius: 15px;-webkit-border-radius: 15px;-webkit-filter: blur(5px);filter: blur(5px); opacity: .4; display: none; z-index: 10; }
#ipboard{position: absolute; width: 700px; top:35px; height: 600px; right: 660px; float: right; background: black;border-radius: 15px;-moz-border-radius: 15px;-webkit-border-radius: 15px;-webkit-filter: blur(5px);filter: blur(5px); opacity: .7; display: none; }
#ipboard_content{position: absolute; width: 665px; top:45px; height: 590px; right: 680px; float: right;display: none;text-align: center;cursor: move}
#graphboard{position: absolute; width: 700px; top:35px; height: 490px; right: 360px; float: right; background: black;border-radius: 15px;-moz-border-radius: 15px;-webkit-border-radius: 15px;-webkit-filter: blur(5px);filter: blur(5px); opacity: .7; display: none; }
#graphboard_content{position: absolute; width: 665px; top:45px; height: 480px; right: 380px; float: right;display: none;text-align: center; cursor: move}
#dashboard_content{position: absolute; width: 165px; top:45px; height: 200px; right: 50px; float: right;display: none; z-index: 15;}
#dashboard_hover{position: absolute; width: 50px; top:0px; height: 200px; right: 0px; float: right; cursor: pointer;}
#dashboard_arrow{position: absolute; width: 20px; top:200px; height: 200px; right: -10px; float: right; cursor: pointer;}
#status {position:absolute; float: left; width: 170px; height: 80px; bottom:50px; left: 65px; display: none;}
#node_search{position:relative; width: 100%; height: 25px; margin-bottom: 5px;}
#input_search{border: none;border-radius: 9px;-moz-border-radius: 9px;-webkit-border-radius: 9px; outline: none; width: 98%; height: 22px;font-size: 17px; text-align: center;color: #404040;}
#img_logo {position:absolute; left: 20px; top:20px; opacity: .3; z-index: 25;}
#info_under {display: none; height: 235px;width: 166px; position: relative;float: left; overflow: visible; margin-bottom: 20px; text-align: center; }
#info_under_wrap{position:absolute; top:0; left: 0; width: 170px; height: 235px; background: white;-webkit-filter: blur(3px);filter: blur(3px); opacity: .6}
#info_under_content{position:absolute; top:0; left: 0; width: 166px; height: 224px; z-index: 5; padding: 3px 3px; margin-top: 3px; }

#modify_under {display: none; height: 80px;width: 166px; position: relative;float: left; overflow: visible; text-align: left; margin-top: 3px}
#modify_under_wrap{position:absolute; top:0; left: 0; width: 170px; height: 65px; background: black;-webkit-filter: blur(3px);filter: blur(3px); opacity: .6}
#modify_under_content{position:absolute; top:0; left: 0; width: 156px; height: 40px; z-index: 5; padding: 10px 10px; margin-top: 3px; color: #cbcbcb; font-size: 15px;}

#copyright {position:absolute;  width: 100%; margin-right: 50px; bottom: 20px; text-align: center;z-index: 25; opacity: .9}
#btn_ipmornitor{cursor: pointer;}
#btn_close{cursor: pointer;display:none;}
.node_hidden{display: none;}
#show_type{cursor: pointer}
#graph_wrap{width: 170px; height: 150px; overflow: hidden; position: relative; margin-top: -12px;}
#graph_live{width: 170px; height: 150px; overflow: hidden; position: relative;}
#title_3{margin-bottom: 5px;}
#btn_skip{cursor: pointer;}
#btn_c_graphb{cursor: pointer;}
#btn_c_ipb{cursor: pointer;}
.pointer { cursor: pointer}
.td_node{border-radius: 4px;-moz-border-radius: 4px;-webkit-border-radius: 4px;}
.td_board{border-radius: 12px;-moz-border-radius: 12px;-webkit-border-radius: 12px; }
.option_txt {font-size:13px;font-family: Georgia, Times, 'Times New Roman', serif; font-size: 13px; margin-top: 2px; margin-bottom: 5px;}
#input_qos{border: none;border-radius: 9px;-moz-border-radius: 9px;-webkit-border-radius: 9px; outline: none; height: 15px; width: 80px; text-align: center; background: #a9a9a9;opacity:.6; font-size: 13px;}
.btn_qos {float: left; position: relative; width: 13px; height: 13px;border-radius: 15px;-moz-border-radius: 15px;-webkit-border-radius: 15px; border: 1px solid #cdcdcd; padding: 3px 3px; text-align: center; margin-right: 4px; font-size: 12px; cursor: pointer; color: #cdcdcd; }
.btn_qos_select {float: left; position: relative; width: 13px; height: 13px;border-radius: 15px;-moz-border-radius: 15px;-webkit-border-radius: 15px; border: 1px solid #cdcdcd; background: #cdcdcd; color:black;  padding: 3px 3px; text-align: center; margin-right: 4px; font-size: 12px; cursor: pointer; }
.board_type {cursor: pointer;color:#b5b5b5;background:none;}
.board_selected {background:#b5b5b5;color:black;}
</style>
<script type="text/javascript" src="js/jquery-1.10.1.min.js"></script>
<script type="text/javascript" src="js/jquery-ui-1.10.3.min.js"></script>
<script type="text/javascript" src="js/raphael.js"></script>
<script type="text/javascript" src="js/three.min.js"></script>
<script type="text/javascript" src="js/helvetiker_regular.typeface.js"></script>
<script type="text/javascript" src="js/malgun_gothic_regular.typeface.js"></script>
<script type="text/javascript" src="js/orbit.js"></script>
<script type="text/javascript" src="js/physi.js"></script>
<script src="http://cdn.oesmith.co.uk/morris-0.4.3.min.js"></script>
<script type="text/javascript" src="js/jquery.shortcuts.min.js"></script>
<script type="text/javascript" src="js/curve_ani.js"></script>
<script type="text/javascript" src="js/index.js"></script>
<script type="text/javascript" src="http://jqueryrotate.googlecode.com/svn/trunk/jQueryRotate.js"></script>
</head>
<body>
<img id="img_logo" src="img/logo.png" width="243" height="74" />
<div id="info"></div>
	<div id="status">Mornitoring<br /><font size="2">Camera : <span id="span_camera"></span>
	<br />Speed : <input id="traffic_speed" value="0" />
	<br />Drop : <input id="drop_node" value="1" width="15" /> <span id="drop">GO!</span>
	<span id="track_node">Track_Node</span>
	
	</font>
	</div>
	<div id="dashboard_arrow">
		<img id="dashboard_arrow_img" src="img/arrow.png" width="55" height="101" />
	</div>
	<div id="dashboard_hover">
		
	</div>
	<div id="dashboard">
	</div>

	<div id="graphboard">
	</div>	

<div id="graphboard_content">
<font size="4" color="#c6c6c6" ><strong><span id="graphboard_label"></span>Graph Board</strong></font><br /><br />
<span id="btn_c_graphb" style="position:absolute;top:0px; right:0px"><img src="img/btn_close_2.png" width="20" height="20" /></span>
<div id="board_type_l" class="board_type" style="position:relative;float:left; padding-top:6px; margin-top:5px; border:1px solid #b5b5b5; margin-left:183px; border-top-left-radius:15px;border-bottom-left-radius:15px; width:100px; height:19px; text-align:center; font-size:12px " alt="_m">Month View</div>
<div id="board_type_c" class="board_type" style="position:relative; float:left; padding-top:6px; margin-top:5px; height:19px;width:100px; text-align:center;border:1px solid #b5b5b5; margin-left:-1px;font-size:12px" alt="_d">Day View</div>
<div id="board_type_r" class="board_type board_selected" style="position:relative;float:left; padding-top:6px; margin-top:5px; border:1px solid #b5b5b5; margin-left:-1px; border-top-right-radius:15px;border-bottom-right-radius:15px; width:100px; height:19px; text-align:center;font-size:12px " alt="">Realtime View</div>
<div style="width:515px;margin-left:100px;margin-top:10px; position:relative;float:left; height:250px; overflow:hidden">
<div id="board_graph_m" class="board_graph" style="width:515px; position:relative;float:left; height:250px;display:none" alt="m"></div>
<div id="board_graph_d" class="board_graph" style="width:515px; position:relative;float:left; height:250px;display:none" alt="d"></div>
<div id="board_graph_r" class="board_graph" style="width:515px; position:relative;float:left; height:250px;" alt=""></div>
</div>
<div style="width:100%; height:30px; position:relative; float:left;">
			<font  size="3" color="#1894a7"><img src="img/arrow_up.png" width="15" height="15" /><span id="info_uptcur_2"></span></font>&nbsp;
		<font  size="3" color="#cf3b6f"><img src="img/arrow_down.png" width="15" height="15" /><span id="info_downtcur_2"></span></font>
</div>
<div style="width:540px;margin-left:70px; height:90px; position:relative; float:left;  border-top:1px solid #b5b5b5 ">
<div style="width:90px; margin-top:10px; height:80px; position:relative;float:left; color:#b5b5b5; font-size:30px;font-family: Georgia, Times, 'Times New Roman', serif;"><i>Port<br/>Scan</i>
</div>
<div style="width:450px; height:60px; margin-top:30px; position:relative;float:left;color:#b5b5b5;font-size:15px;"><div id="scan_loading" style="width:20px; height:20px; border:white 1px solid; position:absolute; border-radius:20px; display:none;"></div><span id="ps_content" style="font-size:12px; color:#d1d1d1;margin-top:30px;"></span><div id="btn_scan" style="z-index:55;margin-top:20px;cursor:pointer;">SCAN</div></div>
</div>


</div>
	<div id="ipboard">
	</div>	

<div id="ipboard_content">
<font size="4" color="#c6c6c6" ><strong>IP Monitoring Board</strong></font><br /><br />
<span id="btn_c_ipb" style="position:absolute;top:0px; right:0px"><img src="img/btn_close_2.png" width="20" height="20" /></span>
	<div style="font-size:12px; width:100%; opacity:.7; margin:0 auto; position:relative; float:left">
				<?php
	
				for($i=0;$i<17;$i++){
						for($j=0;$j<15;$j++){
						$this_id = $i*15+$j+1;
							?>
							<div id="node_<?=$this_id?>" class="td_node td_board" bgcolor="#373737" style=" position:relative;float:left;margin:0 auto; height:27px; width:39px; cursor:pointer; color:white; overflow:hidden; margin-right:5px; margin-bottom:5px;" alt="<?=$this_id?>" name="">
							</div>
							<?php
						} 
				}
				?>
		
		</div>
	</div>

	</div>
	<div id="copyright">
	<img src="img/copyright.png" width="736" height="15" />
	</div>
	
	<div id="dashboard_content">
	<img src="img/title_1.png" width="165" height="29" />
	<div id="node_search">
		<input id="input_search" />
	</div>
	<div id="node_table">
	<table style="font-size:12px; width:100%">
				<?php
	
				for($i=0;$i<17;$i++){

						for($j=0;$j<15;$j++){
						$this_id = $i*15+$j+1;
							?>
							<div id="node_<?=$this_id?>" class="td_node" bgcolor="#373737" style="poition:relative;float:left;height:8px; width:9px; margin-right:2px; margin-bottom:2px; cursor:pointer; color:white" alt="<?=$this_id?>"></div>
							<?php
						}
				}
				?>
		
		</table>
		<div style="display:none;" id="table_load"></div>
	</div>
	<img id="btn_close" src="img/btn_close.png" width="20" height="20" />
	<img id="btn_ipmornitor" src="img/btn_popup.png" width="20" height="20" />
	<br /><br />
	<img id="title_3" src="img/title_3.png" width="165" height="29" />
	<div id="info_under">
		<div id="info_under_wrap"></div>
		<div id="info_under_content">
		<strong><font size="4" color="#3b3b3b" style="font-family: Georgia, Times, 'Times New Roman', serif;"><span id="info_ip"></span></font></strong><br />
		<font color="#4e4e4e" size="2"><i><span id="info_mac"></span></i><br/></font>
		<font  size="3" color="#5f5f5f"><span id="info_name"></span></font><br />
		<div id="graph_wrap"></div>
		<font  size="2" color="#1894a7"><img src="img/arrow_up.png" width="15" height="15" /><span id="info_uptcur"></span></font>&nbsp;
		<font  size="2" color="#cf3b6f"><img src="img/arrow_down.png" width="15" height="15" /><span id="info_downtcur"></span></font>
		<img id="btn_graphmornitor" src="img/btn_popup.png" width="20" height="20" />
		</div><br />

		<br />
		</div>
		<div id="mousemove_div" style="width:100%; height:20px; font-size:13px;font-family: Georgia, Times, 'Times New Roman', serif;color:#2d2d2d " >
		<i><span id="mouseup_ip">Select IP in Table</span></i>
	</div>
	<img id="title_7" src="img/title_7.png" width="165" height="29" /><br/>
	
	<div id="modify_under">
		<div id="modify_under_wrap"></div>
		<div id="modify_under_content">
				<div id="qos_wrap">
				QOS&nbsp;&nbsp;<font style="font-size:12px; opacity:.6; margin-top:2px; width:130px; text-align:right">(* Mbps)<span id="qos_test"></span></font><br />
				<span id="qos_1" class="btn_qos" alt="1">1</span><span id="qos_2" class="btn_qos" alt="2">3</span><span id="qos_3" class="btn_qos" alt="3">5</span><span id="qos_4" class="btn_qos" alt="4">7</span><span id="qos_5" class="btn_qos" style="text-align:left;padding-left:-1px;" alt="5">10</span><span id="qos_6" class="btn_qos" alt="6">X</span><br/>
				<!--<img id="submit_qos" width="15" height="15" style="opacity:.7;" src="img/btn_check.png" /> -->
				</div>
				<!--
				<div id="ps_wrap" style="margin-top:15px;">
				Port Scan&nbsp;&nbsp;<img id="btn_portscan" width="15" height="15" style="opacity:.7;" src="img/btn_refresh.png" /><br />
				<span id="ps_content" style="font-size:12px; color:#d1d1d1"></span>
				</div>
				-->
		</div>
	</div>	
	<img id="title_4" src="img/title_4.png" width="165" height="29" /><br/>
	
	<span class="option_txt"><i>&nbsp;&nbsp;3D FPS : <strong><span id="txt_fps"></span></strong></i></span>
	<div id="slide_fps_wrap" style="height:2px; width:150px; background:#303030; margin-top:8px; margin-left:5px; margin-bottom:15px; overflow:visible;">
	<div id="slide_fps" style="height:10px; width:10px; background:#ffffff;position:absolute;left:5px;margin-left:5px; margin-top:-4px;border-radius: 6px;-moz-border-radius: 6px;-webkit-border-radius: 6px; -moz-box-shadow:0px 1px 1px 1px #535353;-webkit-box-shadow: 0px 1px 1px 1px #535353;box-shadow:0px 1px 1px 1px #535353;"></div>	
	</div>


	<img id="title_5" src="img/title_5.png" width="165" height="29" /><br/>
	<span class="option_txt"><i>&nbsp;&nbsp;Count Of live IP : <strong><span id="txt_liveip"></span></strong></i></span>
	<div  style="height:2px; width:150px; background:#303030; margin-top:8px; margin-left:5px; overflow:visible;">
	<div id="slide_amount_snow" style="height:10px; width:10px; background:#ffffff;position:absolute;left:0;margin-left:5px; margin-top:-4px;border-radius: 6px;-moz-border-radius: 6px;-webkit-border-radius: 6px; -moz-box-shadow:0px 1px 1px 1px #535353;-webkit-box-shadow: 0px 1px 1px 1px #535353;box-shadow:0px 1px 1px 1px #535353;"></div>	
	</div>
	<span id="test"></span>
	<!--
	<div id="graph_live"></div>
	-->
<br />
	<img id="btn_signout" style="position:absolute; bottom:2px; left:0px;" class="pointer" src="img/btn_lock.png" alt="ip" width="35" height="35" />
	<img id="show_type" style="position:absolute; bottom:2px; left:78px; opacity:.7" src="img/view_ip.png" alt="ip" width="92" height="35" />
	</div>

	<div id="zoom_wrap" style="color:white; border-radius: 15px;-moz-border-radius: 15px;-webkit-border-radius: 15px; width:70px; height:20px; border:1px solid white; position:absolute; bottom:50px; left:50px; padding:5px 5px; font-size:17px;">
		<img src="img/search.png" width="20" height="20" /> <span id="zoom_plus" style="position:absolute;cursor:pointer;font-size:25px;left:33px; top : 2px;">+</span> <span id="zoom_minor" style="position:absolute;cursor:pointer;font-size:25px;left:59px; top :0px;">-</span>
	</div>
	<div id="trash_wrap" style="position:absolute; bottom:105px; left:40px; opacity:0; display:none; z-index:50;"><img id="tr_img" src="img/tr_0.png" width="100" height="100" /></div>
	<div id="tis" style="width:1px; height:1px;position:absolute; display:none;border-radius: 100px;-moz-border-radius: 100px;-webkit-border-radius: 100px; background :#25c5dd; opacity:.7; z-index:55;"></div>

	<div id="select_id_wrap" style="width:100%; height:50px; text-align:center; color:white;font-size:13px;font-family: Georgia, Times, 'Times New Roman', serif; font-size:40px; margin-top:50px; opacity:0; position:absolute;">
		<font style="text-shadow: 1px 1px 10px #000000;"><i>Select : <span id="select_id"></span></i></font>
	</div>
	
	<div id="black_wrap"><video id="load_video" style="position:relative;" width="60%" src="video/loading.mp4" autoplay="YED"> </video><br /><span id="btn_skip"><font color="#868686">SKIP</font></span></div>
	<div id="sc_wrap" style="position:absolute; bottom:40px; left:130px; width:406px; height:199px; z-index:50; display:none; opacity:.8"><img id="title_5" src="img/sc_wrap.png" width="406" height="199" /></div>

<div id="canvas"</div></body>