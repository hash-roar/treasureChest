#include "http_conn.h"

http_conn::http_conn()
{
}

http_conn::~http_conn()
{
}

int http_conn::get_one_line(char *buffer, int size)
{
    int i = 0;
    char c = '\0';
    int n;

    while ((i < size - 1) && (c != '\n'))
    {
        //recv()包含于<sys/socket.h>,参读《TLPI》P1259,
        //读一个字节的数据存放在 c 中
        n = recv(fd, &c, 1, 0);
        /* DEBUG printf("%02X\n", c); */
        if (n > 0)
        {
            if (c == '\r')
            {
                //
                n = recv(fd, &c, 1, MSG_PEEK);
                /* DEBUG printf("%02X\n", c); */
                if ((n > 0) && (c == '\n'))
                    recv(fd, &c, 1, 0);
                else
                    c = '\n';
            }
            buffer[i] = c;
            i++;
        }
        else
            c = '\n';
    }
    buffer[i] = '\0';

    return (i);
}

void http_conn::handle_request()
{
    char buffer[buffer_size];
    bzero(buffer, buffer_size);
    get_one_line(buffer, buffer_size);
    std::vector<std::string> header_array;
    std::string header_line1 = buffer;
    parse_header(header_line1, header_array);
    method = header_array[0];
    uri = header_array[1];
    http_version = header_array[2];
    http_version.resize(8);
    if (method != "GET" && method != "POST")
        resolve_can_not();
    if (method == "GET")
        resolve_get();
    if (method == "POST")
        resovle_post();
}
void http_conn::parse_header(const std::string &s, std::vector<std::string> &tokens, const char *delimiter)
{
    tokens.clear();
    char buffer[s.size() + 1];
    std::copy(s.begin(), s.end(), buffer);
    char *p = strtok(buffer, delimiter);
    do
    {
        tokens.push_back(p);
    } while (p = strtok(NULL, delimiter));
    return;
}
void http_conn::resolve_can_not()
{

}
void http_conn::resolve_get()
{
    std::string url_file_temp;
    std::string query_string;
    auto dilimiter_pos = uri.find("?");
    if (dilimiter_pos != string::npos)
    {
        cgi_excu = 1;
        url_file_temp = uri.substr(0, dilimiter_pos);
        query_string = uri.substr(dilimiter_pos + 1, (uri.size() - dilimiter_pos - 1));
    }
    else
    {
        url_file_temp = uri;
    }

    std::string url_file;
    char end = *(url_file_temp.rbegin());
    if (!strcasecmp(&end, "/"))
    {
        url_file_temp += "index.html";
    }
    std::cout<<url_file_temp<<std::endl;
    
}
void http_conn::resovle_post()
{
    
}

//--------------------------------------------->

server::server(int port, const char *ip)
{
    this->server_sock_init(port, ip);
    this->port = port;
}
server::~server()
{
    close(fd);
}
void server::server_sock_init(int port, const char *ip)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1)
    {
        perror("socket");
        echo_log("create socket error", ERROR);
        exit(-1);
    }

    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("bind");
        echo_log("bind socket error", ERROR);
        exit(-1);
    }
    ret = listen(fd, 100);
    if (ret == -1)
    {
        perror("listen");
        echo_log("listen error", ERROR);
        exit(-1);
    }
    return;
}
int server::get_fd()
{
    return fd;
}

//--------------------------------------------->
const char *log_::log_list[] = {(char *)"Access", (char *)"Warning", (char *)"Error"};

log_::log_(const char *logfile_name)
{
    pthread_mutex_init(&mutex_log, NULL);
    bzero(file_path, sizeof(file_path));
    strncpy(file_path, logfile_name, strlen(logfile_name) + 1);
    log_file = new CFile();
    if (!(log_file->Open(logfile_name, "a+", false)))
    {
        printf("open log file faild!");
        exit(-1);
    }
}

bool log_::log_write(const char *message, int level)
{
    char buffer[512];
    bzero(buffer, sizeof(buffer));
    strncpy(buffer, log_list[level], sizeof(log_list[level]));
    strncat(buffer, ":  ", strlen(":  "));
    strncat(buffer, message, strlen(message));
    strncat(buffer, " ,时间:  ", strlen("  ,时间:  "));
    time_t now = time(0);
    char *time_now = ctime(&now);
    strcat(buffer, time_now);
    strcat(buffer, "\r\n");
    pthread_mutex_lock(&mutex_log);
    log_file->Fwrite(buffer, strlen(buffer) + 1);
    pthread_mutex_unlock(&mutex_log);
    return true;
}

