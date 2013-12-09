$(document).ready(function(){
	
	var width, height, renderer, scene, camera, projector, controls,loader;
	var node = new Array();	
	var now_dropping = 0;	
	var now_tracking = 0;
	var spotLight5;
	var text_ma = new Array();
	var search_me ='';
	var ipmornitor = 0;
	var graphmornitor = 0;
	var show_option = 'ip';
	var count_ip = 0;
	var now_fps = 10;
	var gm_key = 0;
	var sh_key = 0;
	var now_upping = 0;
	var now_select = new Array();
	    var port_arr = new Array();
	   var now_graph_status = 'r';
port_arr[1] = "1 -TCPMUX";
port_arr[7] = "7 -ECHO 프로토콜";
port_arr[9] = "9 -DISCARD 프로토콜";
port_arr[13] = "13 -DAYTIME 프로토콜"	;
port_arr[17] = "17 -QOTD 프로토콜";
port_arr[19] = "19 -CHARGEN 프로토콜"	;
port_arr[20] = "20 -FTP - 자료 포트";
port_arr[21] = "21 -FTP - 제어 포트";
port_arr[22] = "22 -SSH - ssh scp, sftp같은 프로토콜 및 포트 포워딩";
port_arr[23] = "23 -텔넷 프로토콜 - 암호화되지 않은 텍스트 통신";
port_arr[25] = "25 -SMTP - 이메일 전송에 사용";
port_arr[37] = "37 -TIME 프로토콜";
port_arr[53] = "53 -DNS";
port_arr[70] = "70 -고퍼 프로토콜";
port_arr[79] = "79 -Finger 프로토콜"	;
port_arr[80] = "80 -HTTP - 웹 페이지 전송";
port_arr[88] = "88 -케르베로스 - 인증 에이전트";
port_arr[109] = "109 -POP2 - 전자우편 가져오기에 사용";
port_arr[110] = "110 -POP3 - 전자우편 가져오기에 사용";
port_arr[113] = "113 -ident - 예전 서버 인증 시스템, 현재는 IRC 서버에서 사용자 인증에 사용";
port_arr[119] = "119 -NNTP - 뉴스 그룹 메시지 가져오기에 사용";
port_arr[139] = "139 -NetBIOS";
port_arr[143] = "143 -IMAP4 - 이메일 가져오기에 사용";
port_arr[179] = "179 -BGP";
port_arr[194] = "194 -IRC";
port_arr[389] = "389 -LDAP";
port_arr[443] = "443 -HTTPS - HTTP over SSL (암호화 전송)";
port_arr[445] = "445 -Microsoft-DS";
port_arr[465] = "465 -SSL 위의 SMTP - Cisco 프로토콜과 충돌";
port_arr[540] = "540 -UUCP";
port_arr[542] = "542 -상용 RFC";
port_arr[587] = "587 -(SMTP)";
port_arr[591] = "591 -파일메이커 6.0 Web Sharing";
port_arr[636] = "636 -SSL 위의 LDAP (암호화된 전송)";
port_arr[666] = "666 -id 소프트웨어의 둠 멀티플레이어 게임";
port_arr[873] = "873 -rsync 파일 동기화 프로토콜";
port_arr[981] = "981 -SofaWare Technologies Checkpoint Firewall-1 소프트웨어 내장 방화벽의 원격 HTTPS 관리";
port_arr[993] = "993 -SSL 위의 IMAP4 (암호화 전송)";
port_arr[995] = "995 -SSL 위의 POP3 (암호화 전송)";
port_arr[3389] = "3389 -원격 데스크탑";

	function print_r(array) {
    var str='';

    for(var i in array) {

        str += '['+ i+':'+array[i]+'] '
    }
    return str;
}
	text_ma[1] = new THREE.MeshPhongMaterial({
        // light
        specular: '#ffdc36',
        // intermediate
        color: '#ff36a8',
        // dark
        emissive: '#006063',
        shininess: 100 
      })
text_ma[2] = new THREE.MeshPhongMaterial({specular: '#ffdc36',color: '#fd9b3b',emissive: '#d6410d',shininess: 100})
text_ma[3] = new THREE.MeshPhongMaterial({specular: '#36ffba',color: '#df5fbf',emissive: '#f313b6',shininess: 100})
text_ma[4] = new THREE.MeshPhongMaterial({specular: '#36ffba',color: '#6dd131',emissive: '#a8ca77',shininess: 100})
text_ma[5] = new THREE.MeshPhongMaterial({specular: '#e9e9e9',color: '#dedede',emissive: '#b0b0b0',shininess: 100})
	//초기화
	init();
	//애니메이션 호출
	main();
	
	function select_id(id){
		$('#select_id').html(id)
		$('#select_id_wrap').stop().show().animate({'opacity':.6},function(){
			$(this).delay(3000).animate({'opacity':0},function(){
				$(this).hide();
			})
		})
	}
	function main(){
		setTimeout(function(){
					 requestAnimationFrame( pre_animate );
					 main();
		}, 1000 / now_fps );
	}		
	

	$('#info').css('opacity',.5)

	//초기화 함수
					function random_number(num){
				return Math.floor(Math.random() * num) + 1;
				}
	function create_node(id,x,y,z,text){
/*
				var tree_leaf_loader = new THREE.JSONLoader();
					tree_leaf_loader.load( "obj/sh_tree1.js", function( geometry ) {
					node[id] = new THREE.Mesh( geometry, new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/nz.jpg' ) } ));
					node[id].scale.set( 0.1, 0.1, 0.1);
					node[id].position.set(x,y,z)
					scene.add( node[id] );
					} );
					*/
	var text2 = new THREE.TextGeometry(text, {size: (3*0.1*(random_number(10)))+2,height: .8,font : "malgun gothic"});
	node[id] = new THREE.Mesh(text2,text_ma[random_number(5)]);
   // node[id].scale.set(1,1,3)
    node[id].position.set(x,y,z);
    scene.add(node[id]);
    
/*
				var apple = new THREE.OBJLoader( manager );
				apple.load( 'obj/apple3.obj', function ( object ) {
					object.traverse( function ( child ) {
						if ( child instanceof THREE.Mesh ) {
							child.scale.set(0.1,0.1,0.1)
							child.position.set(x,y,z)
							node[id] = child
							
						}

					} );
					scene.add( object );
				} );	
*/
}
	
	function init(){
		var width = parseInt($('#canvas').width()), height =  parseInt($(window).height() - $('#canvas').offset().top);
		$('#dashboard').height($(window).height() - $('#dashboard').offset().top-30);
		//$('#ipboard_content').height($(window).height() - $('#ipboard_content').offset().top-20);
		//$('#ipboard').height($(window).height() - $('#ipboard').offset().top-60)
		//$('#graphboard_content').height($(window).height() - $('#graphboard_content').offset().top-20);
		//$('#graphboard').height($(window).height() - $('#graphboard').offset().top-60)
		$('#load_video').css('margin-top',$(window).height()/2-$('#load_video').height()/2+'px')
		$('#black_wrap').height(height)
		$('#dashboard_hover').height($(window).height() - $('#dashboard').offset().top-5)
				$('#node_255').hide();
		var dashboard_on = 0;
		$('#dashboard_hover').hover(function(){
				$('#dashboard_arrow').css({'opacity':0,'left':$(window).width()+'px','top':$(document).height()/2-60}).animate({'left':$('#dashboard_arrow').offset().left-55+'px','opacity':.8});
		},function(){
				$('#dashboard_arrow').animate({'opacity':0,'left':$(window).width()+'px','top':$(document).height()/2-60})
		})
		$('#dashboard_hover').click(function(){
			if(dashboard_on == 0){
$('#dashboard').show();
$('#dashboard').height($(window).height() - $('#dashboard').offset().top-30);
$('#dashboard_content').show();
$('#dashboard_content').height($(window).height() - $('#dashboard').offset().top-60);
$('#dashboard_arrow_img').attr('src','img/arrow_2.png');
				dashboard_on = 1;
				$('#input_search').focus();
			}else{
$('#dashboard').hide();
$('#dashboard_content').hide();
$('#dashboard_arrow_img').attr('src','img/arrow.png');
				dashboard_on = 0;
				$('#input_search').blur();
			}
		});
		//!렌더러 생성
		renderer = new THREE.WebGLRenderer({antialias: true});
		//renderer = new THREE.WebGLRenderer();
		renderer.setSize(width, height);
		$('#canvas')[0].appendChild(renderer.domElement);	//렌더러 사이즈
		
		//!스크린 생성
		scene = new THREE.Scene();
		scene.fog = new THREE.FogExp2( 0x000000, 0.00097 );

		//scene.fog = new THREE.FogExp2( 0x000000, 0.0009 );
			
		
		// texture*
				var manager = new THREE.LoadingManager();
				manager.onProgress = function ( item, loaded, total ) {

					console.log( item, loaded, total );

				};

				// model
				
				//나뭇가지 Loader
				var loader2 = new THREE.OBJLoader( manager );
				loader2.load( 'obj/tree.obj', function ( object ) {
					object.traverse( function ( child ) {
						if ( child instanceof THREE.Mesh ) {
							child.material = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'obj/branch.png' ),transparent: true,shading : "Lambert"} )
							child.material.depthWrite = false
							child.scale.set(2,2,2)
						}

					} );
					object.position.y = - 80;
					scene.add( object );
				} );
			


				
				//나뭇가지 Loader
				var loader5 = new THREE.OBJLoader( manager );
				loader5.load( 'obj/tree.obj', function ( object ) {
					object.traverse( function ( child ) {
						if ( child instanceof THREE.Mesh ) {
							child.material = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'obj/branch_white.png' ),transparent: true,shading : "Lambert"} )
							child.scale.set(2,2,2)
						}

					} );
					object.position.x = 250;
					object.position.y = - 80;
					object.position.z = - 250;
					scene.add( object );
				} );


