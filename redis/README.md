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
### bitmaps

	setbit key offset value
	getbit key offset
	bitcount key 统计1操作
	bitop 与或非操作
	
### hyperloglog

	pfadd

### geo
地理信息

	geoadd key longtitude 
## redis配置

	daemonize no       Redis 默认不是以守护进程的方式运行，可以通过该配置项修改，使用 yes 启用守护进程（Windows 不支持守护线程的配置为 no ）
	pidfile /var/run/redis.pid         当 Redis 以守护进程方式运行时，Redis 默认会把 pid 写入 /var/run/redis.pid 文件，可以通过 pidfile 指定
	loglevel notice
	 maxclients 128      设置同一时间最大客户端连接数，默认无限制，Redis 可以同时打开的客户端连接数为 Redis 进程可以打开的最大文件描述符数，如果设置 maxclients 0，表示不作限制。
	 当客户端连接数到达限制时，Redis 会关闭新的连接并向客户端返回 max number of clients reached 错误信息
	 include /path/to/local.conf    指定包含其它的配置文件，可以在同一主机上多个Redis实例之间使用同一份配置文件，而同时各个实例又拥有自己的特定配置文件
	 
	
## 发布订阅
一种通信模式


## redis验证码

