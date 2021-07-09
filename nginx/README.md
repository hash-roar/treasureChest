# nginx
本人喜欢在powershell上折腾,因此在windows测试使用nginx

### windows下nginx命令
0.总览

	Options:
	  -?,-h         : this help
	  -v            : show version and exit
	  -V            : show version and configure options then exit
	  -t            : test configuration and exit
	  -T            : test configuration, dump it and exit
	  -q            : suppress non-error messages during configuration testing     
	  -s signal     : send signal to a master process: stop, quit, reopen, reload  
	  -p prefix     : set prefix path (default: NONE)
	  -c filename   : set configuration file (default: conf/nginx.conf)
	  -g directives : set global directives out of configuration file

nginx -h：查看帮助

nginx -v：查看nginx的版本

nginx -V：查看版本和nginx的配置选项

nginx -t：测试配置文件的正确性

Nginx -T: 测试配置文件，并显示配置文件（这个命令可以快速查看配置文件）

nginx -q：测试配置文件，但是只显示错误信息

nginx -s：发送信号，下面详细介绍

nginx -p：设置前缀

nginx -c：设置配置文件

nginx -g：附加配置文件路径

1.检查配置文件是否有效
	
	D:\Programs\nginx-1.14.2>nginx -t -c conf/nginx.conf

1.1设置配置文件

	nginx -c

2.查看版本

	D:\Programs\nginx-1.14.2>nginx -v
	nginx version: nginx/1.14.2
3.启动NGINX服务

	D:\Programs\nginx-1.14.2>start nginx
4.重载NGINX服务

	D:\Programs\nginx-1.14.2>nginx -s reload
5.杀掉NGINX进程
	
	Stop-Process -Name nginx
	优雅地停止服务:
	./nginx.exe -s quit