var cylinder2 = new THREE.Mesh(new THREE.CylinderGeometry(1, 1.1, 70, 50, 50, false), new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/branch.png' ),bumpMap: THREE.ImageUtils.loadTexture('obj/branch_white.png')} ));
     cylinder2.overdraw = true;
     cylinder2.position.set(251,-65,-250.1);
      scene.add(cylinder2);

	
				var loader_lamp = new THREE.OBJLoader( manager );
				loader_lamp.load( 'obj/STLamp.obj', function ( object ) {
					object.traverse( function ( child ) {
						if ( child instanceof THREE.Mesh ) {
							child.material = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/backgrounddetailed6.png' ),transparent: true,shininess: 100} )
							child.scale.set(50,50,50)
							child.position.set(-490,-80,-400)
							
						}

					} );
					scene.add( object );
				} );
				
				
				$('#table_load').load('action/load_table.php?q='+$('#input_search').val(),function(){
					var ip_split = $('#load_node_2_ip').html().split('.');
					var ip_glue = ip_split[0]+'.'+ip_split[1]+'.'+ip_split[2]+'.';
					$('#input_search').val(ip_glue);
for(var nn=1;nn<255;nn++){
if(parseInt($('#load_node_'+nn+'_status').html()) == 1){
	create_node(nn,-random_number(80)+random_number(80),random_number(80),random_number(50)-random_number(50),$('#load_node_'+nn+'_'+show_option).html());
}else{
}
}					
				});



$('#track_node').hover(function(){
	now_tracking = $('#drop_node').val();
	controls.zoomIn(1.5,1)
},function(){
	now_tracking = $('#drop_node').val();
	controls.zoomIn(1.5,2)
});

			
//노드 삽입
	
$('#drop').click(function(){
	now_dropping = $('#drop_node').val();
});

			
var cylinder = new THREE.Mesh(new THREE.CylinderGeometry(1.6, 1.9, 70, 50, 50, false), new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/branch.png' ),bumpMap: THREE.ImageUtils.loadTexture('img/branch.png')} ));
     cylinder.overdraw = true;
     cylinder.position.set(0.5,-64,-0.1);
      scene.add(cylinder);
/*
				var loader3 = new THREE.OBJLoader( manager );
				loader3.load( 'obj/tree_leaf2.obj', function ( object ) {
					object.traverse( function ( child ) {
						if ( child instanceof THREE.Mesh ) {
							child.material = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'obj/branch.png' ),transparent: true,shading : "Lambert"} )
							child.material.depthWrite = false
							child.scale.set(9,9,9)
						}

					} );
					object.position.y = - 80;
					object.position.x = - 80;
					object.position.set(-290,-80,-375);
					scene.add( object );
				} );
				*/
				
				create_stree(3,360,-80);
				create_stree(1.5,300,-20);
				
				
function create_stree(s,x,y){
					var other_tree_1 = new THREE.OBJLoader( manager );
					other_tree_1.load( 'obj/tree.obj', function ( object ) {
						object.traverse( function ( child ) {
							if ( child instanceof THREE.Mesh ) {
								child.material = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'obj/branch.png' ),transparent: true,shading : "Lambert"} )
								child.material.depthWrite = false
								child.scale.set(s,s,s)
							}
	
						} );
						object.position.set(x,y,-370)
						scene.add( object );
					} );					
}
					
				//랜덤 함수 
				
				
				tree_leaf_loader = new THREE.JSONLoader();
					tree_leaf_loader.load( "obj/tree_leaf.js", function( geometry ) {
					tree_leaf_mesh = new THREE.Mesh( geometry, new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/nz.jpg' ) } ));
					tree_leaf_mesh.scale.set( 1, 1, 1);
					tree_leaf_mesh.position.set(0,-80,10)
					scene.add( tree_leaf_mesh );
					} );
					
				


					
					/*
				tree_leaf_loader2 = new THREE.JSONLoader();
					tree_leaf_loader2.load( "obj/tree_leaf.js", function( geometry ) {	
					tree_leaf_mesh2 = new THREE.Mesh( geometry, new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/lavatile.jpg' ) } ));
					tree_leaf_mesh2.scale.set( 1, 1, 1);
					tree_leaf_mesh2.position.set(-20,-70,5)
					tree_leaf_mesh2.rotation.set(-1,-1.5,-1)
					scene.add( tree_leaf_mesh2 );
					} );
					
					
				tree_leaf_loader3 = new THREE.JSONLoader();
					tree_leaf_loader3.load( "obj/tree_leaf.js", function( geometry ) {	
					tree_leaf_mesh3 = new THREE.Mesh( geometry, new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/nz.jpg' ) } ));
					tree_leaf_mesh3.scale.set( 1, 1, 1);
					tree_leaf_mesh3.position.set(-5,-85,-5)
					tree_leaf_mesh3.rotation.set(-1,-1.7,-1.1)
					scene.add( tree_leaf_mesh3 );
					} );


				tree_leaf_loader4 = new THREE.JSONLoader();
					tree_leaf_loader4.load( "obj/tree_leaf.js", function( geometry ) {	
					tree_leaf_mesh4 = new THREE.Mesh( geometry, new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/fanta.png' ) } ));
					tree_leaf_mesh4.scale.set( 1, 1, 1);
					tree_leaf_mesh4.position.set(-5,-85,-5)
					tree_leaf_mesh4.rotation.set(-1,-1.5,-1.1)
					scene.add( tree_leaf_mesh4 );
					} );			
					*/	
				/*
var leaf_texture = new THREE.ImageUtils.loadTexture("img/leaf2.png");

	var leaf_numParticles = 50,
        leaf_width = 70,
        leaf_height = 70,
        leaf_depth = 70,
        leaf_systemGeometry = new THREE.Geometry(),
        leaf_systemMaterial = new THREE.ParticleSystemMaterial({ size: 13, map: leaf_texture, transparent: true});
                        
                for( var i = 0; i < leaf_numParticles; i++ ) {
                        var leaf_vertex = new THREE.Vector3(rand( leaf_width ),Math.random() * leaf_height,rand( leaf_depth ) );

                        leaf_systemGeometry.vertices.push( leaf_vertex );
                        leaf_systemGeometry.vertices[i].ry=rand(40);
                }
                var leaf_particleSystem = new THREE.ParticleSystem( leaf_systemGeometry, leaf_systemMaterial );
                leaf_particleSystem.position.set = (0,-80,30);
                
                
            scene.add( leaf_particleSystem );
*/

			
			
		//카메라 객체 생성
		var angle=40;
		var aspect = width/height;
		var near = 1;
		var far = 5000;
		
		camera = new THREE.PerspectiveCamera(angle,aspect,near,far);
		camera.position.set(10,0,670);
		camera.rotation.set(0,0,0);
		scene.add(camera);
					
		controls = new THREE.OrbitControls( camera, renderer.domElement );
		controls.maxPolarAngle = 90*Math.PI/180; 
		controls.minPolarAngle = 70*Math.PI/180; 
		//controls.minDistance = 0;
		//controls.maxDistance = 1;
controls.maxDistance = 610;
controls.minDistance = 210;
controls.momentumScalingFactor = 0.005;
		//Light 객체 생성
		
		
		var spotLight = new THREE.PointLight( 0xf7ffa3,0.3,700 );
		spotLight.position.set( 0, -50, 0 );
		spotLight.castShadow = true;
		scene.add( spotLight );
		
		var spotLight2 = new THREE.PointLight( 0xfaac23,4.3,700 );
		spotLight2.position.set( 0,-150, -400 );
		scene.add( spotLight2 );
		
		var spotLight3 = new THREE.PointLight( 0xffffff,0.5,700 );
		spotLight3.position.set( 0, 0, 10 );
		spotLight3.castShadow = true;
		scene.add( spotLight3 );
					
		var spotLight4 = new THREE.PointLight( 0xfeffaa,0.5,500 );
		spotLight4.position.set( 0, 150, 0 );
		spotLight4.castShadow = true;
		scene.add( spotLight4 );
		
		spotLight5 = new THREE.PointLight( 0xfeffaa,3,400 );
		spotLight5.position.set(0,-80,0);
		spotLight5.castShadow = true;
		scene.add( spotLight5 );
		/*
		var spotLight6 = new THREE.PointLight( 0xffffff,2,800 );
		spotLight6.position.set( 0,15, -370 );
		spotLight6.castShadow = true;
		scene.add( spotLight6 );		
*/
  		
		var spotLight7 = new THREE.SpotLight( 0xfff88d ,20, 400, 45, 30)
		spotLight7.position.set(-490,0,-300);
			spotLight7.castShadow = true;
		spotLight7.target.y = -80;
		
		spotLight7.shadowCameraNear = 500;
		spotLight7.shadowCameraFar = 4000;
		spotLight7.shadowCameraFov = 70;
		scene.add( spotLight7 );	

		spotLight8 = new THREE.PointLight( 0xfff88d,20,14 );
		spotLight8.position.set( -485,85, -390 );
		spotLight8.rotation.set(0,0,0);
		spotLight8.castShadow = true;
		scene.add( spotLight8 );		

		var spotLight9 = new THREE.PointLight( 0xfff88d,10,12 );
		spotLight9.position.set( -497,80, -372 );
		spotLight9.rotation.set(0,0,0);
		spotLight9.castShadow = true;
		scene.add( spotLight9 );				

		var spotLight10 = new THREE.PointLight( 0xfff88d,6,12 );
		spotLight10.position.set( -462,80, -386 );
		spotLight10.rotation.set(0,0,0);
		spotLight10.castShadow = true;
		scene.add( spotLight10 );	
		
		
		var spotLight11 = new THREE.SpotLight( 0xffffff ,1.1, 900, 20, 10)
		spotLight11.position.set(0,120,200);
			spotLight11.castShadow = true;
		spotLight11.target.y=0;
		spotLight11.target.z=0;
		
		spotLight11.shadowCameraNear = 500;
		spotLight11.shadowCameraFar = 4000;
		spotLight11.shadowCameraFov = 70;
		scene.add( spotLight11 );	
						
					sphere = new THREE.Mesh(
    new THREE.SphereGeometry(10,10,10),
    new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/grow.jpg' ) } ));
  //sphere.position.z -= 100;
  sphere.position.set(0,-200,0);
  scene.add(sphere);
  
  
		/*
		GlowPlage = new THREE.PlaneGeometry(1400, 800) ;
		GlowPlage_material = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/grow.jpg' ),bumpMap: THREE.ImageUtils.loadTexture('img/grow_bump.jpg'), bumpScale:   2 } );
		GlowPlage_mesh = new THREE.Mesh( GlowPlage, GlowPlage_material ) ;
		GlowPlage_mesh.position.set(0,-35,-580);
		GlowPlage_mesh.rotation.set(-1.5,0,180 * Math.PI / 180);
		GlowPlage_mesh.receiveShadow = true;
		scene.add( GlowPlage_mesh );
		*/
		GlowPlane2 = new THREE.PlaneGeometry(1400, 900) ;
		GlowPlane2_material = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/grow.jpg' ),bumpMap: THREE.ImageUtils.loadTexture('img/grow_bump.png'), bumpScale: 0.8 } );
		GlowPlane2_mesh = new THREE.Mesh( GlowPlane2, GlowPlane2_material ) ;
		GlowPlane2_mesh.position.set(0,-90,-50);
		GlowPlane2_mesh.rotation.set(-1.5,0,0);
		GlowPlane2_mesh.receiveShadow = true;
		scene.add( GlowPlane2_mesh );

		
			// spotlight #1 -- yellow, dark shadow
		/*
				SkyPlane = new THREE.PlaneGeometry(1400, 800);
		SkyPlane_material = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/sky.jpg' )} )
		*/
		SkyPlane = new THREE.PlaneGeometry(2100, 1300);
		SkyPlane_material = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/nz.jpg' )} )
		SkyPlane_mesh = new THREE.Mesh( SkyPlane, SkyPlane_material ) ;
		SkyPlane_mesh.position.set(0,100,-720);
		SkyPlane_mesh.rotation.set(0,0,0);
		SkyPlane_mesh.receiveShadow = true;
		scene.add( SkyPlane_mesh );
		
		
		TreesPlane = new THREE.PlaneGeometry(900, 400);
		TreesPlane_material = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture( 'img/trees.png' ),transparent: true} )
		TreesPlane_mesh = new THREE.Mesh( TreesPlane, TreesPlane_material ) ;
		TreesPlane_mesh.position.set(-300,60,-700);
		scene.add( TreesPlane_mesh );
		

		MountainPlane = new THREE.PlaneGeometry(1400, 120);
		MountainPlane_material = new THREE.MeshPhongMaterial( {side:THREE.BackSide,depthWrite: false, map: THREE.ImageUtils.loadTexture( 'img/mountain.png' ),transparent: true} )
		MountainPlane_mesh = new THREE.Mesh( MountainPlane, MountainPlane_material ) ;
		MountainPlane_mesh.position.set(0,-20,-450);
		MountainPlane_mesh.rotation.set(-0.3,180 * Math.PI / 180,0);
	//	MountainPlane_mesh.receiveShadow = true;
		scene.add( MountainPlane_mesh );	
		
		
		var geo_box = new THREE.CubeGeometry( 60, 60, 40);
	    var material_box = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture('img/box.jpg'),bumpMap: THREE.ImageUtils.loadTexture('img/grow_bump.jpg'), bumpScale:   0.5 } );;
	 
	    mesh_box = new THREE.Mesh(geo_box, material_box );
	    mesh_box.position.set(-350,-50,-300);
	    mesh_box.rotation.set(-1.5,0,20 * Math.PI / 180);
	    scene.add( mesh_box );
	    
		var geo_box2 = new THREE.CubeGeometry( 60, 60, 40);
	    var material_box2 = new THREE.MeshPhongMaterial( { map: THREE.ImageUtils.loadTexture('img/box.jpg'),bumpMap: THREE.ImageUtils.loadTexture('img/grow_bump.jpg'), bumpScale:   0.5 } );;
	 
	    mesh_box2 = new THREE.Mesh(geo_box2, material_box2 );
	    mesh_box2.position.set(-400,-30,-300);
	    mesh_box2.rotation.set(-1.5,-47 * Math.PI / 180,-20 * Math.PI / 180);
	    scene.add( mesh_box2 );
	    
	     camera.position.x = -130
	     camera.position.y = 0
	     camera.position.z = 250
	     
	     //시작 영상
	     
