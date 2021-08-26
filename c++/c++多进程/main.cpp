#include <iostream>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <fcntl.h>
using namespace std;

int main()
{
    cout << "this is message from Pprocess" << endl;
    int fd[2];
    int ret = pipe(fd);
    if (ret == -1)
    {
        perror("pipe");
        exit(0);
    }

    pid_t pid;
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execl("cgi", "cgi_zlf", "arg1", NULL);
        perror("excelp");
    }
    else
    {
        close(fd[1]);
        char buffer[4096];
        while (1)
        {
            bzero(buffer, 4096);
            int len = read(fd[0], buffer, sizeof(buffer));
            if (len == 0)
            {
                break;
            }
            printf("message from son :---->%s", buffer);
        }
        close(fd[0]);
        wait(NULL);
        return 0;
    }
}