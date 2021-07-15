# linux

## linux命令
### 帮助
	
	1.watis commond 列出命令作用
	2.whatis -w  "loca*" 正则匹配
	3.which command 查看路径
### 目录及文件命令
	
	1 find  ./ | wc -l 查看当前目录下文件个数
	2 cp -r  this that 复制目录
	3 ls | cat -n 带序号查看
	4 (locate or find)  $string 查找某文件
	5 (head  or tail) -$number 查看文件第几行
	6 tail -f $string  动态查看文件
	7 
### 文本处理

	1 find . -regex  ".*\(\.txt|\.pdf\)$" 正则查找
	2 find . -maxdepth 1 -type f 指定搜索深度,打印出当前目录的文件（深度为1）
	3 file命令可以检查文件具体类型（二进制或文本）
	4  cat file.txt| xargs 将多行输出转化为单行输出
	5 grep 文本搜索
	6 用tr进行转换
	7 cut 按列切分文本
	8 paste 按列拼接文本
	9 wc 统计行和字符的工具
	10sed 文本替换利器
	11awk 数据流处理工具
### 磁盘管理

	1 df du 查看磁盘空间
	2 tar 打包文件
	3 gzip 压缩文件
	
### 进程管理
 
 	1 ps 查询进程
 	2 top 实时显示进程消息
 	3 kill 杀死进程
 	4 
 	
### 性能监控

	1sar 查看cpu使用率
	2

### 网络工具

	1.netstat 列出端口
	2.liof 列出系统打开文件
	3.route 查看路由
	4.scp下载
     
### 用户管理

	1.ueradd添加用户
	2.chmod 更改文件读写权限
	3. 

### 