var intro_time = 0;
	    setTimeout(function(){
		   	intro_time = 1;
	    }, 16000)
	    tt = setInterval(function(){
	    if(intro_time ==1 ){
		    camera.position.x += 0.06
		    camera.position.y += 0.008
		    camera.position.z += 0.22
	    }
		});

	    $('#black_wrap').delay(18000).animate({'opacity':0},7000,function(){
		    $(this).hide()
		    clearInterval(tt);
		    
	    });


	}
	
	$('#btn_skip').click(function(){
		clearInterval(tt);
		$('#black_wrap').stop();
		$('#black_wrap').hide();
		camera.position.set(10,0,670);
	});
	var radius = 150;
	var cos_a=0.005;
	
	function render() {
		renderer.render( scene, camera );
	}
	
	
	
	
	var snow_1_texture = new THREE.ImageUtils.loadTexture("img/snow.png");

	var snow_1_numParticles = 70,
        snow_1_width = 800,
        snow_1_height = 430,
        snow_1_depth = 200,
        snow_1_systemGeometry = new THREE.Geometry(),
        snow_1_systemMaterial = new THREE.ParticleBasicMaterial({ size: 50, sizeAttenuation: false, map: snow_1_texture, transparent: true, opacity :0.2,blending: THREE.AdditiveBlending});

                for( var i = 0; i < snow_1_numParticles ; i++ ) {
                        var snow_1_vertex = new THREE.Vector3(rand( snow_1_width ),Math.random() * snow_1_height,rand( snow_1_depth ) );

                        snow_1_systemGeometry.vertices.push( snow_1_vertex );
                }
                snow_1_particleSystem = new THREE.ParticleSystem( snow_1_systemGeometry, snow_1_systemMaterial );
                snow_1_particleSystem.position.y = -70;
                scene.add( snow_1_particleSystem );


	
	var snow_2_texture = new THREE.ImageUtils.loadTexture("img/snow.png");

	var snow_2_numParticles = 200,
        snow_2_width = 800,
        snow_2_height = 430,
        snow_2_depth = 500,
        snow_2_systemGeometry = new THREE.Geometry(),
        snow_2_systemMaterial = new THREE.ParticleBasicMaterial({ size: 10, sizeAttenuation: false,map: snow_2_texture, transparent: true,blending: THREE.AdditiveBlending});
                        
                for( var i = 0; i < snow_2_numParticles ; i++ ) {
                        var snow_2_vertex = new THREE.Vector3(rand( snow_2_width ),Math.random() * snow_2_height,rand( snow_2_depth ) );

                        snow_2_systemGeometry.vertices.push( snow_2_vertex );
                }
                snow_2_particleSystem = new THREE.ParticleSystem( snow_2_systemGeometry, snow_2_systemMaterial );
                snow_2_particleSystem.position.y = -70;
                scene.add( snow_2_particleSystem );
                


	var snow_3_texture = new THREE.ImageUtils.loadTexture("img/snow.png");

	var snow_3_numParticles = 200,
        snow_3_width = 800,
        snow_3_height = 430,
        snow_3_depth = 500,
        snow_3_systemGeometry = new THREE.Geometry(),
        snow_3_systemMaterial = new THREE.ParticleBasicMaterial({ size: 2,sizeAttenuation: false, opacity:0.7, color:0xffea00,blending: THREE.AdditiveBlending});
                        
                for( var i = 0; i < snow_3_numParticles ; i++ ) {
                        var snow_3_vertex = new THREE.Vector3(rand( snow_3_width ),Math.random() * snow_3_height,rand( snow_3_depth ) );

                        snow_3_systemGeometry.vertices.push( snow_3_vertex );
                }
                snow_3_particleSystem = new THREE.ParticleSystem( snow_3_systemGeometry, snow_3_systemMaterial );
                snow_3_particleSystem.position.y = -70;
                scene.add( snow_3_particleSystem );




                
        snow_1_clock = new THREE.Clock();
        snow_2_clock = new THREE.Clock();
        snow_3_clock = new THREE.Clock();
        function rand( v ) {return (v * (Math.random() - 0.5));}

        function updateParticleSystem( elapsed, particleSystem ) {

                var geometry = particleSystem.geometry,
                        vertices = geometry.vertices,
                        numVertices = vertices.length,
                        speedY = 20 * elapsed;
                        //speedY = 20 * elapsed*count_ip/40;
                       // opacity = particleSystem.materials[0].opacity;

                for(var i = 0; i < numVertices; i++) {
                        var v = vertices[i];
                        if( v.y > 0 ) {
                                v.y -= speedY * Math.random();
                                v.x -= count_ip/40 * Math.random();
                        } else {
                                v.y = 230;
                                v.x = rand( snow_2_width );
                        }
                }

                geometry.verticesNeedUpdate = true;

        }
        
        function updateParticleSystem2( elapsed, particleSystem ) {

                var geometry = particleSystem.geometry,
                        vertices = geometry.vertices,
                        numVertices = vertices.length,
                        speedY = 20 * elapsed;
                       // opacity = particleSystem.materials[0].opacity;

                for(var i = 0; i < numVertices; i++) {
                        var v = vertices[i];
                        if( v.y > 0 ) {
                                v.y -= speedY * Math.random();
                                v.x -= count_ip/70 * Math.random();
                        } else {
                                v.y = 230;
                                v.x = rand( snow_3_width );
                        }
                }

                geometry.verticesNeedUpdate = true;

        }
               
	var drop_t = 0.001;
	function pre_animate(){ 
	/*
	camera_working = Math.sin(cos_a);
	camera_working2 = Math.cos(cos_a);
	camera.position.y += camera_working*5
	camera.position.z -= camera_working*2
	camera.position.x -= camera_working2*5
	cos_a += 0.005;
    camera.lookAt( scene.position );
	*/
	var drop_v0 = 1;
	var drop_a = 9.8;
	var drop_h = 0;
	if(now_dropping != 0 && now_dropping != 'scene'){
	
	var reset_y = node[now_dropping].position.y;
		//drop_time ++;
		if(node[now_dropping].position.y < -85){
		now_dropping = 0;		
		//setTimeout(function(){now_tracking = 'scene'}, 5000)	
		drop_t = 0.001;
		}else{
			node[now_dropping].position.y = reset_y - (drop_v0*drop_t + (1/2)*(drop_a)*(drop_t*drop_t)*5000);
			drop_t += 0.001;
		}

	}

	console.log(now_upping);

	var up_v0 = 1;
	var up_a = 9.8;
	var up_h = 0;
	if(now_upping != 0 && now_upping != 'scene'){
	
	var reset_y_ = node[now_upping].position.y;
	console.log('t');
		//up_time ++;
		if(node[now_upping].position.y > random_number(90)){
		now_upping = 0;		
		//setTimeout(function(){now_tracking = 'scene'}, 5000)	
		up_t = 0.001;
		}else{
			node[now_upping].position.y = reset_y_ + (up_v0*up_t + (1/2)*(up_a)*(up_t*up_t)*5000);
			up_t += 0.001;
		}

	}	

	//$('#span_camera').html("("+parseInt(camera.position.x)+","+parseInt(camera.position.y)+","+parseInt(camera.position.z)+")");
	//$('#test').html(now_tracking)
   
	var snow_1 = snow_1_clock.getDelta(),
	snow_2 = snow_2_clock.getDelta(),
	snow_3 = snow_3_clock.getDelta(),
     snow_1_t = snow_1_clock.getElapsedTime() * 0.5,
     snow_2_t = snow_2_clock.getElapsedTime() * 0.5,
     snow_3_t = snow_3_clock.getElapsedTime() * 0.5;

        updateParticleSystem( snow_2, snow_2_particleSystem);
        updateParticleSystem( snow_1, snow_1_particleSystem);
        updateParticleSystem2( snow_3, snow_3_particleSystem);        

		var time = Date.now();

		controls.update();
		//$('#test2').html(parseInt(camera.position.x)+","+parseInt(camera.position.y)+","+parseInt(camera.position.z)+"||"+print_r(controls[0]))
		var now_status = parseInt($('#load_node_'+now_tracking+'_status').html());
		if(now_tracking != 0 && now_tracking != 'scene'  && now_status !=0){
			camera.lookAt(node[now_tracking].position);
			//QOS
			var qos_val = $('#load_node_'+now_tracking+'_qos').html();
			$('#qos_test').val($('#load_node_'+now_tracking+'_qos').html())

			if(qos_val){
				$('#qos_'+qos_val).css({'background':'#cdcdcd','color':'black'});
			}
			node[now_tracking].rotation.x -= Math.sin(time * 0.01)/20;
			if(node[now_tracking].position.z < now_tracking_z+90){
			node[now_tracking].position.z += 2.1;	
						
			}else{
			camera.position.z += 0.6			
			}
			
			//node[now_tracking].scale.x -= Math.sin(time * 0.01)/100;
				camera.position.x += 0.6

		}else if (now_tracking == 'scene'){
			camera.lookAt( scene.position );
			
		}else{
			camera.lookAt( scene.position );	
		}


		renderer.render(scene,camera);


	}
 var graph_data = new Array();
 var graph_data_d = new Array();
 var graph_data_m = new Array();
 graph_data[0] = { y: '1', up: 0,  down: 0 };
 graph_data[1] = { y: '2', up: 0,  down: 0 };
 graph_data[2] = { y: '3', up: 0,  down: 0 };
 graph_data[3] = { y: '4', up: 0,  down: 0 };
 graph_data[4] = { y: '5', up: 0,  down: 0 };
 graph_data[5] = { y: '6', up: 0,  down: 0 };
 graph_data[6] = { y: '7', up: 0,  down: 0 };
 graph_data[7] = { y: '8', up: 0,  down: 0 };
 graph_data[8] = { y: '9', up: 0,  down: 0 };
 graph_data[9] = { y: '10', up: 0,  down: 0 };
 graph_data[10] = { y: '11', up: 0,  down: 0 };

 graph_data_d[0] = { y: '1', up: 0,  down: 0 };
 graph_data_d[1] = { y: '2', up: 0,  down: 0 };
 graph_data_d[2] = { y: '3', up: 0,  down: 0 };
 graph_data_d[3] = { y: '4', up: 0,  down: 0 };
 graph_data_d[4] = { y: '5', up: 0,  down: 0 };
 graph_data_d[5] = { y: '6', up: 0,  down: 0 };
 graph_data_d[6] = { y: '7', up: 0,  down: 0 };
 graph_data_d[7] = { y: '8', up: 0,  down: 0 };
 graph_data_d[8] = { y: '9', up: 0,  down: 0 };
 graph_data_d[9] = { y: '10', up: 0,  down: 0 };
 graph_data_d[10] = { y: '11', up: 0,  down: 0 };
 
  graph_data_m[0] = { y: '1', up: 0,  down: 0 };
 graph_data_m[1] = { y: '2', up: 0,  down: 0 };
 graph_data_m[2] = { y: '3', up: 0,  down: 0 };
 graph_data_m[3] = { y: '4', up: 0,  down: 0 };
 graph_data_m[4] = { y: '5', up: 0,  down: 0 };
 graph_data_m[5] = { y: '6', up: 0,  down: 0 };
 graph_data_m[6] = { y: '7', up: 0,  down: 0 };
 graph_data_m[7] = { y: '8', up: 0,  down: 0 };
 graph_data_m[8] = { y: '9', up: 0,  down: 0 };
 graph_data_m[9] = { y: '10', up: 0,  down: 0 };
 graph_data_m[10] = { y: '11', up: 0,  down: 0 };
 var graph_morris = Morris.Area({
	  element: 'graph_wrap',
	  data: [
	     graph_data[7],
	     graph_data[8],
	     graph_data[9],
	     graph_data[10]
	  ],
	  xLabelFormat : function(x){ return '';},
	  pointStrokeColors :  ['#ffffff', '#ffffff'],
	  gridTextColor : 'black',
	  fillOpacity : 0.1,
	  lineWidth : 2,
	  gridTextSize : 10,
	  xkey: 'y',
	  lineColors : ['#1894a7', '#cf3b6f'],
	  ykeys: ['up', 'down'],
	  labels: ['Current Up Traffic', 'Current Down Traffic']
	});

 var graph_morris2 = Morris.Area({
	  element: 'board_graph_r',
	  data: [
	     graph_data[4],
	     graph_data[5],
	     graph_data[6],
	     graph_data[7],
	     graph_data[8],
	     graph_data[9],
	     graph_data[10]
	  ],
	  xLabelFormat : function(x){ return '';},
	  pointStrokeColors :  ['#ffffff', '#ffffff'],
	  gridTextColor : '#868686',
	  fillOpacity : 0.1,
	  lineWidth : 2,
	  gridTextSize : 10,
	  xkey: 'y',
	  lineColors : ['#1894a7', '#cf3b6f'],
	  ykeys: ['up', 'down'],
	  labels: ['', '']
	});

 var graph_morris_d = Morris.Area({
	  element: 'board_graph_d',
	  data: [
	     graph_data_d[4],
	     graph_data_d[5],
	     graph_data_d[6],
	     graph_data_d[7],
	     graph_data_d[8],
	     graph_data_d[9],
	     graph_data_d[10]
	  ],
	  xLabelFormat : function(x){ return '';},
	  pointStrokeColors :  ['#ffffff', '#ffffff'],
	  gridTextColor : '#868686',
	  fillOpacity : 0.1,
	  lineWidth : 2,
	  gridTextSize : 10,
	  xkey: 'y',
	  lineColors : ['#1894a7', '#cf3b6f'],
	  ykeys: ['up', 'down'],
	  labels: ['', '']
	});


 var graph_morris_m = Morris.Area({
	  element: 'board_graph_m',
	  data: [
	     graph_data_m[4],
	     graph_data_m[5],
	     graph_data_m[6],
	     graph_data_m[7],
	     graph_data_m[8],
	     graph_data_m[9],
	     graph_data_m[10]
	  ],
	  xLabelFormat : function(x){ return '';},
	  pointStrokeColors :  ['#ffffff', '#ffffff'],
	  gridTextColor : '#868686',
	  fillOpacity : 0.1,
	  lineWidth : 2,
	  gridTextSize : 10,
	  xkey: 'y',
	  lineColors : ['#1894a7', '#cf3b6f'],
	  ykeys: ['up', 'down'],
	  labels: ['', '']
	});



