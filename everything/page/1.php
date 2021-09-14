<?php

$item_array = scandir("./");

foreach($item_array as $item)
{
    $suffix = (explode(".",$item));
    if(count($suffix)>1){
        if(end($suffix)=="jpg" ||end($suffix)=="jpeg"){
            echo  " <div class=\"col-2 col-md-1  list_item\" style='background-image: url(\"./".$item."\");'><div class=\"ve_text\">
            玫瑰花的葬礼
         </div></div>";
        }
    }
}