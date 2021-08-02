## redis单线程多路io复用


## key操作
	
	keys * 查看所有key
	exists key 
	type key
	del key
	unlink key 非阻塞删除(后续异步删除)
	expire key 设置过期时间
	select index 选择库
	dbszie 查看key数量
	flushdb 清空当前库
	flushall 清空所有库


## redis数据类型

### string
string 二进制安全

	set key value 设置相同值,覆盖
	get key
	append key value
	strlen
	setnx key value key不存在时设置
	incr
	decr 自减
	incrby key value
	mset 设置多个
	msetnx 都不存在成功
	getrange <> 范围
	setrange <>
	setex key time value 设置过期时间
	getset  用新值换旧值
string 内部实现类似于c++  array多分配空间



redis操作原子性,线程不会被打断

###  list
单键多值,按插入顺序排序,底层为双向链表

	lpush,rpush,入栈,入队
	lrange 取值 lrange 0 -1取全部值
	lpop,rpop.出栈
	rpoplpush key1 key2 key1右边取出插入key2左边
	lindex 获取元素
	llen
	linsert key before/after value newvalue 
	lrem  key n 从左到右
	lset key index value

list数据结构 quicklist 
元素较少时在连续空间中存储
元素较多时多个ziplist链表形式连接

### set
set与list不同,底层hash表

	sadd  key value
	smember 取出所有值
	sismember 判断是否值
	scard key 返回元素个数
	srem 删除元素
	spop 随机弹出
	sranmember 随机取出
	smove source destination value 把集合中一个元素移到另一个集合中
	sinter 取交集
	sunion 取并集
	sdiff 差集
	
### hash
key => (field=>value)

	hset key field value 
	hget key field
	hmset 设置多个
	hexists key field
	hkeys
	hvals
	hincrby
	hsetnx

### Zset
与set相似 ,有序,每个元素关联一个score

	zadd key   score value ....
	zrange key <> (withscores)
	zrangebyscore <>
	zincreby key step member 为元素score加上增量
	zrem key value 删除元素
	zcount key <> 返回元素
	zrank  key value返回排名

底层实现hash 关联value 和score
跳跃表 快速找到元素

## redis配置


	

	