function move_to(x,target){
	if(x<target){
		return x++;
	}else if(x>target){
		return x--;
	}else{
		return 0;
	}
}
		setInterval(function(){
	
	$('#table_load').load('action/load_table.php?q='+$('#input_search').val());
		$('.td_node').each(function(){
		var load_node = $('#load_'+$(this).attr('id'));
		$(this).css({'background':load_node.attr('bgcolor')});
		var status = $('#load_'+$(this).attr('id')+'_status').html();

	});
	count_ip = 1;
if(ipmornitor == 1){
	$('.td_board').each(function(){
	var load_node = $(this).attr('alt');
	var text_color = 'white';
	var upt_color = '#eac45c';
	var downt_color = '#ea985c';
	$(this).attr('bgcolor',$('#load_node_'+load_node).attr('bgcolor'))
		if($(this).attr('bgcolor') != '#373737'){
			text_color = 'black';
			upt_color = '#987410';
			downt_color = '#874718';
		}
	$(this).css({'color':text_color})
	var this_pid = $('#load_node_'+load_node+'_pid').html();
	//var this_pid = $(this).attr('bgcolor')
	var this_uptcur = $('#load_node_'+load_node+'_uptcur').html();
	var this_downtcur = $('#load_node_'+load_node+'_downtcur').html();
	var this_name = $('#load_node_'+load_node+'_name').html();
	$(this).html("<strong><font size='2'>"+this_pid+"</font></strong><br/><font size='1'><font color='"+upt_color+"'>"+this_uptcur+"</font>&nbsp;/&nbsp;<font color='"+downt_color+"'>"+this_downtcur+"</font></font>")
	})
}
for(var nn=1;nn<255;nn++){
if(parseInt($('#load_node_'+nn+'_status').html()) == 1 || parseInt($('#load_node_'+nn+'_status').html()) == 2 ||parseInt($('#load_node_'+nn+'_status').html()) == 3||parseInt($('#load_node_'+nn+'_status').html()) == 4){
	count_ip++;

	if(node[nn] != '[object Object]'){
	create_node(nn,-random_number(90)+random_number(90),random_number(90),random_number(90)-random_number(50),$('#load_node_'+nn+'_'+show_option).html());
	}
}else{
	if(node[nn] != 'undefined'){
	scene.remove(node[nn]);
	node[nn] ='no';

	}
}
}			

	  
	  
	  spotLight8.intensity = random_number(20);
}, 500);
var now_tracking__;
var graph_timer = setInterval(function(){
	if(now_tracking__ != now_tracking){
	graph_data[0] = {y : '1' , up : 0, down : 0}
	graph_data[1] = {y : '2' , up : 0, down : 0}
	graph_data[2] = {y : '3' , up : 0, down : 0}
	graph_data[3] = {y : '4' , up : 0, down : 0}
	graph_data[4] = {y : '5' , up : 0, down : 0}
	graph_data[5] = {y : '6' , up : 0, down : 0}
	graph_data[6] = {y : '7' , up : 0, down : 0}
	graph_data[7] = {y : '8' , up : 0, down : 0}
	graph_data[8] = {y : '9' , up : 0, down : 0}
	graph_data[9] = {y : '10' , up : 0, down : 0}
	graph_data[10] = {y : '11' , up : 0, down : 0}
	}
	if(now_tracking != ''&& now_tracking != 'scene'){
	//$('#status_on').attr('src','action/status_font.php?q='+number);
	if(now_graph_status=='d'){
		$.ajax({
	            type: 'POST',
	            url: 'action/load_traffic.php',
	            data: {
	                ip : $('#load_node_'+now_tracking+'_ip').html(), date : '1'
	            },
	            success: function(result) {
	            	var split_a = result.split('|');
	            	for(var i=0; i<split_a.length;i++){
		            	var split_b = split_a[i].split('/');
		            	graph_data_d[split_b[0]] = {y : split_b[0] , up : split_b[1], down : split_b[2]}
		            	console.log(split_b[0]+'.'+split_b[1] +'.'+split_b[2] )
	            	}
	            //$(this).removeClass('multi_select')
	            },
	            error: function(result) {
	              //  alert("오류가 발생했습니다.");
	            }
	     }); 
	}else if(now_graph_status=='m'){
		$.ajax({
	            type: 'POST',
	            url: 'action/load_traffic_m.php',
	            data: {
	                ip : $('#load_node_'+now_tracking+'_ip').html(), date : '30'
	            },
	            success: function(result) {
	            	var split_a = result.split('|');
	            	for(var i=0; i<split_a.length;i++){
		            	var split_b = split_a[i].split('/');
		            	graph_data_m[split_b[0]] = {y : split_b[0] , up : split_b[1], down : split_b[2]}
		            	console.log(split_b[0]+'.'+split_b[1] +'.'+split_b[2] )
	            	}
	            //$(this).removeClass('multi_select')
	            },
	            error: function(result) {
	              //  alert("오류가 발생했습니다.");
	            }
	     }); 
	}else{
	graph_data[0] = {y : '1' , up : graph_data[1]['up'], down : graph_data[1]['down']}
	graph_data[1] = {y : '2' , up : graph_data[2]['up'], down : graph_data[2]['down']}
	graph_data[2] = {y : '3' , up : graph_data[3]['up'], down : graph_data[3]['down']}
	graph_data[3] = {y : '4' , up : graph_data[4]['up'], down : graph_data[4]['down']}
	graph_data[4] = {y : '5' , up : graph_data[5]['up'], down : graph_data[5]['down']}
	graph_data[5] = {y : '6' , up : graph_data[6]['up'], down : graph_data[6]['down']}
	graph_data[6] = {y : '7' , up : graph_data[7]['up'], down : graph_data[7]['down']}
	graph_data[7] = {y : '8' , up : graph_data[8]['up'], down : graph_data[8]['down']}
	graph_data[8] = {y : '9' , up : graph_data[9]['up'], down : graph_data[9]['down']}
	graph_data[9] = {y : '10' , up : graph_data[10]['up'], down : graph_data[10]['down']}
	graph_data[10] = {y : '11' , up : parseInt($('#load_node_'+now_tracking+'_uptcur').html()), down : parseInt($('#load_node_'+now_tracking+'_downtcur').html())}
	}
	
	graph_morris.setData([
	     graph_data[7],
	     graph_data[8],
	     graph_data[9],
	     graph_data[10]
	  ])
	  if(graphmornitor == 1){
	  
	  $('#graphboard_label').html($('#load_node_'+now_tracking+'_ip').html()+'\'s ')
	if(now_graph_status=='d'){

	graph_morris_d.setData([
	     graph_data_d[0],
	     graph_data_d[1],
	     graph_data_d[2],
	     graph_data_d[3],
	     graph_data_d[4],
	     graph_data_d[5],
	     graph_data_d[6],
	     graph_data_d[7],
	     graph_data_d[8],
	     graph_data_d[9],
	     graph_data_d[10]
	  ])		  
	  }else if(now_graph_status=='m'){
	graph_morris_m.setData([
	     graph_data_m[0],
	     graph_data_m[1],
	     graph_data_m[2],
	     graph_data_m[3],
	     graph_data_m[4],
	     graph_data_m[5],
	     graph_data_m[6],
	     graph_data_m[7],
	     graph_data_m[8],
	     graph_data_m[9],
	     graph_data_m[10]
	  ])		  
	  }else{
		  graph_morris2.setData([
	     graph_data[0],
	     graph_data[1],
	     graph_data[2],
	     graph_data[3],
	     graph_data[4],
	     graph_data[5],
	     graph_data[6],
	     graph_data[7],
	     graph_data[8],
	     graph_data[9],
	     graph_data[10]
		 ])		  
	  }
	  			  	$('#info_uptcur_2').html($('#load_node_'+now_tracking+'_uptcur').html()) 
	  			  	$('#info_downtcur_2').html($('#load_node_'+now_tracking+'_downtcur').html()) 
	  }
	  now_tracking__ = now_tracking;
	  }
}, 1000);
setInterval(function(){
	$('#slide_amount_snow').animate({'left':parseInt(count_ip/1.7)+'px'})
	$('#txt_liveip').html(parseInt(count_ip/1.7));
}, 3000);
function getTimeStamp(minor) {
  var d = new Date();
  if(!minor){
	  var m = 0;
  }else{
	  var m = minor;
  }
  var s =
    leadingZeros(d.getFullYear(), 4) + '-' +
    leadingZeros(d.getMonth() + 1, 2) + '-' +
    leadingZeros(d.getDate(), 2) + ' ' +

    leadingZeros(d.getHours(), 2) + ':' +
    leadingZeros(d.getMinutes(), 2) + ':' +
    leadingZeros(d.getSeconds(), 2)-m;

  return s;
}



