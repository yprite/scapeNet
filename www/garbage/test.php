<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<?php

$hostname = "127.0.0.1";
$username = "root";
$password = "1234";
$dbname = "scapenet";

$connect = mysql_connect($hostname, $username, $password) or die("MySQL Server 연결에 실패했습니다");
$result = mysql_select_db($dbname,$connect);

if($result) {

}
else {
 echo("MySQL Server Connect 실패");
}

mysql_query("set names utf8");     // 결과값이 한글인 경우 사용

$sql="SELECT * FROM ip_data;";
$rs =  mysql_query($sql, $connect);   // sql문 실행

while($info=mysql_fetch_array($rs)){
	$arr[$info['pid']]['pid'] = $info['pid'];
	$arr[$info['pid']]['ip'] = $info['ip'];
	$arr[$info['pid']]['mac'] = $info['mac'];
	$arr[$info['pid']]['up_traffic_cur'] = $info['up_traffic_cur'];
	$arr[$info['pid']]['down_traffic_cur'] = $info['down_traffic_cur'];
	$arr[$info['pid']]['up_traffic_limit'] = $info['up_traffic_limit'];
	$arr[$info['pid']]['down_traffic_limit'] = $info['down_traffic_limit'];
	$arr[$info['pid']]['isStatus'] = $info['isStatus'];
}
mysql_close($connect);

?>
<script>
$(document).ready(function(){
	 $('.td_node').draggable({helper:'clone'});
});
</script>
<table style="font-size:12px; width:100%">
			<?php

			for($i=0;$i<17;$i++){
				?>
				<tr style="border:1px solid black;">
					<?php
					for($j=0;$j<15;$j++){
					$this_id = $i*15+$j;
					$this_color;
					switch($arr[$this_id]['isStatus']){
						case 0 : $this_color='#373737'; break;
						case 1 : $this_color='#25c5dd'; break;
						case 2 : $this_color='#dd2548'; break;
						case 3 : $this_color='#dd2548'; break;
					}
						?>
						<td id="node_<?=$this_id?>" class="load_td_node" bgcolor="<?=$this_color?>" style="height:5px; width:5px; cursor:pointer; color:white" alt="<?=$this_id?>">
						<span id="node_<?=$this_id?>_ip" class="node_hidden"><?=$arr[$this_id]['ip']?></span>
						<span id="node_<?=$this_id?>_mac" class="node_hidden"><?=$arr[$this_id]['mac']?></span>
						<span id="node_<?=$this_id?>_uptcur" class="node_hidden"><?=$arr[$this_id]['up_traffic_cur']?></span>
						<span id="node_<?=$this_id?>_downtcur" class="node_hidden"><?=$arr[$this_id]['down_traffic_cur']?></span>
						</td>
						<?php
					}
					?>
				</tr>
				<?php
			}
			?>
		
		</table>