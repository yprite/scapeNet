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
html {overflow: hidden}
body{margin: 0 auto; background:black;}
#canvas{width: 100%;height: 580px;}
#black_wrap{position:absolute;width: 100%;height: 580px;background: black;text-align: center; }

#info{position: absolute; width: 200px; height: 100px; bottom:40px; left: 50px; background: white;border-radius: 15px;-moz-border-radius: 15px;-webkit-border-radius: 15px;-webkit-filter: blur(5px);filter: blur(5px); opacity: .5; display: none;}
#dashboard{position: absolute; width: 200px; top:30px; height: 200px; right: 30px; float: right; background: white;border-radius: 15px;-moz-border-radius: 15px;-webkit-border-radius: 15px;-webkit-filter: blur(5px);filter: blur(5px); opacity: .48; display: none; }
#ipboard{position: absolute; width: 700px; top:35px; height: 210px; right: 360px; float: right; background: black;border-radius: 15px;-moz-border-radius: 15px;-webkit-border-radius: 15px;-webkit-filter: blur(5px);filter: blur(5px); opacity: .7; display: none; }
#ipboard_content{position: absolute; width: 665px; top:45px; height: 210px; right: 380px; float: right;display: none;text-align: center;}
#dashboard_content{position: absolute; width: 165px; top:45px; height: 200px; right: 50px; float: right;display: none;}
#dashboard_hover{position: absolute; width: 50px; top:0px; height: 200px; right: 0px; float: right; cursor: pointer;}
#dashboard_arrow{position: absolute; width: 20px; top:200px; height: 200px; right: -10px; float: right; cursor: pointer;}
#status {position:absolute; float: left; width: 170px; height: 80px; bottom:50px; left: 65px; display: none;}
#node_search{position:relative; width: 100%; height: 25px;}
#input_search{border: none;border-radius: 7px;-moz-border-radius: 7px;-webkit-border-radius: 7px; outline: none; width: 98%; text-align: center;}
#img_logo {position:absolute; left: -20px; top:20px; opacity: 0; z-index: 25;}
#info_under {display: none; height: 80px;width: 170px; position: relative;float: left; overflow: visible; margin-bottom: 20px; }
#info_under_wrap{position:absolute; top:0; left: 0; width: 170px; height: 80px; background: white;-webkit-filter: blur(3px);filter: blur(3px); opacity: .8}
#info_under_content{position:absolute; top:0; left: 0; width: 164px; height: 74px; z-index: 5; padding: 3px 3px;}
#copyright {position:absolute;  width: 100%; margin-right: 50px; bottom: 20px; text-align: center;z-index: 25; opacity: 0}
#btn_ipmornitor{cursor: pointer;}
.node_hidden{display: none;}
#show_type{cursor: pointer}
</style>
<script type="text/javascript" src="js/jquery-1.10.1.min.js"></script>
<script type="text/javascript" src="js/jquery-ui-1.10.3.min.js"></script>
<script type="text/javascript" src="js/three.min.js"></script>
<script type="text/javascript" src="js/helvetiker_regular.typeface.js"></script>
<script type="text/javascript" src="js/malgun_gothic_regular.typeface.js"></script>
<script type="text/javascript" src="js/orbit.js"></script>
<script type="text/javascript" src="js/physi.js"></script>
<script type="text/javascript">
$(document).ready(function(){

	var width, height, renderer, scene, camera, projector, controls,loader;
	var node = new Array();	
	var now_dropping = 0;	
	var now_tracking = 0;
	var spotLight5;
	var text_ma = new Array();
	var search_me ='';
	var ipmornitor = 0;
	var show_option = 'ip';
	
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
text_ma[3] = new THREE.MeshPhongMaterial({specular: '#ffdc36',color: '#6b5fdf',emissive: '#a75fdf',shininess: 100})
	//초기화
	init();
	//애니메이션 호출
	setInterval(function() {

        requestAnimationFrame( pre_animate );

    }, 1000 / 10 );		
	

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
	var text2 = new THREE.TextGeometry(text, {size: 4,height: 0.2,font : "malgun gothic"});
	node[id] = new THREE.Mesh(text2,text_ma[random_number(3)]);
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
		$('#ipboard_content').height($(window).height() - $('#ipboard_content').offset().top-20);
		$('#ipboard').height($(window).height() - $('#ipboard').offset().top-60)
		$('#load_video').css('margin-top',$(window).height()/2-$('#load_video').height()/2+'px')
		$('#black_wrap').height(height)
		$('#dashboard_hover').height($(window).height() - $('#dashboard').offset().top-5)
		
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
		//renderer = new THREE.WebGLRenderer({antialias: true});
		renderer = new THREE.WebGLRenderer();
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
	// alert('0');
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
		    $('#img_logo').animate({'left':'20px','opacity':.3},1200)
		    $('#copyright').animate({'opacity':.9},1200)
	    $('#black_wrap').delay(18000).animate({'opacity':0},7000,function(){
		    $(this).hide()
		    clearInterval(tt);
		    
	    });


	}
	
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
        snow_1_systemMaterial = new THREE.ParticleBasicMaterial({ size: 50, sizeAttenuation: false, map: snow_1_texture, transparent: true, opacity :0.3,blending: THREE.AdditiveBlending});

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
                       // opacity = particleSystem.materials[0].opacity;

                for(var i = 0; i < numVertices; i++) {
                        var v = vertices[i];
                        if( v.y > 0 ) {
                                v.y -= speedY * Math.random();
                                v.x -= $('#traffic_speed').val() * Math.random();
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
                                v.x -= $('#traffic_speed').val() * Math.random();
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
		if(node[now_dropping].position.y < -91){
		now_dropping = 0;			
		drop_t = 0.001;
		}else{
			node[now_dropping].position.y = reset_y - (drop_v0*drop_t + (1/2)*(drop_a)*(drop_t*drop_t)*5000);
			drop_t += 0.001;
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
		if(now_tracking != 0 && now_tracking != 'scene'){
			camera.lookAt(node[now_tracking].position);
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
			//camera.lookAt( scene.position );	
		}


		renderer.render(scene,camera);


	}
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
		$(this).css('background',load_node.attr('bgcolor'))
		var status = $('#load_'+$(this).attr('id')+'_status').html();
	});
if(ipmornitor == 1){
	$('.td_board').each(function(){
	var load_node = $(this).attr('alt');
	$(this).css('background',$('#load_node_'+load_node).attr('bgcolor'))
	var this_pid = $('#load_node_'+load_node+'_pid').html();
	var this_uptcur = $('#load_node_'+load_node+'_uptcur').html();
	var this_downtcur = $('#load_node_'+load_node+'_downtcur').html();
	var this_name = $('#load_node_'+load_node+'_name').html();
	$(this).html("<strong><font size='2'>"+this_pid+"</font></strong><br/><font size='1'><font color='#eac45c'>"+this_uptcur+"</font>&nbsp;/&nbsp;<font color='#ea985c'>"+this_downtcur+"</font></font>")
	})
}
for(var nn=1;nn<255;nn++){
if(parseInt($('#load_node_'+nn+'_status').html()) == 1 || parseInt($('#load_node_'+nn+'_status').html()) == 2 ||parseInt($('#load_node_'+nn+'_status').html()) == 3){
	//alert(node[nn])
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

}, 500);

	//Document.Resize
	$( window ).resize(function() {
		var width2 = parseInt($('#canvas').width()), height2 =  parseInt($(window).height() - $('#canvas').offset().top);
		$('#dashboard').height($(window).height() - $('#dashboard').offset().top-30);
		$('#ipboard').height($(window).height() - $('#ipboard').offset().top-60);
		$('#load_video').css('margin-top',$(window).height()/2-$('#load_video').height()/2+'px')
		$('#ipboard_content').height($(window).height() - $('#ipboard_content').offset().top-20);
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

$('#btn_ipmornitor').click(function(){
	if(ipmornitor == 1){
		$('#ipboard').hide();
		
		$('#ipboard_content').hide();
		ipmornitor = 0;
	}else{
		$('#ipboard').show();
		$('#ipboard').height($(window).height() - $('#ipboard').offset().top-60)
		$('#ipboard_content').show();
		ipmornitor = 1;
	}
})

function singleClick(e) {
var now_status = $('#load_node_'+parseInt($(this).attr('alt'))+'_status').html();
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
			}
			now_tracking = parseInt($(this).attr('alt'));
			//alert(node[now_tracking].geometry.text)
		  	spotLight5.intensity = 1;
		  	load_timer = setInterval(function(){
		  	$('#info_ip').html($('#load_node_'+now_tracking+'_ip').html())
		  	if($('#load_node_'+now_tracking+'_name').html() == ''){
				$('#info_name').html('Wi-fi Address');  	
		  	}else{
			  	$('#info_name').html($('#load_node_'+now_tracking+'_name').html())
		  	}
			  	$('#info_uptcur').html($('#load_node_'+now_tracking+'_uptcur').html())
			  	$('#info_downtcur').html($('#load_node_'+now_tracking+'_downtcur').html())
		  	}, 300);
		  		$('#info_under').slideDown();
		  		controls.zoomIn(2.5,1)
		  		node[now_tracking].scale.set(2,2,2);
		  		now_tracking_z = node[now_tracking].position.z;
	
		  	//$('#test').html(parseInt(camera.position.x)+","+parseInt(camera.position.y)+","+parseInt(camera.position.z))
		  	
		  	}

	}else{
			var now_status = $('#load_node_'+parseInt($(this).attr('alt'))+'_status').html();
	
			if(now_tracking != 0 || now_tracking != 'scene'){
			//now_tracking2 = parseInt($(this).attr('alt'));
			  	spotLight5.intensity = 3;
			  	$('#info_ip').html('');
			  	$('#info_name').html('');
			  	$('#info_uptcur').html('');
			  	$('#info_downtcur').html('');
			  	clearInterval(load_timer);
			  	$('#info_under').slideUp();
			  	$('#info_top').slideUp();
			  	//clearInterval(timers);
			  	//controls.zoomIn(2.5,2)
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
	if(this_status == 0 || this_status == 4){
		$.ajax({
	            type: 'POST',
	            url: 'action/pass_node.php',
	            data: {
	                ip : $('#load_node_'+parseInt($(this).attr('alt'))+'_ip').html()
	            },
	            success: function(result) {
	            alert("\""+result+"\"가 접속하였습니다." );
	            },
	            error: function(result) {
	                alert("오류가 발생했습니다.");
	            }
	        });
	}else{	        
		$.ajax({
	            type: 'POST',
	            url: 'action/kill_node.php',
	            data: {
	                ip : $('#load_node_'+parseInt($(this).attr('alt'))+'_ip').html()
	            },
	            success: function(result) {
	            alert("\""+result+"\"의 접속을 차단하였습니다.");
	            },
	            error: function(result) {
	                alert("오류가 발생했습니다.");
	            }
	        });
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
});


  $('.td_node').draggable({helper:'clone'});
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
		for(var nn=1;nn<255;nn++){
			scene.remove(node[nn]);
			node[nn] ='no';
		}
	} else{
		$(this).attr('alt','name')
		$(this).attr('src','img/view_name.png');
		show_option = 'name';	
		for(var nn=1;nn<255;nn++){
			scene.remove(node[nn]);
			node[nn] ='no';
		}	
		
	}
 });
 
 $('#btn_signout').click(function(){
	location.href = 'signout.php'; 
 });
});


