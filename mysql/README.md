
## mysql 
#### mysql远程连接速度慢
在mysql配置文件中加一个
skip-name-resolve

#### mysql模糊查询

mysql 中模糊查询有两种，一种LIKE， NOT LIKE 。另一种就是匹配 REGECXP， NOT REGEXP。

LIKE NOT LIKE

1、%
表示任意几个字符，比如：
select * from T_Bank where BankName like '%农%'
将查询出BankName中任何带有 ‘农’的数据。

2、_
任意单个字符，比如：
select * from T_Bank where BankName like '农'
只会查询出BankName 有三个字中间一个是‘农’的数据。

3、[]
表示匹配[ ] 内的任意一个字符比如：
select * from T_Bank where BankName like '[张李王]三'
只会查询出张三、李三、王三 的数据。
[0-9],[a-e] 表示[0123456789] [abcde]等。

4、[^]
表示取反，查询出不是某些匹配的数据比如：
select * from T_Bank where BankName like '[^张李王]三'
表示查询出排除张三、李三、王三 的数据。


REGECXP， NOT REGEXP

1、^
表示以某个字符开头的比如：
select * from T_Bank where BankName REGEXP '^中国'
查询出以中国开头的数据

2、$
表示查询出以某个字符结尾的比如：
select * from T_Bank where BankName REGEXP '移动$'
查询出以移动结尾的数据。

3、.
表示任意字符
select * from T_Bank where BankName REGEXP '.移.'
查询出以任意带有‘移’的数据。

4、*
匹配0 或者多个字符，前面必须有字符
select * from T_Bank where BankName REGEXP '中国'
查询出中国开头的所有字符

5、
select * from T_Bank where BankName REGEXP '中国'
查询出任意含有中国的数据

6、a
匹配任意多个a（包括空串)

7、a+
匹配任意多个a（不包括空串)

8、a?
匹配一个或零个a

9、a|b
匹配a或者b