function leadingZeros(n, digits) {
  var zero = '';
  n = n.toString();

  if (n.length < digits) {
    for (i = 0; i < digits - n.length; i++)
      zero += '0';
  }
  return zero + n;
}


	//Document.Resize
	$( window ).resize(function() {
		var width2 = parseInt($('#canvas').width()), height2 =  parseInt($(window).height() - $('#canvas').offset().top);
		$('#dashboard').height($(window).height() - $('#dashboard').offset().top-30);
		//$('#ipboard').height($(window).height() - $('#ipboard').offset().top-60);
		//$('#graphboard').height($(window).height() - $('#graphboard').offset().top-60);
		$('#load_video').css('margin-top',$(window).height()/2-$('#load_video').height()/2+'px')
		//$('#ipboard_content').height($(window).height() - $('#ipboard_content').offset().top-20);
		//$('#graphboard_content').height($(window).height() - $('#graphboard_content').offset().top-20);
		$('#black_wrap').height(height2);
		$('#dashboard_hover').height($(window).height() - $('#dashboard').offset().top-5);
		$('#dashboard_content').height($(window).height() - $('#dashboard').offset().top-60);
		//!렌더러 생성
		renderer.setSize(width2, height2);
		renderer.render(scene,camera);

  });

var load_timer;
var now_tracking_z;
//var timers;
var now_fps_;
$('#btn_ipmornitor').click(function(){
	if(ipmornitor == 1){
		$('#ipboard').hide();
		
		$('#ipboard_content').hide();

		
		ipmornitor = 0;
		$('#slide_fps').animate({'left':now_fps_*4.6},1000,function(){
			now_fps = now_fps_;
			$('#txt_fps').html(now_fps)
		})
	}else{
	now_fps_ = now_fps;
	$('#ipboard_content').click();
		$('#slide_fps').animate({'left':10*4.6},1000,function(){
			now_fps = parseInt($(this).position().left/4.6);
			if(now_fps<0){
				now_fps = 10;
			}
			$('#txt_fps').html(now_fps)
		})
		$('#ipboard').show();
		//$('#ipboard').height($(window).height() - $('#ipboard').offset().top-60)
		$('#ipboard_content').show();
		ipmornitor = 1;
	}
})