</script>
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

	<div id="ipboard">
	</div>	

<div id="ipboard_content">
<font size="4" color="#c6c6c6" ><strong>IP Monitoring Board</strong></font><br /><br />
	<div style="font-size:12px; width:100%; opacity:.7; margin:0 auto; position:relative; float:left">
				<?php
	
				for($i=0;$i<17;$i++){
						for($j=0;$j<15;$j++){
						$this_id = $i*15+$j+1;
							?>
							<div class="td_node td_board" bgcolor="#373737" style=" position:relative;float:left;margin:0 auto; height:25px; width:39px; cursor:pointer; color:white; overflow:hidden; margin-right:5px; margin-bottom:5px;" alt="<?=$this_id?>">
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
					?>
					<tr style="border:1px solid black;">
						<?php
						for($j=0;$j<15;$j++){
						$this_id = $i*15+$j+1;
							?>
							<td id="node_<?=$this_id?>" class="td_node" bgcolor="#373737" style="height:5px; width:5px; cursor:pointer; color:white" alt="<?=$this_id?>">
							</td>
							<?php
						}
						?>
					</tr>
					<?php
				}
				?>
		
		</table>
		<div style="display:none;" id="table_load"></div>
	</div>
	<img id="btn_ipmornitor" src="img/btn_popup.png" width="20" height="20" />
	<br /><br />
	<img src="img/title_2.png" width="165" height="29" /><br/>
	<div id="info_under">
		<div id="info_under_wrap"></div>
		<div id="info_under_content">
		<strong><font size="4"><span id="info_ip"></span></font></strong><br />
		<font  size="3"><span id="info_name"></span></font><br />
		<font  size="2" color="#eac45c"><img src="img/arrow_up.png" width="15" height="15" /><span id="info_uptcur"></span></font> / 
		<font  size="2" color="#ea985c"><img src="img/arrow_down.png" width="15" height="15" /><span id="info_downtcur"></span></font>
		</div><br /><br />
		</div>
	<img src="img/title_3.png" width="165" height="29" /><br />
	<span id="btn_signout">로그아웃</span>
	<img id="show_type" style="position:absolute; bottom:2px; left:78px; opacity:.7" src="img/view_ip.png" alt="ip" width="92" height="35" />
	</div>
	
	<div id="black_wrap"><video id="load_video" style="position:relative;" width="60%" src="video/loading.mp4" autoplay="YED"> </video></div>
<div id="canvas"></div></body>