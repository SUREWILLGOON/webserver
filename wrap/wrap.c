#include "wrap.h"
int Daemon(int nochdir, int noclose)
{
    int ret = daemon(nochdir, noclose);
    if (ret < 0)
    {
       error_die("Daemon error");
        Err_Out("Daemon error");
    }
    return ret;
}
//system function
int Setsid(void)
{
    int ret = setsid();
    if (ret < 0)
        Err_Out("Can not Set process at the first in the group");
    return ret;
}

int Dup(int oldfd)
{
    int fd = dup(oldfd);
    if (fd == -1)
    {
        error_die("Dup error");
        Err_Out("Dup error");
    }
    return fd;
}

int Dup2(int fd1, int fd2)
{
    int ret;
    if ((ret = dup2(fd1, fd2)) < 0)
    {
       error_die("Dup2 error");
        Err_Out("Dup 2 error");
    }
    return ret;
}

pid_t Fork(void)
{
    pid_t pid = fork();
    if (pid < 0)
    {
       error_die("Fork Error\n");
        Err_Out("Fork error");
    }
    return pid;
}

int Pipe(int fd[2])
{
    int ret = pipe(fd);
    if (ret == -1)
    {
       error_die("Pipe Error");
        Err_Out("Pipe Error");
    }
    return ret;
}

int Open(LPCSTR pathname, int flags, mode_t mode)
{
    char buf[MAX_PATH];
    int fd = open(pathname, flags, mode);
    if (fd < 0)
    {
        sprintf(buf, "open %s error", pathname);
        error_die(buf);
        Err_Out(buf);
    }
    return fd;
}

ssize_t Read(int fd, void *buf, size_t count)
{

    int ret = read(fd, buf, count);
    if (ret < 0)
    {
        error_die("Read error");
        Err_Out("Read error");
    }
    return ret;
}

ssize_t Write(int fd, const void *buf, size_t count)
{

    int ret = write(fd, buf, count);
    if (ret < 0)
    {
        error_die("Read error");
        Err_Out("Read error");
    }
    return ret;
}

int Close(int fd)
{
    int ret = close(fd);
    if (ret < 0)
    {
       error_die("Close error");
        Err_Out("Close error");
    }
    return ret;
}
//socket function
int Socket(int domain, int type, int protocol)
{

    int ret = socket(domain, type, protocol);
    if (ret < 0)
    {
        error_die("Socket error");
        Err_Out("Socket error");
    }
    return ret;
}
int Listen(int sockfd, int backlog)
{
    int ret = listen(sockfd, backlog);
    if (ret < 0)
    {
        error_die("Listen error");
        Err_Out("Listen error");
    }
    return ret;
}
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int ret = accept(sockfd, addr, addrlen);
    if (ret < 0)
    {
        error_die("Accept error");
        Err_Out("Accept error");
    }
    return ret;
}
int Bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen)
{

    int ret = bind(sockfd, my_addr, addrlen);
    if (ret < 0)
        ;
    {
        error_die("Bind error");
        Err_Out("Bind error");
    }
    return ret;
}
int Connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen)
{
    int ret = connect(sockfd, serv_addr, addrlen);
    if (ret < 0)
    {
        error_die("Connect error");
        Err_Out("Connect error");
    }
    return ret;
}

//dns function
void dnsError(LPCSTR strOut)
{
    fprintf(stderr, "%s: DNS error %d\n", strOut, h_errno);
    exit(0);
}

pHOSTTENT Gethostbyname(LPCSTR name)
{
    pHOSTTENT p = gethostbyname(name);
    if (p == NULL)
    {
        error_die("Gethostbyname error");
        dnsError("Gethostbyname error");
    }
    return p;
}
pHOSTTENT Gethostbyaddr(LPCSTR addr, int len, int type)
{
    pHOSTTENT p = gethostbyaddr(addr, len, type);
    if (p == NULL)
    {
       error_die("Gethostbyaddr error");
        dnsError("Gethostbyaddr error");
    }
    return p;
}