$('#btn_graphmornitor').click(function(){
	//if(now_tracking =='' || !now_tracking || now_tracking =='scene'){
	if(gm_key == 1){
	gm_key = 0;
		var arg = prompt("그래프로 표시 할 IP를 입력하세요.","");
		arg2= arg.replace('210.118.34.', '');
		var prom = parseInt($('#load_node_'+arg2+'_status').html());
		
		if(prom == 1 || prom ==2 || prom ==3){
		now_tracking = arg2;
		}else{
		alert('해당 IP가 존재하지 않습니다.');
		return 0;	
		}
	}
	gm_key = 0;
	//}
	
	if(graphmornitor == 1){
		$('#graphboard').hide();
		
		$('#graphboard_content').hide();
		graphmornitor = 0;
				$('#slide_fps').animate({'left':now_fps_*4.6},1000,function(){
			now_fps = now_fps_;
			$('#txt_fps').html(now_fps)
		})
	}else{
		now_fps_ = now_fps;
		$('#graphboard_content').click()
		$('#slide_fps').animate({'left':10*4.6},1000,function(){
			now_fps = parseInt($(this).position().left/4.6);
			if(now_fps<0){
				now_fps = 10;
			}
			$('#txt_fps').html(now_fps)
		})
		$('#graphboard').show();
		//$('#graphboard').height($(window).height() - $('#graphboard').offset().top-60)
		$('#graphboard_content').show();
		graphmornitor = 1;
	}
})
$('#btn_close').click(function(){
	var now_id = '';
	$('.multi_select').each(function(){
		now_id += $('#load_node_'+parseInt($(this).attr('alt'))+'_ip').html()+',';
	})
	 if (confirm(now_id+"ip접속을 차단하시겠습니까?")!=0) {   
	 var timess = 1;
	 $('.multi_select').each(function(){
	 timess += 1;
	 setTimeout(function(){
		$.ajax({
	            type: 'POST',
	            url: 'action/kill_node.php',
	            data: {
	                ip : $('#load_node_'+parseInt($(this).attr('alt'))+'_ip').html()
	            },
	            success: function(result) {
	            //$(this).removeClass('multi_select')
	            },
	            error: function(result) {
	              //  alert("오류가 발생했습니다.");
	            }
	     }); 
	 }, 2000*timess)
		
	  });
	  timess = 1;
             } else {
				 $('.multi_select').each(function(){
	            $(this).html('')
	            $(this).removeClass('multi_select')
	            });
	            sh_key = 0;
	            $('#btn_close').hide('normal');
	            
			 }
})
function singleClick(e) {
var now_status = $('#load_node_'+parseInt($(this).attr('alt'))+'_status').html();
if(sh_key==1){
now_tracking = 0;
$('#btn_close').show('normal');
$(this).html('*');
$(this).addClass('multi_select');
now_select.push($(this).attr('alt'));
//$('#test').html(print_r(now_select))
return false;
}else{
	now_select = new Array();
}

	if((now_tracking == 0 && now_status!=0) || (now_tracking == 'scene' && now_status!=0)  || ($(this).attr('alt') != now_tracking && now_status!=0)){
		var now_status = $('#load_node_'+parseInt($(this).attr('alt'))+'_status').html();
	
		if(now_status ==1 || now_status == 2 || now_status == 3){
			if(now_tracking != 0 && now_tracking != 'scene'){
			clearInterval(load_timer);
				node[now_tracking].scale.set(1,1,1);
			  	node[now_tracking].rotation.set(0,0,0);
			  	node[now_tracking].position.z = now_tracking_z;
			  	controls.zoomIn(2.5,2)
			  	$('#info_under').slideUp();
			  	$('#modify_under').slideUp();
			  	$('#mousemove_div').show();
			}
			$('#mousemove_div').hide();
			now_tracking = parseInt($(this).attr('alt'));
			if(show_option == 'ip'){
			select_id($('#load_node_'+parseInt($(this).attr('alt'))+'_name').html());
			}else{
			select_id($('#load_node_'+parseInt($(this).attr('alt'))+'_ip').html())
			}
			//now_select.push(now_tracking);
			$('.btn_qos').each(function(){
				$(this).css({'background':'none','color':'#cdcdcd'});
			})
			//alert(node[now_tracking].geometry.text)
		  	spotLight5.intensity = 1;
		  				$('.btn_qos').each(function(){
				$(this).css({'background':'none','color':'#cdcdcd'});
			})
		  	load_timer = setInterval(function(){
		  	$('#info_ip').html($('#load_node_'+now_tracking+'_ip').html())
		  	if($('#load_node_'+now_tracking+'_name').html() == ''){
				$('#info_name').html('Wi-fi Address');  	
		  	}else{
			  	$('#info_name').html($('#load_node_'+now_tracking+'_name').html())
		  	}
		  	
		  		$('#info_mac').html($('#load_node_'+now_tracking+'_mac').html())
			  	$('#info_uptcur').html($('#load_node_'+now_tracking+'_uptcur').html())
			  	$('#info_downtcur').html($('#load_node_'+now_tracking+'_downtcur').html())

		  	}, 300);
		  		$('#ps_content').html('');
		  		$('#btn_scan').html('SCAN');
		  		$('#info_under').slideDown();
		  		$('#modify_under').slideDown();
		  		controls.zoomIn(2.5,1)
		  		node[now_tracking].scale.set(2,2,2);
		  		now_tracking_z = node[now_tracking].position.z;
	
		  	//$('#test').html(parseInt(camera.position.x)+","+parseInt(camera.position.y)+","+parseInt(camera.position.z))
		  	
		  	}

	}else{
		
			var now_status = $('#load_node_'+parseInt($(this).attr('alt'))+'_status').html();
	
			if(now_tracking != 0 || now_tracking != 'scene'){
			$('#mousemove_div').show();
			//now_tracking2 = parseInt($(this).attr('alt'));
			  	spotLight5.intensity = 3;
			  	$('#info_ip').html('');
			  	$('#info_name').html('');
			  	$('#info_mac').html('');
			  	$('#info_uptcur').html('');
			  	$('#info_downtcur').html('');
			  	clearInterval(load_timer);
			  	$('#info_under').slideUp();
			  	$('#modify_under').slideUp();
			  	$('#info_top').slideUp();
			  	//clearInterval(timers);
			  	//controls.zoomIn(2.5,2)
			  	//now_select = new Array();
			  	node[now_tracking].scale.set(1,1,1);
			  	node[now_tracking].rotation.set(0,0,0);
			  	node[now_tracking].position.z = now_tracking_z;
			  	//camera.position.set(0,-50,0)
			  	
			  	}
			  	controls.zoomIn(2.5,2)
			  now_tracking = 'scene';
	}

}