log_::~log_()
{
    delete log_file;
}
// GET / HTTP/1.1
// Host: 192.168.0.23:47310
// Connection: keep-alive
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*; q = 0.8
// Accept - Encoding: gzip, deflate, sdch
// Accept - Language : zh - CN, zh; q = 0.8
// Cookie: __guid = 179317988.1576506943281708800.1510107225903.8862; monitor_count = 5
//

// POST / color1.cgi HTTP / 1.1
// Host: 192.168.0.23 : 47310
// Connection : keep - alive
// Content - Length : 10
// Cache - Control : max - age = 0
// Origin : http ://192.168.0.23:40786
// Upgrade - Insecure - Requests : 1
// User - Agent : Mozilla / 5.0 (Windows NT 6.1; WOW64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 55.0.2883.87 Safari / 537.36
// Content - Type : application / x - www - form - urlencoded
// Accept : text / html, application / xhtml + xml, application / xml; q = 0.9, image / webp, */*;q=0.8
// Referer: http://192.168.0.23:47310/
// Accept-Encoding: gzip, deflate
// Accept-Language: zh-CN,zh;q=0.8
// Cookie: __guid=179317988.1576506943281708800.1510107225903.8862; monitor_count=281
// Form Data
// color=gray

const int buffer_size = 1024 * 20;
struct http_info
{
    std::string method;
    std::string host;
    std::string url;
    std::string *query_string;
    std::string http_version;
    int content_length;
};

void split(const std::string &s, std::vector<std::string> &tokens, const char *delimiter = (char *)" ")
{
    tokens.clear();
    char buffer[s.size() + 1];
    std::copy(s.begin(), s.end(), buffer);
    char *p = strtok(buffer, delimiter);
    do
    {
        tokens.push_back(p);
    } while (p = strtok(NULL, delimiter));
    return;
}

void echo_log(const char *message, int level)
{
    char *log_list[] = {(char *)"Access", (char *)"Warning", (char *)"Error"};
    char *log_path = (char *)"log/log_file";
    int fd = open(log_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
    char buffer[512];
    bzero(buffer, sizeof(buffer));
    strncpy(buffer, log_list[level], sizeof(log_list[level]));
    strncat(buffer, ":  ", strlen(":  "));
    strncat(buffer, message, strlen(message));
    strncat(buffer, " ,时间:  ", strlen("  ,时间:  "));
    time_t now = time(0);
    char *time_now = ctime(&now);
    strcat(buffer, time_now);
    strcat(buffer, "\r\n");
    write(fd, buffer, strlen(buffer) + 1);
    close(fd);
}

int init_socket(int port, const char *ip)
{
    //创建监听套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1)
    {
        perror("socket");
        echo_log("create socket error", ERROR);
        return -1;
    }

    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("bind");
        echo_log("bind socket error", ERROR);
        return -1;
    }
    ret = listen(fd, 100);
    if (ret == -1)
    {
        perror("listen");
        echo_log("listen error", ERROR);
        return -1;
    }
    return fd;
}

void parse_headers(std::vector<std::string> &token, struct http_info *info)
{
    std::vector<std::string> temp;
    //method
    temp.clear();
    split(token[0], temp);
    info->method = temp[0];
    info->url = temp[1];
    info->http_version = temp[2];
    //host
    temp.clear();
    split(token[2], temp);
    info->host = temp[1];
    //content length
    temp.clear();
    split(token[3], temp);
    size_t num_po = temp[1].size();
    info->content_length = std::stoi(temp[1], &num_po, 10);
}
void *handle_request(void *arg)
{
    sock_info *info = (sock_info *)arg;
    int cfd = info->cfd;
    char buffer[buffer_size];
    int num = recv(cfd, buffer, buffer_size, 0);
    std::vector<std::string> tokens;
    std::string s = buffer;
    split(s, tokens, "\r\n");
    struct http_info info_;
    bzero(&info, sizeof(info_));
    parse_headers(tokens, &info_);
    while (1)
    {
        bzero(buffer, buffer_size);
        int num = recv(cfd, buffer, buffer_size, 0);
        if (num > 0)
        {
        }
        if (num == 0)
        {
            break;
        }
        else
        {
            echo_log("read error", ERROR);
            break;
        }
    }

    int a = 10;
    pthread_exit(NULL);
}
