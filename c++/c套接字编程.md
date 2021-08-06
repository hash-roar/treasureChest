## 大小端转换

	现在电脑都是小端存储,因此在发送网络数据时需要把小段转化为大段.

### 整形转换

	// 将一个短整形从主机字节序 -> 网络字节序
	uint16_t htons(uint16_t hostshort);	
	// 将一个整形从主机字节序 -> 网络字节序
	uint32_t htonl(uint32_t hostlong);	
	
	// 将一个短整形从网络字节序 -> 主机字节序
	uint16_t ntohs(uint16_t netshort)
	// 将一个整形从网络字节序 -> 主机字节序
	uint32_t ntohl(uint32_t netlong);

### ip地址转换

	// 点分十进制IP -> 大端整形
	in_addr_t inet_addr (const char *cp);
	
	// 大端整形 -> 点分十进制IP
	char* inet_ntoa(struct in_addr in);

## 通信流程
### 客户端

socket->connect->send->recv->close

	创建套接字
	连接
	通信
	断开连接

####服务端

socket->bind->listen->accept->recv->send->recv->close

	socket创建套接字,得到文件描述符
	bind 绑定端口ip
	listen监听端口
	accept 等待连接,并得到一个新的描述符,没有连接就阻塞,
	close两次挥手


## 函数
###socket
	#include <sys/types.h>         
       	#include <sys/socket.h>
	int socket(int domain, int type, int protocol);
	On success, a file descriptor for the new socket is returned.  On error, -1 is  returned,  and
       	errno is set appropriately.

### bind

	#include <sys/types.h>         	
	#include <sys/socket.h>
	
	int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);addr大端

### listen

	int listen(int sockfd, int backlog);backlog(max128)一次性能检测多少个连接
	On success, zero is returned.  On error, -1 is returned, and errno is set appropriately

### accept 

	#include <sys/types.h>          /* See NOTES */
	       #include <sys/socket.h>
	
	       int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) 
	      On  success, these system calls return a nonnegative integer that is a file descriptor for the
       accepted socket.  On error, -1 is returned, and errno is set appropriately.
    

### connect
客户端也需要端口
 自动绑定随机端口
`	 #include <sys/types.h>          /* See NOTES */
         	 #include <sys/socket.h>

      	 int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);
	             If the connection or binding succeeds, zero is returned.  On error, -1 is returned, and  errno
	       is set appropriately
	       
### 通信

	read()
	recv()接受
	发送:
	write()    send()
		       