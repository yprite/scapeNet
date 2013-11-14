<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<meta name="Generator" content="SeoSeungHyun WebKit">
<title>Scapenet</title>
<link rel="stylesheet" type="text/css" charset="UTF-8" href="css/morris.css" />
<link rel="stylesheet" type="text/css" charset="UTF-8" href="css/index.css" />
<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.10.1/jquery.min.js"></script>
<script src="http://code.jquery.com/ui/1.10.3/jquery-ui.js"></script>
<script type="text/javascript" src="js/raphael.js"></script>
<script type="text/javascript" src="js/morris.min.js"></script>
<script type="text/javascript" src="js/index.js"></script>
</head>

<body>

<div id="header_wrap">
	<div id="logo_wrap" class="btn_dashboard"><img src="img/logo.png" alt="scapenet" width="176" height="65" /></div>
	<div id="func_wrap">&nbsp;&nbsp;&nbsp;<img id="btn_func_terminer" class="func_btn" src="img/func_terminer.png" alt="terminer" width="33" height="33" /></div>
	<div id="desk_wrap">
			<div id="status_list"><img src="img/status_list.png" width="70" height="70" /></div>
			<div id="status_count"><div id="status_count_alert">1</div><img id="status_on" src="http://sshdb.com/ssm/status_font.php?q=26" width="70" height="70" /></div>
	</div>

</div>
<div id="terminer_wrap">
	<input id="terminer_area" value="Scapenet > " />
</div>
<div id="wrap">
<div id="navi_wrap">
	<div id="search">
		<input id="input_search" type="text" /><img id="btn_search" src="img/btn_search.png" width="25" height="25" alt="Search" />
	</div>
	<div id="mornitor_toggle">︿</div>
	<div id="mornitor_wrap">
	<div id="mornitor_content">
	- Count of live IP : <span id="txt_mor_livecount">10</span><br />
	- Network Traffic : <span id="txt_mor_traffic"></span><br /><br />
	- Status IP : <span id="txt_mornitor" style="font-size:10px;"></span>
	
	</div>
	</div>
	<div id="navi">
	<div id="navi_t_dashboard" class="navi_title"><strong id="btn_dashboard" class="btn_dashboard">Dashboard</strong></div>
	<div id="navi_t_dashboard" class="navi_title"><strong>Mornitoring</strong></div>
		<ul>
		<li class="li_1" alt="ipm">IP-Mapping</li>
		<li class="li_2">Analytics IP</li>
		<li class="li_1">Table</li>
		<li class="li_2">test</li>
		<li class="li_1">test</li>


		</ul>
	</div>	

</div>


<div id="content_wrap">
	<div id="info_traffic_day_wrap" class="dashboard_wrap content_main">
	<div id="info_traffic_day_title" class="dashboard_title"><h2>Traffic Of Today</h2></div>
	<div id="info_traffic_day" class="dashboard_content"></div>
	</div>
	
	<div id="info_donut_wrap" class="dashboard_wrap  content_main">
	<div id="info_donut_title" class="dashboard_title"><h2>Access Time</h2></div>
	<div id="info_donut" class="dashboard_content">
		<div id="info_donut_1"></div>
		<div id="info_donut_2"></div>
		<div id="info_donut_3"></div>
	</div>
	</div>
	
	<div id="ip_mapping_wrap" class="dashboard_wrap ipm_main">

	<div id="info_ip_title" class="dashboard_title"><h2>Information Of IP</h2></div>
	<div id="ip_info_content" class="dashboard_content">
		test
	</div>
	<div id="ip_map_wrap" class="dashboard_content">
		<?php
			for($i=0;$i<255;$i++){
			$node_status = rand(0,3);
				?>
				<div id="test_<?=$i?>" class="map_node map_node_<?=$node_status?>" alt="<?=$i?>"></div>
				<?php
			}
		?>
		<br /><br /><br />
	</div>
	</div>	
	
	
	
	<div id="table_wrap" class="dashboard_wrap table_main">

	<div id="table_title" class="dashboard_title"><h2>Information Of IP</h2></div>
	<div id="table_content" class="dashboard_content">
		test
	</div>
	
	</div>	
	
	
	
</div>
</div>
<div id="test_timer"></div>
</body>