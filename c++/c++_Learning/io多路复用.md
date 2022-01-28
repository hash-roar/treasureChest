## 原理
套接字通信时,监听文件描述符和通信文件描述符都会阻塞.
通过多路io服用,由操作系统内核检测文件描述符.不用自己维护
##类别
io多路复用select,poll,epoll

### select函数

	int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);
	时间定义:
	struct timeval {
	time_t second;
	susecond_t tv_usec;}

##  epoll
高效的红黑树
用户和内核共享内存
epoll能直接通知就绪的文件描述符数量;

### 水平触发模式

读:文件描述符还有数据未读就触发,

写: