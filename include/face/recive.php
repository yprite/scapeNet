<?php
  3
    4    $pipe="pipout";
	  5    if(!file_exists($pipe)) {
		    6       echo "I am not blocked!";
			  7    }
			    8    else {
					  9       //block and read from the pipe
					   10       $f = fopen($pipe,"r");
					    11       echo fread($f,1024);
						 12    }
						  13 ?>

