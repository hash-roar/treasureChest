#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 1024
#define SOCKINFO_SIZE 256
typedef struct sock_info
{
    struct sockaddr_in addr;
    int cfd;
} sock_info;
//避免堆空间的重复释放,定义结构体数组
sock_info sock_infos[SOCKINFO_SIZE];

void *working(void *arg)
{
    sock_info *pinfo = (sock_info *)arg;
    int cfd = pinfo->cfd;
    //定义ip
    char ip[32];
    //接受文件名
    char file_name[50];
    read(cfd, file_name, sizeof(file_name));
    //打开文件
    FILE *fp = fopen(file_name, "wb");
    if (fp == NULL)
    {
        perror("fopen");
        return NULL;
    }
    //打印连接客户端信息inet_ntop将ip地址转化为小端,
    printf("客户端ip:%s,客户端端口:%d\n", inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, ip, sizeof(ip)), ntohs(pinfo->addr.sin_port));
    while (1)
    {
        char buffer[BUFFER_SIZE];
        //接受客户端数据
        int len = read(cfd, buffer, sizeof(buffer));
        if (len > 0)
        {
            printf("客户端说送%dB数据", len);
            fwrite(buffer, len, 1, fp);
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "服务端收到%dB数据", len);
            write(cfd, buffer, strlen(buffer) + 1);
        }
        else if (len == 0)
        {
            printf("客户端已关闭连接\n");
            break;
        }
        else
        {
            perror("recv");
            break;
        }
    }
    pinfo->cfd = -1;
    fclose(fp);
    close(cfd);
    return NULL;
}

int main(int argc, char *arg[])
{
    char *file_path = arg[1];
    // try open files
    int fd = socket(AF_INET, SOCK_STREAM, 0); //使用ipv4,流式传输协议,使用默认协议
    if (fd == -1)
    {
        perror("socket");
        return -1;
    };
    //转换本地字节序到网络字节序
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8999);                                 //端口
    saddr.sin_addr.s_addr = INADDR_ANY;                           //接收任意网络数据
    int ret = bind(fd, (struct sockaddr *)&saddr, sizeof(saddr)); //绑定端口和地址到套接字
    if (ret == -1)
    {
        perror("bind");
        return -1;
    }
    ret = listen(fd, 100); //开启监听
    if (ret == -1)
    {
        perror("listen");
        return -1;
    }
    //开始连接
    //建立通信套接字
    int addrlen = sizeof(struct sockaddr_in);
    for (int i = 0; i < SOCKINFO_SIZE; i++)
    {
        bzero(&sock_infos[i], sizeof(sock_infos[0]));
        sock_infos->cfd = -1;
    }

    //循环连接
    while (1)
    {
        sock_info *pinfo;
        // 遍历寻找未使用的结构体
        for (int i = 0; i < SOCKINFO_SIZE; i++)
        {
            if (sock_infos[i].cfd == -1)
            {
                pinfo = &sock_infos[i];
                break;
            }
            if (i == SOCKINFO_SIZE - 1)
            {
                //结构体用完了
                break;
            }
        }

        // caddr 记录连接地址信息 ,addrlen指明addr指向内存大小
        int cfd = accept(fd, (struct sockaddr *)&pinfo->addr, &addrlen);
        pinfo->cfd = cfd;
        if (cfd == -1)
        {
            perror("accept");
            break;
        }
        //创建子线程
        pthread_t tid;
        pthread_create(&tid, NULL, working, pinfo);
        pthread_detach(tid);
    }
    close(fd);
    return 0;
}
