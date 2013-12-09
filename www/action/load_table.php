<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<?php
$q = $_GET['q'];
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
	$arr[$info['pid']]['name'] = $info['name'];
	$arr[$info['pid']]['port'] = $info['port'];
	$arr[$info['pid']]['qos'] = $info['qos'];
	if($info['pid'] == 252){
		$arr[1]['up_traffic_cur'] = $info['up_traffic_cur'];
		$arr[1]['down_traffic_cur'] = $info['down_traffic_cur'];
		$arr[1]['up_traffic_limit'] = $info['up_traffic_limit'];
		$arr[1]['down_traffic_limit'] = $info['down_traffic_limit'];
		$arr[1]['isStatus'] = $info['isStatus'];
		$arr[1]['port'] = $info['port'];
		$arr[1]['qos'] = $info['qos'];
	}
}
mysql_close($connect);

?>

<table style="font-size:12px; width:100%">
			<?php

			for($i=0;$i<17;$i++){
				?>
				<tr style="border:1px solid black;">
					<?php
					for($j=0;$j<15;$j++){
					$this_id = $i*15+$j+1;
					$this_color;
		 			if($arr[$this_id]['pid']== 1){
			 			$arr[$this_id]['isStatus'] = 1;
		 			}
					switch($arr[$this_id]['isStatus']){
						case 0 : $this_color='#373737'; break;
						case 1 : $this_color='#25c5dd'; break;
						case 2 : $this_color='#dd2548'; break;
						case 3 : $this_color='#dd2548'; break;
						case 4 : $this_color='#d6cb52'; break;
					}
		 			if($arr[$this_id]['pid'] >=150 && $arr[$this_id]['pid'] <=229){
			 			$arr[$this_id]['name'] = 'WiFi IP';
		 			}
		 			if(!$arr[$this_id]['name']){
			 			$arr[$this_id]['name'] = '알 수 없는';
		 			}
					$explode = explode('.', $arr[$this_id]['ip']);
					if(!$q || $q == $explode[0].'.'.$explode[1].'.'.$explode[2].'.'){
						
					}else{
						$pos = strpos($arr[$this_id]['ip'], $q);
						$pos2 = strpos($arr[$this_id]['name'], $q);
						if ($pos !== false || $pos2 !== false) {
							switch($arr[$this_id]['isStatus']){
								case 0 : $this_color='#8b8b8b'; break;
								case 1 : $this_color='#ade5ee'; break;
								case 2 : $this_color='#efa5b3'; break;
								case 3 : $this_color='#efa5b3'; break;
								case 4 : $this_color='#d6cb52'; break;
							}
			 			}
			 			if ($q=='서버' || $q =='server'){
							$pos3 = strpos($arr[$this_id]['port'], '80P');
							if ($pos3 !== false){
							$this_color='orange';
							}
						}else if ($q=='ftp' || $q =='파일'){
							$pos4 = strpos($arr[$this_id]['port'], '21P');
							if ($pos4 !== false){
							$this_color='yellow';
							}
						}else if ($q=='ssh' || $q =='sftp'){
							if (strpos($arr[$this_id]['port'], '22P') !== false){
							$this_color='white';
							}
						}else if ($q=='원격' || $q =='원격 데스크탑' || $q =='원격 데스크톱'){
							if (strpos($arr[$this_id]['port'], '3389P') !== false){
							$this_color='b';
							}
						}
		 			}
		 			
						?>
						<td id="load_node_<?=$this_id?>" class="load_td_node" bgcolor="<?=$this_color?>" style="height:5px; width:5px; cursor:pointer; color:white" alt="<?=$this_id?>">
						<span id="load_node_<?=$this_id?>_pid" class="node_hidden"><?=$arr[$this_id]['pid']?></span>
						<span id="load_node_<?=$this_id?>_ip" class="node_hidden"><?=$arr[$this_id]['ip']?></span>
						<span id="load_node_<?=$this_id?>_mac" class="node_hidden"><?=$arr[$this_id]['mac']?></span>
						<span id="load_node_<?=$this_id?>_uptcur" class="node_hidden"><?=$arr[$this_id]['up_traffic_cur']?></span>
						<span id="load_node_<?=$this_id?>_downtcur" class="node_hidden"><?=$arr[$this_id]['down_traffic_cur']?></span>
						<span id="load_node_<?=$this_id?>_status" class="node_hidden"><?=$arr[$this_id]['isStatus']?></span>
						<span id="load_node_<?=$this_id?>_name" class="node_hidden"><?=$arr[$this_id]['name']?></span>
						<span id="load_node_<?=$this_id?>_port" class="node_hidden"><?=$arr[$this_id]['port']?></span>
						<span id="load_node_<?=$this_id?>_qos" class="node_hidden"><?=$arr[$this_id]['qos']?></span>
						</td>
						<?php
					}
					?>
				</tr>
				<?php
			}
			?>
		
		</table>