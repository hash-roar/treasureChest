#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
void *working(void *arg);

struct SockInfo
{
    struct sockaddr_in addr;
    int fd;
};

struct SockInfo infos[128];

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
    int addrlen = sizeof(struct sockaddr_in);
    int max = sizeof(infos) / sizeof(infos[0]);
    for (int i = 0; i < max; i++)
    {
        bzero(&infos[i], sizeof(infos[i]));
        infos[i].fd = -1;
    }

    while (1)
    {
        struct SockInfo *pinfo;
        for (int i = 0; i < max; i++)
        {
            if (infos[i].fd == -1)
            {
                pinfo = &infos[i];
                break;
            }
        }

        int cfd = accept(fd, (struct sockaddr *)&pinfo->addr, &addrlen);
        pinfo->fd = cfd;
        if (cfd == -1)
        {
            perror("accept");
            continue;
        }
        //get son thread
        pthread_t tid;
        pthread_create(&tid, NULL, working, pinfo);
        //
        pthread_detach(tid);
    }

    close(fd);
    return 0;
}
void *working(void *arg)
{
    struct SockInfo *pinfo = (struct SockInfo *)arg;
    char ip[32];
    printf("clientIP: %s ---clientPORT:%d\n", inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, ip, sizeof(ip)),
           ntohs(pinfo->addr.sin_port));
    //通信
    while (1)
    {
        char buff[1024];
        int len = recv(pinfo->fd, buff, sizeof(buff), 0);
        if (len > 0)
        {
            printf("clent_sent:%s\n", buff);
            send(pinfo->fd, buff, len, 0);
        }
        else if (len == 0)
        {
            printf("client close....\n");
            break;
        }
        else
        {
            perror("recv");
            break;
        }
    }
    close(pinfo->fd);
    pinfo->fd = -1;

    return NULL;
}