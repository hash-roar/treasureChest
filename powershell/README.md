# powershell

### 守护进程

Linux Daemon（守护进程）是运行在后台的一种特殊进程。它独立于控制终端并且周期性地执行某种任务或等待处理某些发生的事件。它不需要用户输入就能运行而且提供某种服务，不是对整个系统就是对某个用户程序提供服务。Linux系统的大多数服务器就是通过守护进程实现的。常见的守护进程包括系统日志进程syslogd、 web服务器httpd、邮件服务器sendmail和数据库服务器mysqld等。
Windows下类似概念为服务:

	利用powershell操作Windows服务:
		利用get-commod查看service相关服务:
			get-commond *service*
		利用get-help查看cmdt用法:
			get-help   -name get-service
		Start-Service，启动服务。
		
		Stop-Service，停止服务。
		
		Restart-Service，重启服务。
		
		Suspend-Service，挂起/暂停服务。
		
		Resume-Service，继续服务。
		
		Set-Service，设置服务的属性。
		
		New-Service，创建新服务。	
