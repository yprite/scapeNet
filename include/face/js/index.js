$(document).ready(function(){
	$('.dashboard_wrap').hide();
	$('.content_main').show();
	var interval = 10;
	var aa = Morris.Area({
	  element: 'info_traffic_day',
	  data: [
	    { y: '2013-10-24 15:00', a: 100, b: 90 },
	    { y: '2013-10-24 16:00', a: 75,  b: 65 },
	    { y: '2013-10-24 17:00', a: 50,  b: 40 },
	    { y: '2013-10-24 18:00', a: 75,  b: 65 },
	    { y: '2013-10-24 19:00', a: 50,  b: 40 },
	    { y: '2013-10-24 20:00', a: 75,  b: 65 },
	    { y: '2013-10-24 21:00', a: 100, b: 90 }
	  ],
	  xkey: 'y',
	  ykeys: ['a', 'b'],
	  labels: ['210.118.34.222', '210.118.34.65']
	});
	
	Morris.Donut({
	  element: 'info_donut_1',
	  data: [
	    {label: "Mail", value: 12},
	    {label: "HTTP", value: 30},
	    {label: "FTP", value: 20}
	  ]
	});
	
	Morris.Donut({
	  element: 'info_donut_2',
	  data: [
	    {label: "torrent", value: 70},
	    {label: "www", value: 10},
	    {label: "Etc", value: 500}
	  ]
	});
	
	Morris.Donut({
	  element: 'info_donut_3',
	  data: [
	    {label: "test1", value: 5},
	    {label: "test2", value: 3},
	    {label: "test3", value: 1}
	  ]
	});
	
	var timer1 = setInterval(function(){
	var number = 1 + Math.floor(Math.random() * 253);
	$('#status_on').attr('src','http://sshdb.com/ssm/status_font.php?q='+number);
	}, 2000);
	
	var timer3 = setInterval(function(){
			$.ajax({
			type: 'POST',
			url: '/action/view_face.php',
			success: function(result) {
				var str = result.replace(/L/gi, '<br />&nbsp;&nbsp;');
				
			$('#txt_mornitor').html("<br />&nbsp;&nbsp;<strong><u>"+str+"</u></strong>");
			},
			error: function(result) {
			}
	});
	}, interval);
	
	
	var timer2 = setInterval(function(){
	var number = 1 + Math.floor(Math.random() * 253);
	var number2 = 10 + Math.floor(Math.random() * 90);
	var number3 = 10 + Math.floor(Math.random() * 90);
	var number4 = 10 + Math.floor(Math.random() * 90);
	var number5 = 10 + Math.floor(Math.random() * 90);
	aa.setData([
	    { y: '2013-10-24 16:00', a: number4, b: number3 },
	    { y: '2013-10-24 17:00', a: number3,  b: number5 },
	    { y: '2013-10-24 18:00', a: number2,  b: number },
	    { y: '2013-10-24 19:00', a: number,  b: number4 },
	    { y: '2013-10-24 20:00', a: number5,  b: number3 },
	    { y: '2013-10-24 21:00', a: number,  b: number2 },
	    { y: '2013-10-24 22:00', a: number3, b: number2 }
	  ])
	}, 5000);
	
	aa.on('click',function(id,row){
		alert(id+','+print_r(row));
	});
	function print_r(array) {
    var str='';
    for(var i in array) {

        str += '['+ i+':'+array[i]+'] '
    }
    return str;
}


	var mornitor_on = 1;
	$('#mornitor_toggle').click(function(){
		if(mornitor_on == 0){
		$('#mornitor_content').fadeTo(250,1);
			$('#mornitor_wrap').slideDown();
			$(this).html('︿');
			mornitor_on = 1
		}else{
			$('#mornitor_content').fadeTo(250,0.08);
			$('#mornitor_wrap').slideUp();			
			mornitor_on = 0
			$(this).html('﹀');
		}
	})	
	
	$('.func_btn').mouseover(function(){
		$(this).attr('src',$(this).attr('src').replace('.png', '_0.png'));
	})
	.mouseout(function(){
		$(this).attr('src',$(this).attr('src').replace('_0.png', '.png'));
	});
	
	var terminer_on = 0;
	$('#btn_func_terminer').click(function(){
		if(terminer_on == 0){
			$('#terminer_wrap').slideDown();
			$('#terminer_area').focus();
			$('#terminer_area').val($('#terminer_area').val()+'');
			terminer_on = 1
		}else{
			$('#terminer_wrap').slideUp();			
			$('#terminer_area').blur();
			terminer_on = 0
		}

	});
	$('#terminer_area').keyup(function(e){
		var code = (e.keyCode ? e.keyCode : e.which);
	     if(code == 13) { //Enter keycode
	       //Do something
	       $.ajax({
			type: 'POST',
			data: { q : $('#terminer_area').val()},
			url: '/action/terminer.php',
			success: function(result) {
			$('#terminer_area').blur();
				eval(result);
			$('#terminer_area').focus();
			},
			error: function(result) {
			}
			});
	         $(this).val('Scapenet > ');
	     }
	})
	$('#input_search').keyup(function(){
		if(!$(this).val()){
			$('.content_main').show();
		}else{
			$('.content_main').hide();
		}
	});
	$(".navi_title").click(function(){
            var submenu = $(this).next("ul");
 
            // submenu 가 화면상에 보일때는 위로 보드랍게 접고 아니면 아래로 보드랍게 펼치기
            if( submenu.is(":visible") ){
                submenu.slideUp();
            }else{
                submenu.slideDown();
            }
    });
    $('.btn_dashboard').click(function(){
	    $('.dashboard_wrap').hide();
	    $('.content_main').show();
	    $('.map_node').each(function(){
		    $(this).stop();
	    });
	    
    })
    .mouseover(function(){
	    $(this).css('color','#2490ce');
    })
    .mouseout(function(){
	    $(this).css('color','#393939');
    });
    
    function change_node(){
    var return_color = function(rand){
	    switch(rand){
		    case 0 : return "#949494"; break;
		    case 1 : return "#38dc89"; break;
		    case 2 : return "#dd5f8f"; break;
		    default : return "#dce636"; break;
	    }
    }
    var result = new Array();
    for(i=0;i<255;i++){
    var rands = Math.floor(Math.random() * 4);
    
    result[i] = return_color(rands);
    }
	    $('.map_node').each(function(){
		    $(this).delay(3000).animate({'backgroundColor': result[$(this).attr('alt')]},600,function(){
		    change_node(); 
			});
	    });
    }
    
    $('.li_1').click(function(){
	    switch($(this).attr('alt')){
		    case 'ipm' :$('.dashboard_wrap').hide();$('.ipm_main').show();change_node();break;
	    }
    });
    $('li').mouseover(function(){
	    $(this).css('color','#2490ce');
    })
    .mouseout(function(){
	    $(this).css('color','#6d6d6d');
    })

});