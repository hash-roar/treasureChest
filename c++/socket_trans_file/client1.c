#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 1024

int main(int argc, char *arg[])
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
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr);
    //连接客户端
    int ret = connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("connect");
        return -1;
    }
    int message_index = 0;
    //打开文件
    FILE *fp;
    //以二进制形式读写文件
    if ((fp = fopen(file_path, "rb")) == NULL)
    {
        perror("fopen");
        return -1;
    }
    char buffer[BUFFER_SIZE] = {0};
    int read_count = 0;
    while ((read_count = fread(buffer, 1, BUFFER_SIZE, fp)) > 0)
    {

        write(fd, buffer, read_count);

        int len = read(fd, buffer, sizeof(buffer));
        if (len > 0)
        {
            printf("服务端说:%s\n", buffer);
        }
        else if (len == 0)
        {
            printf("服务端关闭连接\n");
            break;
        }
        else
        {
            perror("recv");
            break;
        }
        //清空缓冲区
        memset(buffer, 0, sizeof(buffer));
        sleep(1);
    }
    fclose(fp);
    close(fd);
    return 0;
}
