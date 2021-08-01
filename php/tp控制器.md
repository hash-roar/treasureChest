## api规范

common.php中定义返回函数

function result($code,$message,$data,$httpStatus){
  $result= [
       "code" => $codel,
       "message" => $meaasge,
       "data"=> $data]
      return json($result,$httpStatus)