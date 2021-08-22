#include "./http_conn.h"
const int INFO_SIZE = 512;

sock_info sock_infos[INFO_SIZE];

int main()
{
    //创建监听套接字
    log_ log_obj;
    server server_obj;
    while (1)
    {
        http_conn http_obj;
        http_obj.fd = accept(server_obj.get_fd(), (struct sockaddr *)&http_obj.saddr, &http_obj.addrlen);
        if (http_obj.fd == -1)
        {
            perror("accept");
            log_obj.log_write("accept error",ERROR);
            exit(-1);
        }
        http_obj.handle_request();
        char ip[64];
        char client_info[256];
        sprintf(client_info, "IP: %s<---->端口:%d\n", inet_ntop(AF_INET, &http_obj.saddr.sin_addr.s_addr, ip, sizeof(ip)), ntohs(http_obj.saddr.sin_port));
        log_obj.log_write(client_info,ACCES);
        // pthread_t tid;
        // pthread_create(&tid, NULL, handle_request, &sock_infos[sock_info_index]);
        // pthread_join(tid,NULL);
    }
    return 0;
}
