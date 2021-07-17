### mkdir

	mkdir -m $number (设置模式) -p (建立父级目录)

###  rmdir

	rmdir -p (删除指定目录后，若该目录的上层目录已变成空目录，则将其一并删除) 
	-v (显示命令的详细执行过程)

### tree

	tree -a(显示所有文件)  -d (显示目录) -f (显示完整路径) -L (限制目录层级)

### touch

	touch -t (使用指定时间)
	
### rename

	rename -v (输出替换) txt log 1.txt 2.txt 
	
### file 显示文件类型
### locate 查找文件

	update 更新数据库
	locate -c (输出数量) -l  (显示几条输出)
	-r (使用正则)  -i (忽略大小写)

### find 查找文件

	find -depth(指定深度) -exec (执行指令)
	-regex(正则)  -type(类型)
	-maxdepth(最大深度) -name (名字)
	-size (大小)  -delete(删除) 

	实例 :
	 find . -name "*.java"|xargs cat|grep -v ^$|wc -l 
	# 代码行数统计, 排除空行
	

	
### chmod  chown 改变文件权限

### mv

	mv -u (当源文件比目标文件新或者目标文件不存在时，才执行移动操作)
	-i (交互式操作，覆盖前先行询问用户，)

### rm
	
	rm -f 强制 -r 递归 -i 询问

### head

	head -n (查看前几行) 

###  tail

	tail -c (末尾字节) -n (末尾行)
	-f (新增内容) 

### sed  替换

### sar系统运行状态

	sar -e(设置显示报告时间) -R(内存)
	-u (cpu)  -x(进程)

### ps 进程查看工具

	ps -ef(列出所以程序) | grep (查找)
	-u (特定用户)  -C(按名字查找)
	-f (以树的风格显示父子进程关系)

### kill

	kill -s sig(信号名字
	-n (信号编号)
	-l(列出信号数字)
	发送信号到某个进程
	pkill -g(指定进程组) 
	(以名字杀死进程)
	killall  -i(交互式杀死进程)
###  
系统服务是在后台运行的应用程序，并且可以提供一些本地系统或网络的功能。我们把这些应用程序称作服务，也就是 Service。

	systemctl enable service 开启自启动
		         disable  关闭
		         status 检查服务状态 
		         start  or stop or restart or reload
		         
### 	crontab 周期启动

### curl 
	curl -silent 不显示进度条
	-O 写入文件   -o 写入指定文件
	-- progress 进度条
	- I 打印头信息
	$ curl -d 'login=emma' -d 'password=123' -X POST  https://wangchujiang.com/login
	post请求
	curl -d '@data.txt' https://wangchujiang.com/upload
	# 读取data.txt文件的内容，作为数据体向服务器发送。
	
### wget

	wget -O 指定下载文件  -c 断点续传
	--spider 测试下载链接
	-i 下载多个文件

### ip 查看网络信息
### hostname
### firewalld
### nc 端口扫描
### netstat

	netstat -l 监听的端口 -a所有端口
	-p 显示程序

### df查看磁盘使用
### 
	
		 