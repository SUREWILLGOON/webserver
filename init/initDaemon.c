#include "initDaemon.h"
void init()
{
int ret=GetInitStyle(CONFIG_FILE);
if(ret)
init_as_daemon();
else
printf("can not find boot setting\n");
}
bool GetInitStyle(LPCSTR path)
{
LPCSTR key="DaemonBoot";
char value_buf[MAX_PATH];
GetConfig(value_buf,key,path);
if(strcasecmp(value_buf,"true")==0)
return true;
return false;
}
void init_as_daemon(void)
{
  if(signal(SIGCHLD,SIG_IGN)==SIG_ERR)
	  exit(1);
  int i;
  pid_t pid;
  struct sigaction sc;
  if(pid=Fork())
	  exit(0);
  chdir("/");
  for(i=0;i<getdtablesize();i++)
  {
   close(i);
   open("/dev/null",O_RDWR);
   dup(0);
   dup(0);
  }
  umask(0);
  return;
}

