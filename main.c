#include "common/common.h"
#include "wrap/wrap.h"
#include "init/initDaemon.h"
#include "getconfig/getconfig.h"
#include "log/log.h"
#include "connect/connect.h"
#include "parse/parseHeader.h"
#include "respone/respone.h"
#include "servertypes.h"
#include "log/log.h"
//#define 
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

int startup(u_short *port)
{
    int httpd = 0;
    int on = 1;
    struct sockaddr_in name;

    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        error_die("socket");
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
    {
        error_die("setsockopt failed");
    }
    if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
        error_die("bind");
    if (*port == 0) 
    {
        socklen_t namelen = sizeof(name);
        if (getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1)
            error_die("getsockname");
        *port = ntohs(name.sin_port);
    }
    if (listen(httpd, 5) < 0)
        error_die("listen");
    return (httpd);
}

int main(void)
{
    if (access(CONFIG_FILE, F_OK) != 0)
    {
        error_die("Config file not exist!");
        Err_Out("error,Config file not exist!");
    }

   //init();
   // daemon(0,0);
    pthread_t newthread;
    int server_sock = -1;
    pid_t pid;
    char strPort[20];
    char strConfig[MAX_BUF];
    GetConfigPath(strConfig);
    GetConfig(strPort,"port",strConfig);
    u_short port = atoi(strPort);
    int client_sock = -1;
    struct sockaddr_in client_name;
    socklen_t client_name_len = sizeof(client_name);
    server_sock = startup(&port);


    while (1)
    {
        client_sock = accept(server_sock,
                             (struct sockaddr *)&client_name,
                             &client_name_len);
         struct timeval timeout={0,300000};//0.3s
    int ret=setsockopt(client_sock,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout));
        pid = fork();
        if (pid)
            close(client_sock);
            #define MB_BYTE (1024*1024*2)
        else if (pid == 0)
        {
            char buf[MB_BYTE];
            memset(buf, 0, sizeof(buf));
            int nRead=0;
            int n=0; 
            while((n=recv(client_sock, buf+nRead, sizeof(buf), 0))>0)
            nRead+=n;

              if(nRead>0)
              {
                  //for(int i=0;i<ret;i++)
                  //printf("%c",buf[i]);
                sendRespone(client_sock, buf);
              }
               
            close(client_sock);
            exit(0);
        }
    }
    int status;
    waitpid(pid, &status, 0);
    close(server_sock);
    return 0;
}
