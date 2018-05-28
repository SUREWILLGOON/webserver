#include "connect.h"
int initSocket(u_short *port)
{
    struct sockaddr_in name;
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    int httpd = 0;
    httpd = Socket(PF_INET, SOCK_STREAM, 0);
    int on = 1;
    setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    Bind(httpd, (struct sockaddr *)&name, sizeof(name));
    if (*port == 0)
    {
        socklen_t namelen = sizeof(name);
        if (getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1)
            Err_Out("getsockname");
        *port = ntohs(name.sin_port);
    }
    Listen(httpd, 5);
    return(httpd);	
}
