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

### 网络排查

## 查看端口

lsof -i:端口号 查看端口占用

	lsof -i:8080：查看8080端口占用
	lsof abc.txt：显示开启文件abc.txt的进程
	lsof -c abc：显示abc进程现在打开的文件
	lsof -c -p 1234：列出进程号为1234的进程所打开的文件
	lsof -g gid：显示归属gid的进程情况
	lsof +d /usr/local/：显示目录下被进程开启的文件
	lsof +D /usr/local/：同上，但是会搜索目录下的目录，时间较长
	lsof -d 4：显示使用fd为4的进程
	lsof -i -U：显示所有打开的端口和UNIX domain文件

netstat -tunlp | grep 端口号

	netstat -ntlp   //查看当前所有tcp端口
	netstat -ntulp | grep 80   //查看所有80端口使用情况
	netstat -ntulp | grep 3306   //查看所有3306端口使用情况

### telnet

telnet ip port 查看端口通畅

## linux工具

### sed

流编辑器

```bash
sed -r '命令' fileName;
sed -nr #扩展正则
```

| 功能 |                |
| ---- | -------------- |
| s    | 替换substitute |
| p    | print          |
| d    | delete         |
| cal  | c/a/i          |

**一行一行读判断执行**,**默认输出加-n不输出**

#### 查找

```bash
sed  '1p' #根据行号查找
sed '1,5p'#范围
sed '/正则/p' #正则
sed '//,//p' #正则范围
```

#### 删除

```bash
sed '1d'
sed '1,5d'
删除文件空行
sed -r '/^$/d' filename
!取反:
sed -r '/^$/!p' filename#不显示
```

#### 插入

```bash
c #替代
sed '3a content' filename #3行下加一行
i#上插一行
```

#### 替换

```bash
sed 's###g' #g 全局替换,默认只替换每行第一个
```

#### 引用

```bash
sed -r 's#(.*)#\1#g' #后向引用
sed 
```

