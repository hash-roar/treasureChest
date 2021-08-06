#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

int main()
{
    //创建监听套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8999);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("bind");
        return -1;
    }

    ret = listen(fd, 100);
    if (ret == -1)
    {
        perror("listen");
        return -1;
    }
    struct sockaddr_in caddr;
    int addrlen = sizeof(caddr);
    int cfd = accept(fd,(struct sockaddr *)&caddr,&addrlen);
    if(cfd ==-1){
        perror("accept");
        return -1;
    }
    char ip[32];
    printf("clientIP: %s ---clientPORT:%d\n",inet_ntop(AF_INET,&caddr.sin_addr.s_addr,ip,sizeof(ip)),ntohs(caddr.sin_port));
    //通信
    while (1)
    {
        char buff[1024];
        int len = recv(cfd,buff,sizeof(buff),0);
        if(len >0 ){
            printf("clent_sent:%s\n",buff);
            send(cfd,buff,len,0);
        }
        else if (len == 0)
        {
           printf("client close....\n");
           break;
        }
        else{
            perror("recv");
            break;
        }
    }
    close(fd);
    close(cfd);
    return 0;
}