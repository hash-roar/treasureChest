## make构建工具

### makefile
make根据文件编译

	makefile规则:
	目标:依赖
	(tab)命令
	make执行时只执行第一条规则,如果依赖不存在时才往下寻找生成依赖命令
	ep:
	hello:hello.c
		gcc hello.c -o hello
	
###makefile变量

	自定义变量 abc=123          $(abc)
	预定义变量 
	自动变量 $* 目标文件名称 $+所有依赖文件  $@目标文件名称(有扩展名)
	$^所有依赖(不重复  $< 第一个依赖

### makefile模式匹配

	% 匹配的依赖文件名字

### makefie  函数

	wildcard 
	ep: src= $(wildcard /home/rui/*.o )
	patsubst 

### makefile伪目标
	
	.PHONY:clean
	clean:
		rm $(obj)
### make  

	make  target 生成特定目标
	目标不存在时会更新
	依赖小于目标时间,更新
	