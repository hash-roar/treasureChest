let fs =require("fs");

fs.open("1.txt","r",(error,fd)=>{
    console.log(fd);
});