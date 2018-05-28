#include "log.h"

static int GetMonth(pTM localTime)
{
char buf[8];
int i;
static char *months[12]={"Jan","Feb","Mar","Apr",\
	"May","Jun","Jul","Aug",\
	"Sept","Oct","Nov","Dec"};
	strftime(buf,127,"%b",localTime);
	for(i=0;i<12;++i)
	{
	if(!strcmp(buf,months[i]))
	return i+1;
	}
	return 0;
}
static int GetDate(void)
{

}
static int GetHour(void)
{

}
static int GetMin(void)
{

}
static int GetSecond(void)
{

}
LPSTR GetstrTime(void)
{

}
bool isChangeTime(void)
{

}
int Writelog(const char* buf)
{
FILE *logfp=NULL;
char path[256]="Record.log";
if(access(path,F_OK)==0)
logfp=fopen(path,"a+");
else
logfp=fopen(path,"w");
if(logfp==NULL)
{
fclose(logfp);
exit(0);
}
WriteTime(logfp);
fwrite(buf,strlen(buf),1,logfp);
fputs("\r\n",logfp);
fflush(logfp);
fclose(logfp);
}

int WriteTime(FILE *logfp)
{
	time_t timeval;
	char other[24];
	char year[8];
	char together[64];
	int month;

	(void)time(&timeval);
	struct tm *local=localtime(&timeval);

	strftime(year,7,"%Y",local);
	month=GetMonth(local);
	strftime(other,23,"%d %H:%M:%S",local);
	sprintf(together,"%s/%d/%s ",year,month,other);
	fwrite(together,strlen(together),1,logfp);
}

