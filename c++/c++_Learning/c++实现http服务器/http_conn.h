#ifndef __HTTP_CONNECT__
#define __HTTP_CONNECT__
// #include <sys/types.h> //open
// #include <sys/stat.h>  //open
// #include <fcntl.h>     //open
// #include <string.h>    //str
// #include <ctime>       //ctime
// #include <unistd.h>    //write
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <pthread.h>
// #include <arpa/inet.h>
// #include <sys/epoll.h>
// #include <sys/types.h>
// #include <sys/sendfile.h>
// #include <fcntl.h>
// #include <assert.h>
// #include <vector>
// #include <string>
// #include <cstdlib>

#include "./tools/tool.h"
#define BUFFER_SIZE 2048;

enum LOG_LEVEL
{
    ACCES = 0,
    WARNING,
    ERROR
};
typedef struct sock_info
{
    int cfd;
    sockaddr_in client_addr;
    sock_info()
    {
        cfd = -1;
        bzero(&client_addr, sizeof(client_addr));
    };
} sock_info;

void echo_log(const char *message, int level);

int init_socket(int port = 8999, const char *ip = INADDR_ANY);
void *handle_request(void *arg);

class server
{
private:
    int fd;
    int port;
    struct sockaddr_in saddr;

public:
    server(int port = 8999, const char *ip = INADDR_ANY);
    ~server();
    void server_sock_init(int port, const char *ip);
    int get_fd();
};
class log_
{
private:
    // FILE *file_ptr;
    char file_path[200];
    CFile *log_file;
    pthread_mutex_t mutex_log;
    
public:
    static const char *log_list[];

public:
    log_(const char *logfile_name = "log/log_file");
    bool log_write(const char *message, int level);
    ~log_();
};

class http_conn
{
public:
    int fd;
    struct sockaddr_in saddr;
    socklen_t addrlen = sizeof(struct  sockaddr);
private:
    std::string method;
    std::string uri;
    std::string path;
    std::string http_version;
    int cgi_excu =0;
    const int buffer_size = BUFFER_SIZE;
public:
    http_conn();
    ~http_conn();
    void handle_request();

public:
    void bad_request();
    void error_print(const char *mess);
    void exc_cgi();
    void send_header();
    void fourOfour_error();
    void send_server_file();
    void parse_header(const std::string &s, std::vector<std::string> &tokens, const char *delimiter = (char *)" ");
    int get_one_line(char * buffer,int size);
    void resolve_can_not();
    void resolve_get();
    void resovle_post();
};


#endif