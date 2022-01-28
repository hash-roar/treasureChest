#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/stat.h>

typedef struct fdInfo
{
    int fd;
    int *maxfd;
    fd_set *readset;
} fdInfo;
void *acception(void *arg)
{
    fdInfo *info = (fdInfo *)arg;
    int cfd = accept(info->fd, NULL, NULL);
    FD_SET(cfd, info->readset);
    *info->maxfd = cfd > *info->maxfd ? cfd : *info->maxfd;
    free(info);
    return NULL;
}

void *communicatio(void *arg)
{
    fdInfo *info = (fdInfo *)arg;
    char buff[1024];
    int len = recv(info->fd, buff, sizeof(buff), 0);
    if (len > 0)
    {
        printf("clent_sent:%s\n", buff);
        send(info->fd, buff, len, 0);
    }
    else if (len == 0)
    {
        printf("client close....\n");
        FD_CLR(info->fd, info->readset);
        close(info->fd);
    }
    else
    {
        perror("recv");
    }
    free(info);
}
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
    //初始化读集合
    fd_set readset;

    FD_ZERO(&readset);
    FD_SET(fd, &readset);
    int maxfd = fd;
    struct sockaddr_in caddr;
    int addrlen = sizeof(caddr);
    while (1)
    {
        fd_set temp = readset;
        int ret = select(maxfd + 1, &temp, NULL, NULL, NULL);
        if (FD_ISSET(fd, &temp))
        {
            int cfd = accept(fd, NULL, NULL);
            FD_SET(cfd, &readset);
            maxfd = cfd > maxfd ? cfd : maxfd;
            //
            pthread_t tid;
            fdInfo *info = (fdInfo *)malloc(sizeof(fdInfo));
            info->fd = fd;
            info->maxfd = &maxfd;
            info->readset = &readset;
            pthread_create(&tid, NULL, acception, info);
            pthread_detach(tid);
        }
        for (int i = 0; i < maxfd; i++)
        {
            if (i != fd && FD_ISSET(i, &temp))
            {
                pthread_t tid;
                fdInfo *info = (fdInfo *)malloc(sizeof(fdInfo));
                info->fd = i;
                info->maxfd = &maxfd;
                info->readset = &readset;
                pthread_create(&tid, NULL, communicatio, info);
                pthread_detach(tid);
            }
        }
    }

    close(fd);

    return 0;
}