function doubleClick(e) {
var this_status = parseInt($('#load_node_'+parseInt($(this).attr('alt'))+'_status').html());
var this_pid = parseInt($('#load_node_'+parseInt($(this).attr('alt'))+'_pid').html());

	if(this_status == 0 || this_status == 4){
         if (confirm($('#load_node_'+parseInt($(this).attr('alt'))+'_ip').html()+" ip접속을 허용하시겠습니까?")!=0) {
		$.ajax({
	            type: 'POST',
	            url: 'action/pass_node.php',
	            data: {
	                ip : $('#load_node_'+parseInt($(this).attr('alt'))+'_ip').html()
	            },
	            success: function(result) {
	            //alert("\""+result+"\"가 접속하였습니다." );
	            now_upping = this_pid;
	            },
	            error: function(result) {
	            //    alert("오류가 발생했습니다.");
	            }
	        });
             } else {
				  $('#trash_wrap').animate({'opacity':0},function(){$(this).hide()});
			 }
	}else{	     
         if (confirm($('#load_node_'+parseInt($(this).attr('alt'))+'_ip').html()+" ip접속을 차단하시겠습니까?")!=0) {   
         var this_left = $(this).offset().left;
         var this_top = $(this).offset().top;
var bezier_params = {
		            start: {
		                x: this_left,
		                y: this_top,
		                angle: 10
		            },
		            end: {
		                x: $('#trash_wrap').offset().left,
		                y: $('#trash_wrap').offset().top,
		                angle: -30,
		                length: 1.1
		            }
		        };
		        
				
		        $("#tis").css({'height':'20px','width':'20px'}).show().animate({ path: new $.path.bezier(bezier_params),'width':'100px','height':'100px' }, 1500,function(){
			        $(this).hide();
			        $('#tr_img').attr('src','img/tr_1.png');

			        $('#trash_wrap').delay(2000).animate({'opacity':0},function(){$(this).hide();$('#tr_img').attr('src','img/tr_0.png');
				        now_dropping = this_pid;
				        
			        });
		        });
		$.ajax({
	            type: 'POST',
	            url: 'action/kill_node.php',
	            data: {
	                ip : $('#load_node_'+parseInt($(this).attr('alt'))+'_ip').html()
	            },
	            success: function(result) {	         
		         
	            //alert("\""+result+"\"의 접속을 차단하였습니다.");
	            },
	            error: function(result) {
	              //  alert("오류가 발생했습니다.");
	            }
	        });
             } else {
				 	 $('#trash_wrap').animate({'opacity':0},function(){$(this).hide()});
			 }
	}
}


$('.td_node').click(function(e) {
    var that = this;
    setTimeout(function() {
        var dblclick = parseInt($(that).data('double'), 10);
        if (dblclick > 0) {
            $(that).data('double', dblclick-1);
        } else {
            singleClick.call(that, e);
        }
    }, 300);
}).dblclick(function(e) {
    $(this).data('double', 2);
    doubleClick.call(this, e);
}).hover(function(){
	$('#mouseup_ip').html($('#load_node_'+$(this).attr('alt')+'_ip').html())
},function(){
	$('#mouseup_ip').html('Select IP in Table');
})


  $('.td_node').draggable({helper:'clone',
	  start:function(){
	  var this_status_ = $('#load_node_'+$(this).attr('alt')+'_status').html();
	  	if(this_status_==1){
		  $('#trash_wrap').show().animate({'opacity':.7});
		}
	  },
	  stop:function(){
		 // $('#trash_wrap').animate({'opacity':.5},function(){$(this).hide()});
	  }
  });
 $('#input_search').focus(function(){
	 $(this).css('opacity',0.8)
 }).blur(function(){
	 $(this).css('opacity',0.5)
 })
 
 
 $('.show_select').click(function(){
	 for(var nn=1;nn<255;nn++){

	scene.remove(node[nn]);
	node[nn] ='no';
	show_option = $(this).attr('alt');
	}
 });
 
 $('#show_type').click(function(){
 var this_alt = $(this).attr('alt');
	if(this_alt =='name'){
		$(this).attr('alt','ip')
		$(this).attr('src','img/view_ip.png');
		show_option = 'ip';	
		var now_tracking_ = now_tracking;
		now_tracking = 'scene';
		for(var nn=1;nn<255;nn++){
			scene.remove(node[nn]);
			node[nn] ='no';
		}
		now_tracking = now_tracking_;
	} else{
		$(this).attr('alt','name')
		$(this).attr('src','img/view_name.png');
		show_option = 'name';
		var now_tracking_ = now_tracking;
		now_tracking = 'scene';	
		for(var nn=1;nn<255;nn++){
			scene.remove(node[nn]);
			node[nn] ='no';
		}	
		now_tracking = now_tracking_;
	}
 });
 
 $('#btn_signout').click(function(){
	location.href = 'signout.php'; 
 });
$('#ipboard_content').draggable({containment: "#canvas",drag:function(){
	$('#ipboard').css({top:$(this).offset().top-10+'px',left:$(this).offset().left-15+'px','z-index':5})
	$('#ipboard_content').css('z-index',6);
	$('#graphboard_content').css('z-index',4);
	$('#graphboard').css('z-index',3);
}}).click(function(){
	$('#ipboard').css({'z-index':5});
	$('#ipboard_content').css('z-index',6);
	$('#graphboard_content').css('z-index',4);
	$('#graphboard').css('z-index',3);	
});
$('#graphboard_content').draggable({containment: "#canvas",drag:function(){
	$('#graphboard').css({top:$(this).offset().top-10+'px',left:$(this).offset().left-15+'px','z-index':5});
	$('#graphboard_content').css('z-index',6);
	$('#ipboard_content').css('z-index',4);
	$('#ipboard').css('z-index',3);
}}).click(function(){
	$('#graphboard').css({'z-index':5});
	$('#graphboard_content').css('z-index',6);
	$('#ipboard_content').css('z-index',4);
	$('#ipboard').css('z-index',3);
});
$('#btn_c_graphb').click(function(){
	$('#btn_graphmornitor').click();
});

$('#btn_c_ipb').click(function(){
	$('#btn_ipmornitor').click();
});
var trash_drop = 0;
$('#trash_wrap').droppable({
	drop:function(e,ui){
	trash_drop = 1;
		if(ui.draggable.hasClass('td_node')){
			doubleClick.call(ui.draggable, e)
		}
	}
});
$('#canvas').droppable({drop:function(){
	if(trash_drop == 1){
	trash_drop = 0;	
	}else{
	$('#trash_wrap').animate({'opacity':0},function(){$(this).hide()});
	}
}})
$('#txt_fps').html(parseInt(now_fps))
$('#slide_fps').css({'left':parseInt(now_fps*4.6)+'px'})
$('#slide_fps').draggable({containment: '#slide_fps_wrap', axis: "x", drag:function(){
	$('#txt_fps').html(parseInt($(this).position().left/4.6))
},stop:function(){
	now_fps = parseInt($(this).position().left/4.6);
		//clearInterval(entire_timer);
	//entire_timer = setInterval(function(){main();},parseInt($(this).position().left/4.6));
} });
//스캔 부분
	var ps_angle = 0;
	var ps_timer;
	
	$('#btn_scan').click(function(){
		var bezier_params = {
		            start: {
		                x: 50,
		                y: 10,
		                angle: 10,
		                length: 1.2
		            },
		            end: {
		                x: 400,
		                y: 10,
		                angle: 10,
		                length: 1.5
		            }
		        };
		var bezier_params2 = {
		            start: {
		                x: 400,
		                y: 10,
		                angle: 10,
		                length: 1.5
		            },
		            end: {
		                x: 50,
		                y: 10,
		                angle: 10,
		                length: 1.2
		            }
		        };
		        
		        
		var start_animation = function(){
		        $("#scan_loading").css({'height':'20px','width':'20px','opacity':1}).show().animate({ path: new $.path.bezier(bezier_params),'width':'30px','height':'30px' }, 3000,function(){
			         $(this).css({'height':'30px','width':'30px'}).show().animate({ path: new $.path.bezier(bezier_params2),'width':'20px','height':'20px' }, 3000,function(){
				         start_animation();
			         });
			        
		        });
		}
	    start_animation();
	    $('#ps_content').html('포트를 스캔하고 있습니다.')
	    $('#btn_scan').hide();
			$.ajax({
				            type: 'POST',
				            url: 'action/port_scan.php',
				            data: {
				                ip : $('#load_node_'+now_tracking +'_ip').html()
				            },
				            success: function(result) {
				            },
				            error: function(result) {
				              //  alert("오류가 발생했습니다.");
				            }
				        });
			setTimeout(function(){
				var res = function(x){
					//$('#ps_content').html($('#load_node_'+x +'_port').html().replace(/\s+/gi, ', '));
					
					var content ='';
					var arr = $('#load_node_'+x +'_port').html().split('P');
					for(var i=0;i< arr.length;i++){
						if(port_arr[arr[i]]){
						content += '['+port_arr[arr[i]]+'] ';
						}else{
						content += '['+arr[i]+'] ';
						}
					}
					
										$('#ps_content').html(content);
				}
				if($('#load_node_'+now_tracking +'_port').html() == ''){
					$('#ps_content').html('커피 한잔의 여유는 어떠세요?^^')
					$.ajax({
						            type: 'POST',
						            url: 'action/port_scan.php',
						            data: {
						                ip : $('#load_node_'+now_tracking +'_ip').html()
						            },
						            success: function(result) {

						            $('#scan_loading').animate({'opacity':0},function(){$(this).stop().hide();res(now_tracking);});

						            },
						            error: function(result) {
						                //alert("오류가 발생했습니다.");
						            }
						        });
				}else{
				$('#scan_loading').stop().hide();res(now_tracking);
				}
			$('#btn_scan').show();
			}, 6000);
			$('#btn_scan').html('ReSCAN');
	});
	
