$(document).ready(function(){
	var aa = Morris.Area({
	  element: 'info_traffic_day',
	  data: [
	    { y: '2012-02-24 15:00', a: 100, b: 90 },
	    { y: '2012-02-24 16:00', a: 75,  b: 65 },
	    { y: '2012-02-24 17:00', a: 50,  b: 40 },
	    { y: '2012-02-24 18:00', a: 75,  b: 65 },
	    { y: '2012-02-24 19:00', a: 50,  b: 40 },
	    { y: '2012-02-24 20:00', a: 75,  b: 65 },
	    { y: '2012-02-24 21:00', a: 100, b: 90 }
	  ],
	  xkey: 'y',
	  ykeys: ['a', 'b'],
	  labels: ['192.168.0.1', '192.168.0.2']
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
	$('#status_on').attr('src','action/status_font.php?q='+number);
	}, 2000);
	
	
	
	
	var timer2 = setInterval(function(){
	var number = 1 + Math.floor(Math.random() * 253);
	var number2 = 10 + Math.floor(Math.random() * 90);
	var number3 = 10 + Math.floor(Math.random() * 90);
	var number4 = 10 + Math.floor(Math.random() * 90);
	var number5 = 10 + Math.floor(Math.random() * 90);
	$('#status_on').attr('src','action/status_font.php?q='+number);
	aa.setData([
	    { y: '2012-02-24 16:00', a: number4, b: number3 },
	    { y: '2012-02-24 17:00', a: number3,  b: number5 },
	    { y: '2012-02-24 18:00', a: number2,  b: number },
	    { y: '2012-02-24 19:00', a: number,  b: number4 },
	    { y: '2012-02-24 20:00', a: number5,  b: number3 },
	    { y: '2012-02-24 21:00', a: number,  b: number2 },
	    { y: '2012-02-24 22:00', a: number3, b: number2 }
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
        })
});