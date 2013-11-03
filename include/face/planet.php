<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<meta name="Generator" content="SeoSeungHyun WebKit">
<title>WebGL :: TEST</title>
<style>
/*Style*/
body{margin: 0 auto; background: black;}
#canvas{width: 100%;height: 800px;}
</style>
<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.10.1/jquery.min.js"></script>
<script type="text/javascript" src="js/three.min.js"></script>
<!-- ---------------- Custom Shader Code ------------------------ -->
<script id="vertexShader" type="x-shader/x-vertex">
	uniform vec3 viewVector;
	uniform float c;
	uniform float p;
	varying float intensity;
	void main() 
	{
	    vec3 vNormal = normalize( normalMatrix * normal );
		vec3 vNormel = normalize( normalMatrix * viewVector );
		intensity = pow( c - dot(vNormal, vNormel), p );
		
	    gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );
	}
</script>

<!-- fragment shader a.k.a. pixel shader -->
<script id="fragmentShader" type="x-shader/x-vertex"> 
	uniform vec3 glowColor;
	varying float intensity;
	void main() 
	{
		vec3 glow = glowColor * intensity;
	    gl_FragColor = vec4( glow, 1.0 );
	}
</script>
<script type="text/javascript">
$(document).ready(function(){
	var mouseX = 0, mouseY = 0;
	var windowHalfX = window.innerWidth / 2, windowHalfY = window.innerHeight / 2,windowY = window.innerHeight;
	var width, height, renderer, scene, camera, projector;
	var obj = new Array;
	var objects = [];
	//!	Pre Function
	//!	랜덤 값 추출 함수
	function random(min,max){
		return Math.round(Math.random()*max-min)+min;	
	}
	
	
	//!초기화 함수 load
	init();
	//pre_animate 호출
	requestAnimationFrame(pre_animate);
	
	
	
	
	
	
	
	
	
	//************************Draw Function*************************
	function init(){
		var width = parseInt($('#canvas').width()), height =  parseInt($('#canvas').height());
	
		//!렌더러 생성
		renderer = new THREE.WebGLRenderer({antialias: true, alpha: false});
		renderer.setSize(width, height);
		$('#canvas')[0].appendChild(renderer.domElement);	//렌더러 사이즈
		
		
		
		//!스크린 생성
		scene = new THREE.Scene();
		scene.fog = new THREE.FogExp2( 0x000000, 0.0009 );
			
			
			
		//카메라 객체 생성
		var angle=45;
		var aspect = width/height;
		var near = 1;
		var far = 2000;
		camera = new THREE.PerspectiveCamera(angle,aspect,near,far);
		camera.position.set(0,0,800);
		scene.add(camera);
		
		
		
		//Light 객체 생성
		scene.add( new THREE.AmbientLight( 0x404040 ) );
		scene.add( new THREE.AmbientLight( 0x404040 ) );
		scene.add( new THREE.AmbientLight( 0x404040 ) );
		
		
		//Click Projector 생성
		projector = new THREE.Projector();
		
		
		create_group(0,[0,0,0],60,60);
		create_group(1,[-500,-300,-100],10,50);
		create_group(2,[500,-100,-100],10,60);
		create_group(3,[500,100,-600],10,60);
		create_background(2500,20,2000,750,-800,1);
		create_background(300,35,2500,550,-100,2);
		//create_background(1,1000,500,0,-600,3);
	}
	
	function pre_animate(){
		var time = Date.now() * 0.002;
		
		for(i=0;i<obj.length;i++){
			//obj[i][0].rotation.y += 0.008;
			obj[i][2].forEach(function(item){
			var item_attr = item.class.split('|');
			var posit = parseInt(item_attr[0]);
			var speed = parseInt(item_attr[1]);
			//item.position.x = 150*posit*.03*( Math.sin(time/speed/0.8))+obj[i]['position'][0];
			//item.position.y = 150*posit*.03*( Math.cos(time/speed/0.8))+obj[i]['position'][1];
			//item.position.z = 150*posit*.03*( Math.cos(time/speed/0.8))+obj[i]['position'][2];
			});	
			//obj[i][1].material.uniforms.viewVector.value = new THREE.Vector3().subVectors( camera.position, obj[i][1].position );
		}
		
		
		camera.position.x += ( mouseX - camera.position.x ) * 0.1;
		camera.position.y += ( - mouseY - camera.position.y ) * 0.1;
		camera.lookAt( scene.position );
		renderer.render(scene,camera);
		requestAnimationFrame(pre_animate);
	}
	//************************Scapenet Function*************************
	//항성과 행성 생성에 대한 함수.
	function create_group(id,posit,count,size){
		//!중앙 개체 생성
		// 모든 객체의 배열화로 나중에 유지 보수가 편리하게 제작한다.
		// obj[id][0] = 가운데 항성
		// obj[id]['position'] = 가운데 항성
		// obj[id][1] = 해당 항성에 대한 Glow Object
		// obj[id][2][i>1] = 나머지 행성 id에 대한 Elements
		var sphereGeom = new THREE.SphereGeometry(size,size,size);
		var moonTexture = THREE.ImageUtils.loadTexture( 'img/sun.jpg' );
		var moonMaterial = new THREE.MeshBasicMaterial( { map: moonTexture } );
		obj[id] = new Array;
		obj[id][0] = new THREE.Mesh(sphereGeom, moonMaterial);
		obj[id]['position'] = posit;
		obj[id][0].position.set(posit[0],posit[1],posit[2]);
	    scene.add(obj[id][0]);
	    objects.push(obj[id][0])
		var light = new THREE.DirectionalLight( 0xffffff );;
		light.position.set(posit[0],posit[1]+2,posit[2]);
		scene.add(light);

		
		//Glow Effect 부분.
		var customMaterial = new THREE.ShaderMaterial( 
		{
	    	uniforms: 
	    	{ 
			"c":   { type: "f", value: 0 },
			"p":   { type: "f", value: 5.5 },
			glowColor: { type: "c", value: new THREE.Color(0xf7a67f) },
			viewVector: { type: "v3", value: camera.position }
			},
			vertexShader:   document.getElementById( 'vertexShader'   ).textContent,
			fragmentShader: document.getElementById( 'fragmentShader' ).textContent,
			side: THREE.FrontSide,
			blending: THREE.AdditiveBlending,
			transparent: true
		});
		
		scene.add(obj[id][1]);
		
		
		
		
		//!행성 생성 부분
		obj[id][2] = new Array;
	
		//mapping
		var map = new Array;
		map[0] = THREE.ImageUtils.loadTexture( 'img/planet_Dank_1182.png' );
		map[1] = THREE.ImageUtils.loadTexture( 'img/planet_hoth_1235.png' );
		map[2] = THREE.ImageUtils.loadTexture( 'img/planet_Bog_2275.png' );
	
		for (var i=0;i<count;i++){
		var material = new THREE.MeshLambertMaterial( { ambient: 0xbbbbbb, map:map[random(0,2)], side: THREE.DoubleSide } );
		var random_shape_size_2 = random(5,8);
		var geometry = new THREE.SphereGeometry(size/6+random_shape_size_2,size/6+random_shape_size_2,size/6+random_shape_size_2);
		//	var material = new THREE.MeshPhongMaterial({color : t_color(colors['red'])});
		var	mesh = new THREE.Mesh(geometry, material);
		mesh.position.set(posit[0],posit[1],posit[2]);
		mesh.class = random((size+40)*1.8,(size+40)*1.8+count)+'|'+random(30,50);
		scene.add(mesh);	
		obj[id][2].push(mesh);
		}
	
	}
	
	//Background Star 생성 함수
	function create_background(count,size,width,posit,depth,type){
			// create the particle variables
			var particleCount = count,
			particles = new THREE.Geometry(),
			pMaterial = new THREE.ParticleBasicMaterial({size: size,overdraw: true,map: THREE.ImageUtils.loadTexture("img/star"+type+".png"),
						blending: THREE.AdditiveBlending,transparent: true});
			particles.sortParticles = true;
			for(var p = 0; p < particleCount; p++) {
				// create a particle with random
				// position values, -250 -> 250
				var pX = Math.random() * width - posit,
				pY = Math.random() * width - posit,
				pZ = Math.random() * + depth,
				particle = new THREE.Vertex(new THREE.Vector3(pX, pY, pZ));
				// add it to the geometry
				particles.vertices.push(particle);
			}
			particleSystem = new THREE.ParticleSystem(particles,pMaterial);
			particles.sortParticles = true;
			scene.add(particleSystem);
	}
	
	function update_group(id,attr,val){
		
	}
	
	
	
	
	
	
			//************************Mouse Move Function*************************
			document.addEventListener( 'mousemove', onDocumentMouseMove, false );
			document.addEventListener('mousedown', onDocumentMouseDown, false);
          //  document.addEventListener('mousewheel', onDocumentMouseWheel, false);
			
			
       function onDocumentMouseWheel(event) {

            var fovMAX = 1500;
            var fovMIN = 100;

            camera.fov -= event.wheelDeltaY * 0.05;
            camera.fov = Math.max( Math.min( camera.fov, fovMAX ), fovMIN );
            camera.projectionMatrix = new THREE.Matrix4().makePerspective(camera.fov, $('#canvas').width() / $('#canvas').height(), camera.near, camera.far);

        }
			function onDocumentMouseMove( event ) {
				event.preventDefault();

				mouseXOnMouseDown = event.clientX - windowHalfX;
				mouseYOnMouseDown = event.clientY - windowY;
				//targetRotationOnMouseDown = targetRotation;
				mouseX = event.clientX - windowHalfX;
				mouseY = event.clientY - windowY;
				
				document.addEventListener( 'mouseup', onDocumentMouseUp, false );
				document.addEventListener( 'mouseout', onDocumentMouseOut, false );
				//targetRotation = targetRotationOnMouseDown + ( mouseX - mouseXOnMouseDown ) * 0.02;
				//targetRotation = targetRotationOnMouseDown + ( mouseY - mouseYOnMouseDown ) * 0.02;

			}

			function onDocumentMouseUp( event ) {

				document.removeEventListener( 'mousemove', onDocumentMouseMove, false );
				document.removeEventListener( 'mouseup', onDocumentMouseUp, false );
				document.removeEventListener( 'mouseout', onDocumentMouseOut, false );
			}

			function onDocumentMouseOut( event ) {
				document.removeEventListener( 'mousemove', onDocumentMouseMove, false );
				document.removeEventListener( 'mouseup', onDocumentMouseUp, false );
				document.removeEventListener( 'mouseout', onDocumentMouseOut, false );
			}
			function onDocumentScrollUp( event ) {
				document.removeEventListener( 'mousemove', onDocumentMouseMove, false );
				document.removeEventListener( 'mouseup', onDocumentMouseUp, false );
				document.removeEventListener( 'mouseout', onDocumentMouseOut, false );
			}
});
</script>
</head>

<body>
<div id="canvas"></div>
</body>