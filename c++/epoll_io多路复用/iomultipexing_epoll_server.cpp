#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
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

    int epfd = epoll_create(1);
    if (epfd == -1)
    {
        /* code */ perror("epoll_create");
        exit(0);
    }
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);

    struct epoll_event events[1024];
    int size = sizeof(events) / sizeof(events[0]);
    while (1)
    {
        int num = epoll_wait(epfd, events, size, -1);
        printf("就绪数量:%d\n", num);
        for (int i = 0; i < num; i++)
        {
            int fd_i = events[i].data.fd;
            if (fd_i == fd)
            {
                struct sockaddr_in caddr;
                socklen_t addrlen = sizeof(caddr);
                int cfd = accept(fd, (struct sockaddr *)&caddr, &addrlen);
                if (cfd == -1)
                {
                    perror("accept");
                    return -1;
                }
                char ip[32];
                printf("clientIP: %s ---clientPORT:%d\n", inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ip, sizeof(ip)), ntohs(caddr.sin_port));
                event.events = EPOLLIN;
                event.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &event);
            }
            else
            {
                char buffer[1024];
                int len = recv(fd_i, buffer, sizeof(buffer), 0);
                if (len == -1)
                {
                    perror("receive");
                }
                else if (len > 0)
                {
                    printf("client sent----->%s\n", buffer);
                    bzero(buffer, sizeof(buffer));
                    sprintf(buffer, "this message form server");
                    write(fd_i, buffer, strlen(buffer) + 1);
                }
                else if (len == 0)
                {
                    printf("client clost connection\n");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd_i, NULL);
                    close(fd_i);
                    break;
                }
            }
        }
    }

    close(fd);
    return 0;
}