$('#btn_portscan').click(function(){
ps_timer = setInterval(function(){
      ps_angle+=15;
     $('#btn_portscan').rotate(ps_angle);
},50);
$('#ps_content').html('포트를 스캔하고 있습니다.')
			$.ajax({
				            type: 'POST',
				            url: 'action/port_scan.php',
				            data: {
				                ip : $('#load_node_'+now_tracking +'_ip').html()
				            },
				            success: function(result) {
				            },
				            error: function(result) {
				              //  alert("오류가 발생했습니다.");
				            }
				        });
			setTimeout(function(){
				var res = function(x){
					$('#ps_content').html($('#load_node_'+x +'_port').html().replace(/\s+/gi, ', '));
				}
				if($('#load_node_'+now_tracking +'_port').html() == ''){
					$('#ps_content').html('커피 한잔의 여유는 어떠세요?^^')
					$.ajax({
						            type: 'POST',
						            url: 'action/port_scan.php',
						            data: {
						                ip : $('#load_node_'+now_tracking +'_ip').html()
						            },
						            success: function(result) {
						            },
						            error: function(result) {
						                //alert("오류가 발생했습니다.");
						            }
						        });
						        setTimeout(function(){	clearInterval(ps_timer);
								res(now_tracking);
								}, 3500);
								
					
				}else{
				clearInterval(ps_timer);
				res(now_tracking);
				}
			}, 3500);
			
});




$('.btn_qos').click(function(){
			$('.btn_qos').each(function(){
				$(this).css({'background':'none','color':'#cdcdcd'});
			})
				$.ajax({
			            type: 'POST',
			            url: 'action/qos_refresh.php',
			            data: {
			                ip : $('#load_node_'+now_tracking +'_ip').html(), way : 'add', lv : $(this).attr('alt')
			            },
			            success: function(result) {
			            },
			            error: function(result) {
			                alert("오류가 발생했습니다.");
			            }
			        });	
})

$(document).bind('keydown.Alt_a',function (evt){$('#btn_ipmornitor').click();return false; });
$(document).bind('keydown.Alt_s',function (evt){gm_key=1;$('#btn_graphmornitor').click();return false; });
$(document).bind('keydown.Alt_c',function (evt){$('#show_type').click();return false; });
$(document).bind('keydown.Alt_d',function (evt){$('#dashboard_hover').click();return false; });
$(document).bind('keydown.Alt_z',function (evt){$('#zoom_plus').click();return false; });
$(document).bind('keydown.Alt_x',function (evt){$('#zoom_minor').click();return false; });
$(document).bind('keydown.tab',function (evt){$('#sc_wrap').show();return false; });
$(document).bind('keydown.shift',function (evt){
if(now_tracking != 0 || now_tracking != 'scene'){
	now_tracking = 0;
}
sh_key=1;return false; });
$(document).bind('keyup.tab',function (evt){$('#sc_wrap').hide();return false; });
$(document).bind('keyup.esc',function (evt){$('#btn_signout').click();return false; });
$(document).bind('keyup.space',function (evt){$('#btn_skip').click();return false; });
$(document).bind('keyup.shift',function (evt){sh_key=0;
$('.multi_select').each(function(){
	$(this).html('');
	$(this).removeClass('multi_select')
	
})
$('#btn_close').hide('normal');now_select = new Array();return false; });


$('#input_search').bind('keydown.Alt_a',function (evt){$('#btn_ipmornitor').click();return false; });
$('#input_search').bind('keydown.Alt_s',function (evt){gm_key=1;$('#btn_graphmornitor').click();return false; });
$('#input_search').bind('keydown.Alt_c',function (evt){$('#show_type').click();return false; });
$('#input_search').bind('keydown.Alt_d',function (evt){$('#dashboard_hover').click();return false; });
$('#input_search').bind('keydown.Alt_z',function (evt){$('#zoom_plus').click();return false; });
$('#input_search').bind('keydown.Alt_x',function (evt){$('#zoom_minor').click();return false; });
$('#input_search').bind('keydown.tab',function (evt){$('#sc_wrap').show();return false; });
$('#input_search').bind('keydown.shift',function (evt){sh_key=1;return false; });
$('#input_search').bind('keyup.tab',function (evt){$('#sc_wrap').hide();return false; });
$('#input_search').bind('keyup.esc',function (evt){$('#btn_signout').click();return false; });
$('#input_search').bind('keyup.space',function (evt){$('#btn_skip').click();return false; });
$('#input_search').bind('keyup.shift',function (evt){sh_key=0;now_select = new Array();return false; });


$('.btn_qos').hover(function(){
	$(this).css({'background':'#cdcdcd','border':'1px solid #cdcdcd','color':'black'})
},function(){
	$(this).css({'background':'none','border':'1px solid #cdcdcd','color':'#cdcdcd'})
});

$('#zoom_minor').click(function(){
var width2 = parseInt($('#canvas').width()), height2 =  parseInt($(window).height() - $('#canvas').offset().top);

	$('#dashboard').animate({'zoom':1,'height':$(window).height() - $('#dashboard').offset().top-30+'px','top':'30px'},function(){
		$('#dashboard').animate({'zoom':1,'height':$(window).height() - $('#dashboard').offset().top-30+'px','top':'30px'});
	});
	$('#dashboard_content').animate({'zoom':1,'top':'45px','height':$(window).height() - $('#dashboard').offset().top-60+'px'},function(){
	$('#dashboard_content').animate({'zoom':1,'top':'45px','height':$(window).height() - $('#dashboard').offset().top-60+'px'});
			$('#dashboard_content').css({'cursor':'default'});
	$('#dashboard_content').draggable( 'disable' )
	$('.td_node').draggable( 'enable' )
	});

});
$('#zoom_plus').click(function(){
	$('#dashboard').animate({'zoom':1.8,'height':'1050px','top':'-50px'});
	$('#dashboard_content').animate({'zoom':1.8,'top':'15px'});
	$('#dashboard_content').css({'cursor':'move'});
	$('#dashboard_content').draggable({axis:"y",stop:function(){
	var height2 =  parseInt($(window).height() - $('#canvas').offset().top)
		if($(this).offset().top > 10){
			$(this).animate({'top':'10px'});
		}else if($(this).offset().top < -height2+190){
			$(this).animate({'top':-height2+190+'px'});
		}
	}});
	$('#dashboard_content').draggable( 'enable' );
	$('.td_node').draggable( 'disable' );
});


$('.board_type').hover(function(){
	$(this).css({'background':'#b5b5b5','color':'black'})
},function(){
	if(!$(this).hasClass('board_selected')){
	$(this).css({'background':'none','color':'#b5b5b5'})	
	}
}).click(function(){
	$('.board_selected').css({'background':'none','color':'#b5b5b5'}).removeClass('board_selected');
	now_graph_status = $(this).attr('alt').replace('_', '');
	$('#board_type_l').css({'background':'none','color':'#b5b5b5'});
	$('#board_type_m').css({'background':'none','color':'#b5b5b5'});
	$('#board_type_r').css({'background':'none','color':'#b5b5b5'});
	$(this).css({'background':'#b5b5b5','color':'black'});
	$(this).addClass('board_selected');
	$('#board_graph_m').hide();
	$('#board_graph_d').hide();
	$('#board_graph').hide();
	$('#board_graph'+$(this).attr('alt')).show();
	
})


});