6.批处理文件

	@echo off
	rem 提供Windows下nginx的启动，重启，关闭功能
	
	echo ==================begin========================
	
	cls 
	::ngxin 所在的盘符
	set NGINX_PATH=D:
	
	::nginx 所在目录
	set NGINX_DIR=D:\Programs\nginx-1.14.2\
	color 0a 
	TITLE Nginx 服务管理
	
	CLS 
	
	echo. 
	echo. ** Nginx 管理程序  *** 
	echo. 
	
	:MENU 
	
	echo. ***** nginx 进程list ****** 
	::tasklist|findstr /i "nginx.exe"
	tasklist /fi "imagename eq nginx.exe"
	
	echo. 
	
	if ERRORLEVEL 1 (
	echo nginx.exe不存在
	) else (
	echo nginx.exe存在
	)
	
	echo. 
	::*************************************************************************************************************
	echo. 
	echo.  [1] 启动Nginx  
	echo.  [2] 关闭Nginx  
	echo.  [3] 重启Nginx 
	echo.  [4] 刷新控制台  
	echo.  [5] 重新加载Nginx配置文件
	echo.  [6] 检查测试nginx配置文件
	echo.  [7] 查看nginx version
	echo.  [8] 打开错误日志
	echo.  [9] 删除错误日志
	echo.  [0] 退 出 
	echo. 
	
	echo.请输入选择的序号:
	set /p ID=
	IF "%id%"=="1" GOTO start 
	IF "%id%"=="2" GOTO stop 
	IF "%id%"=="3" GOTO restart 
	IF "%id%"=="4" GOTO MENU
	IF "%id%"=="5" GOTO reloadConf 
	IF "%id%"=="6" GOTO checkConf 
	IF "%id%"=="7" GOTO showVersion 
	IF "%id%"=="8" GOTO openErrorLog
	IF "%id%"=="9" GOTO delErrorLog
	IF "%id%"=="0" EXIT
	PAUSE 
	
	::*************************************************************************************************************
	::启动
	:start 
	call :startNginx
	GOTO MENU
	
	::停止
	:stop 
	call :shutdownNginx
	GOTO MENU
	
	::重启
	:restart 
	call :shutdownNginx
	call :startNginx
	GOTO MENU
	
	::检查测试配置文件
	:checkConf 
	call :checkConfNginx
	GOTO MENU
	
	::重新加载Nginx配置文件
	:reloadConf 
	call :checkConfNginx
	call :reloadConfNginx
	GOTO MENU
	
	::显示nginx版本
	:showVersion 
	call :showVersionNginx
	GOTO MENU   
	
	::打开错误日志
	:openErrorLog 
	call :openErrorLogNginx
	GOTO MENU   
	
	::删除错误日志
	:delErrorLog 
	call :delErrorLogNginx
	GOTO MENU
	
	::*************************************************************************************
	::底层
	::*************************************************************************************
	:shutdownNginx
	echo. 
	echo.关闭Nginx...... 
	taskkill /F /IM nginx.exe > nul
	echo.OK,关闭所有nginx 进程
	goto :eof
	
	:startNginx
	echo. 
	echo.启动Nginx...... 
	IF NOT EXIST "%NGINX_DIR%nginx.exe" (
	echo "%NGINX_DIR%nginx.exe"不存在
	goto :eof
	)
	
	%NGINX_PATH% 
	cd "%NGINX_DIR%" 
	
	IF EXIST "%NGINX_DIR%nginx.exe" (
	echo "start '' nginx.exe"
	start "" nginx.exe
	)
	echo.OK
	goto :eof
	
	
	:checkConfNginx
	echo. 
	echo.检查测试 nginx 配置文件...... 
	IF NOT EXIST "%NGINX_DIR%nginx.exe" (
	echo "%NGINX_DIR%nginx.exe"不存在
	goto :eof
	)
	
	%NGINX_PATH% 
	cd "%NGINX_DIR%" 
	nginx -t -c conf/nginx.conf
	
	goto :eof
	
	::重新加载 nginx 配置文件
	:reloadConfNginx
	echo. 
	echo.重新加载 nginx 配置文件...... 
	IF NOT EXIST "%NGINX_DIR%nginx.exe" (
	echo "%NGINX_DIR%nginx.exe"不存在
	goto :eof
	)
	
	%NGINX_PATH% 
	cd "%NGINX_DIR%" 
	nginx -s reload
	
	goto :eof
	
	::显示nginx版本
	:showVersionNginx
	echo. 
	%NGINX_PATH% 
	cd "%NGINX_DIR%" 
	nginx -V
	goto :eof
	
	::打开错误日志
	:openErrorLogNginx
	echo. 
	echo.打开错误日志...... 
	%NGINX_PATH% 
	cd "%NGINX_DIR%"  
	start logs/error.log
	goto :eof
	
	::删除错误日志
	:delErrorLogNginx
	echo. 
	echo.删除错误日志...... 
	%NGINX_PATH% 
	cd "%NGINX_DIR%"  
	del logs\error.log
	goto :eof

### 配置结构

	# 这里是一些配置
	...
	http {
	  # 这里是一些配置
	  ...
	  # 这部分可能存在于/etc/nginx/conf.d/目录下
	  upstream {
	
	  }
	  server {
	    listen 8080;
	    root /data/up1;
	
	    location / {
	    }
	  }
	  server {
	    listen 80;
	    root /data/up2;
	
	    location / {
	    }
	  }
	  这里是一些配置
	  ...
	}
	
	mail {
	}


### nginx搭建文件服务器
修改conf文件

	server {
	  listen 80; 
	  server_name myServerNamne; # 自己PC的ip或者服务器的域名
	  charset utf-8; # 避免中文乱码 
	  root /www/static; # 存放文件的目录 
	  location / { 
	    autoindex on; # 索引 
	    autoindex_exact_size on; # 显示文件大小 
	    autoindex_localtime on; # 显示文件时间 
	  }
	}

### 多个webapp配置


