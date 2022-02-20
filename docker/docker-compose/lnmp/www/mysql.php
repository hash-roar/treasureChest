  <?php  
                                                             
 $conn = new mysqli("lnmp_mysql",'root','123456');          
  if($conn->connect_error)                                   
  {                                                          
      die("connect error".$conn->connect_error);                  
  }                                                          
                                                             
 echo "connecnt success";                                        
        
  ?>                                                              
            
