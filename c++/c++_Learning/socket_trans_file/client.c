#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

int main(int argc,char *arg[])
{
    printf("传入%d参数\n", argc);
    char *self_path = arg[0];
    char *file_path = arg[1];
    printf("file_path:%s", file_path);
      
    
      //创建通信套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        return -1;
    }
    //定义套接字数据结构
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8999);
    //大小端转换
    inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr.s_addr);
    //连接客户端
    int ret = connect(fd,(struct sockaddr *)&saddr,sizeof(saddr));
    if(ret == -1)
    {
        perror("connect");
        return -1;
    }
    int message_index = 0;
    while (1)
    {
        char buffer[1024];
        sprintf(buffer,"客户端发送消息:%d\n",message_index++);
        write(fd,buffer,strlen(buffer)+1);
        //清空缓冲区
        memset(buffer,0,sizeof(buffer));
        int len = read(fd,buffer,sizeof(buffer));
         if(len >0 ){
            printf("服务端说:%s\n",buffer);
        }
        else if (len == 0)
        {
           printf("服务端关闭连接\n");
           break;
        }
        else{
            perror("recv");
            break;
	}

	sleep(3);	
    }
    close(fd);
    return 0;
}
