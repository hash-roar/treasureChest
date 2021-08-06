## gdb
 gcc 编译时加上-g 
 
 ### 使用
 
 gdb app
 
 #### 传入信息
 set args 1 2 3 4
 show  args
 
 #### 启动程序
 
 	start 运行第一行代码
 	run 运行到断点
 
 #### list命令
 
 	list查看main文件
 	list n 查看某行,上下5行
 	list 函数名
 	l 文件名:行号
 	l 文件名:函数
 	
### 断点

	b n 设置断点
	b 文件名:函数名 设置断点
	b n-m 设置一堆断点
	d n(编号) 删除断点
	dis n 使断点无效
	ena n 使断点生效

### 调试相关

	继续运行continue (c)运行到下一个断点
	p name 打印变量
	ptype name 打印变量类型
	display name 自动打印变量名
	info display 查看跟踪的变量
	undispaly n 删除跟踪变量

### 单步调试

	step s 单步执行,进入函数
	next n 不进入函数
	finish 结束函数
	until 跳出循环

### 设置变量值

	set var name =value
	