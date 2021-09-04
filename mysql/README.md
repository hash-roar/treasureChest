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

## 配置
log-bin 二进制文件
log-error 错误日志
log 查询日志

## mysql逻辑架构

## 引擎

myisam 不支持外键,表锁,表空间小
innodb 

## 语法

### 增删改查

```sql
insert into table (field1,field2) values(value1,value2);

delete from table where

update table set field1 = value1 where

select columName from table where condition (and|or) condition
```

### 其他

```sql
模糊查询:
SELECT field1, field2,...fieldN 
FROM table_name
WHERE field1 LIKE condition1 [AND [OR]] filed2 = 'somevalue'

UNION:

SELECT expression1, expression2, ... expression_n
FROM tables
[WHERE conditions]
UNION [ALL | DISTINCT]
SELECT expression1, expression2, ... expression_n
FROM tables
[WHERE conditions];

排序:
SELECT field1, field2,...fieldN FROM table_name1, table_name2...
ORDER BY field1 [ASC [DESC][默认 ASC]], [field2...] [ASC [DESC][默认 ASC]]

结果集分组:
SELECT column_name, function(column_name)
FROM table_name
WHERE column_name operator value
GROUP BY column_name;

```

### 连接

```sql
内连接,查公共部分:
select  a.field1 a.fieled2 b.field1 from table1 as a jion table2 as b on a.field1 = b.field1
左连接,保留左边的:
select  a.field1 a.fieled2 b.field1 from table1 as a left jion table2 as b on a.field1 = b.field1
全连接,全部保留:

select  a.field1 a.fieled2 b.field1 from table1 as a full  jion table2 as b on a.field1 = b.field1
```

### null值

 MySQL 使用 SQL SELECT 命令及 WHERE 子句来读取数据表中的数据,但是当提供的查询条件字段为 NULL 时，该命令可能就无法正常工作。

为了处理这种情况，MySQL提供了三大运算符:

- **IS NULL:** 当列的值是 NULL,此运算符返回 true。
- **IS NOT NULL:** 当列的值不为 NULL, 运算符返回 true。
- **<=>:** 比较操作符（不同于 = 运算符），当比较的的两个值相等或者都为 NULL 时返回 true。

关于 NULL 的条件比较运算是比较特殊的。你不能使用 = NULL 或 != NULL 在列中查找 NULL 值 。

在 MySQL 中，NULL 值与任何其它值的比较（即使是 NULL）永远返回 NULL，即 NULL = NULL 返回 NULL 。

MySQL 中处理 NULL 使用 IS NULL 和 IS NOT NULL 运算符。

### 正则

```sql
SELECT name FROM person_tbl WHERE name REGEXP '正则';
```

### 事务

- 在 MySQL 中只有使用了 Innodb 数据库引擎的数据库或表才支持事务。
- 事务处理可以用来维护数据库的完整性，保证成批的 SQL 语句要么全部执行，要么全部不执行。
- 事务用来管理 insert,update,delete 语句

**事务特性**:

- **原子性：**一个事务（transaction）中的所有操作，要么全部完成，要么全部不完成，不会结束在中间某个环节。事务在执行过程中发生错误，会被回滚（Rollback）到事务开始前的状态，就像这个事务从来没有执行过一样。
- **一致性：**在事务开始之前和事务结束以后，数据库的完整性没有被破坏。这表示写入的资料必须完全符合所有的预设规则，这包含资料的精确度、串联性以及后续数据库可以自发性地完成预定的工作。
- **隔离性：**数据库允许多个并发事务同时对其数据进行读写和修改的能力，隔离性可以防止多个事务并发执行时由于交叉执行而导致数据的不一致。事务隔离分为不同级别，包括读未提交（Read uncommitted）、读提交（read committed）、可重复读（repeatable read）和串行化（Serializable）。
- **持久性：**事务处理结束后，对数据的修改就是永久的，即便系统故障也不会丢失。

### alter

```sql
删除字段
alter table tablename drop field

增加字段
alter table tablename add name ... [after|before]

改变字段
alter table tablename modify name ... 

```

### 索引

```sql
创建索引
CREATE INDEX indexName ON table_name (column_name)

添加索引
ALTER table tableName ADD INDEX indexName(columnName)

删除索引
DROP INDEX [indexName] ON mytable; 

唯一索引(索引值必须唯一):
CREATE UNIQUE INDEX indexName ON mytable(username(length)) 



```

### 临时表



## 索引

#### 索引介绍

**索引字段会排序**,**查找更快**,**本质是数据结构**

**排好序的快速查找数据结构**

**索引两大功能**:

查找和排序

以引用或指针的方式指向数据(b树索引)

#### 索引优势劣势

**优势**:提高检索速度

**劣势**:减少写操作速度

#### 分类

**单值索引**:一个索引只包含单个列,一个表可以有多个索引

**唯一索引**:索引列的值必须唯一,允许有空值

**符合索引**:多个列

#### 语法

```sql
增
create [unique] index indexname on table(Colum)
alter 
删
drop index indexname on table
查
show index from 
```

#### 索引结构

**bTree,hash,full-text,r-tree**

##### bTree

非叶子节点不储存数据

#### 适合建索引结构

1. 主键
2. 频繁查询
3. 外键
4. 频繁更新的不适合
5. where用不到
6. 排序字段
7. 查询中统计或分组字段

#### 不适合索引

1. 数据重复且分布平均

## 性能分析

### 常见瓶颈

1. cpu饱和

2. io瓶颈

3. 硬件

###  查询优化(explain)

```sql
explain sql语句
```

**id**:包含查询顺序 ,id高先执行,相同顺序执行(derived(衍生))

**select-type**:

1. simple 普通查询,无子查询,无union
2. subquery select,where列中包含子查询
3. primary 查询中最外层
4. derived  from 包含的子查询放在临时表中





















## jion查询
### sql执行顺序

**从from 读**

### jion查询

```sql
内连:取出在两个表共有的
select table1 jion table2 on t1.id = t2.id
左连:
select t1  left jion t2 on t1.id =t2.id 
 右连:
 左内:
select t1  left jion t2 on t1.id =t2.id where t2.id =null
 全:
select t1 full jion t2 on 
```

------

## 索引优化

