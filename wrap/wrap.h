/*****************************
 *by SURE_GOGOGO
 *QQ:851497767
 *Time:2017/3/28
 *Note:some wrap function Add 
 * ***************************/
#ifndef ___WRAP_HEADER___
#define ___WRAP_HEADER___
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <syslog.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../servertypes.h"
#include "../common/common.h"

//#define pid_t PID
typedef struct hostent * pHOSTTENT;

//Init as daemon
int Daemon(int nochdir, int noclose);
//system functions
pid_t Fork(void);
int Setsid(void);
int Open(LPCSTR pathname,int flags,mode_t mode);
int Close(int fd);
ssize_t Read(int fd,void *buf,size_t count);
ssize_t Write(int fd,const void *buf,size_t count);
int Pipe(int fd[2]);
int Dup(int fd);
int Dup2(int fd1,int fd2);
void SendFile();
void RecvFile();
//Socket functions
int Socket(int domain,int type,int protocol);
int Listen(int sockfd,int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int Bind( int sockfd , const struct sockaddr * my_addr, socklen_t addrlen);
int Connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
//dns settingfunction
void dnsError(LPCSTR strOut);
pHOSTTENT Gethostbyname(LPCSTR name);
pHOSTTENT Gethostbyaddr(LPCSTR addr,int len,int type);
#endif

