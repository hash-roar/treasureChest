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
	12
	