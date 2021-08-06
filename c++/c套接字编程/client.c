#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

int main()
{
    //创建通信套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8999);
    inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("connet");
        return -1;
    }
    int number = 0;
    while (1)
    {
        char buff[1024];
        sprintf(buff,"hello,server----%d",number++);
        send(fd,buff,strlen(buff)+1,0);
        //使缓冲区为0
        memset(buff,0,sizeof(buff));
        int len = recv(fd,buff,sizeof(buff),0);
        if(len >0 ){
            printf("server_sent:%s\n",buff);
        }
        else if (len == 0)
        {
           printf("server close....\n");
           break;
        }
        else{
            perror("recv");
            break;
        }
        //让子线程睡眠,防止发送消息过快
        sleep(3);

    }
    close(fd);
    return 0;
}