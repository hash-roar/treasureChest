## powershell命令
#### 历史命令

	 Cmdlet (Alias)       Description
          -------------------  ------------------------------------------
          Get-History (h)      Gets the command history.

          Invoke-History (r)   Runs a command in the command history.

          Add-History          Adds a command to the command history.

          Clear-History (clh)  Deletes commands from the command history.


#### 查看端口占用

	PS C:\Users\GZlaoBen> netstat -ano | findstr 8000
	协议      本地地址                         外部地址                  状态                       PID
	TCP    127.0.0.1:8000       0.0.0.0:0      LISTENING        12960

		PS C:\Users\GZlaoBen> tasklist | findstr 12960
	映像名称                       PID 会话名              会话       内存使用
	========================= ======== ================ =========== ============
	php.exe           12960 Console       1     15,524 K
	
