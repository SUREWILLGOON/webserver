#include "parseHeader.h"
int GetFileType(LPSTR FileType, LPCSTR FileName)
{
    if (strstr(FileName, ".html"))
        strcpy(FileType, "text/html");
    else if (strstr(FileName, ".gif"))
        strcpy(FileType, "image/gif");
    else if (strstr(FileName, ".jpg"))
        strcpy(FileType, "image/jpeg");
    else if (strstr(FileName, ".png"))
        strcpy(FileType, "image/png");
    else if (strstr(FileName, ".mp3"))
        strcpy(FileType, "audio/mp3");
    else if (strstr(FileName, ".mp3"))
        strcpy(FileType, "video/mpeg4");
    else
        strcpy(FileType, "text/plain");
}
int GetExtName(char cSeparator,LPSTR extName, LPCSTR FileName)
{
    int n=strlen(FileName);
    int Pos=n-1;
    if(n>1)
    {
		while(Pos>0)
		{
			if(FileName[Pos]==cSeparator)
				break;
			Pos--;
		}
       for(;Pos<n;)
       *extName++=FileName[Pos++];
	   *extName='\0';	
    }
    return 0;
	
}
int GetFileTypeByFile(LPSTR typeBuf, LPCSTR strType, LPCSTR strPath)
{
    int ret = GetConfig(typeBuf, strType, CONFIG_FILE);
    return ret;
}
int IsPermittedIP(LPCSTR strIP)
{
    char HostList[256];
    int nPos = 0;
    char ConfigPath[256];
    GetConfigPath(ConfigPath);
    GetConfig(HostList, "UnPermitted", ConfigPath);
    char *delim = ";";
    char *p = NULL;

    int n = 0;
    p = strtok(HostList, delim);
    
    if(strcmp(strIP,p)==0)
    return -1;
    
    while ((p = strtok(NULL, delim)))
    {
       if(strcmp(strIP,p)==0)
       n++;
    }
    if(n>0)
    return -1;
    
    return 0;
}
int GetConfigPath(LPSTR strConfigPath)
{
    char currentPath[256];

    getcwd(currentPath, sizeof(currentPath));
    strcat(currentPath, "/");
    strcpy(strConfigPath, currentPath);
    strcat(strConfigPath, CONFIG_FILE);

    if (strlen(strConfigPath) == 0)
        return -1;
    return 0;
}
//date:5.5 modify
int GetRequestHeader(LPSTR RequestHeader,LPCSTR strRecv)
{
	if(strRecv==NULL)
		return -1;
	char *p=(char*)strRecv;
	while(*p!='\0'&&*p!='\r'&&*(p+1)!='\n')
		*RequestHeader++=*p++;
	*RequestHeader='\0';
	 return (strlen(RequestHeader));
}
int GetMethod(LPSTR Method,LPCSTR RequestHeader)
{
	if(RequestHeader==NULL)
		return -1;
	char *p=(char*)RequestHeader;
	while(*p!=' '&&p!='\0')
		*Method++=*p++;
	*Method='\0';
	 return (strlen(Method));

}
int GetRequestString(LPSTR Requeststring,LPCSTR RequestHeader )
{
	char *str1=(char*)strstr(RequestHeader," ");
	if(str1==NULL)
		return -1;
	str1++;
	while(*str1!=' '&&*str1!='\0')
		*Requeststring++=*str1++;
	*Requeststring='\0';

	 return (strlen(Requeststring));
}

int GetProtocolVersion(LPSTR ProtocolVersion,LPCSTR RequestHeader)
{
	char *str1=(char*)strstr(RequestHeader,"HTTP/");
	if(str1==NULL)
		return -1;

	while(*str1!='\r')
		*ProtocolVersion++=*str1++;
	*ProtocolVersion='\0';
     return (strlen(ProtocolVersion));
}
int GetRequestFile(LPSTR strRequestFile,LPCSTR Requeststring)
{
	char *str=(char*)Requeststring;
	if(str==NULL)
		return -1;
    char *str1=strstr(Requeststring,"\?");
    if(str1!=NULL)
    {
	while(*str!='\?')
    *strRequestFile++=*str++;
    }
    else
    {
    while(*str!='\0')
    *strRequestFile++=*str++;  
    }
    *strRequestFile='\0';
    return (strlen(strRequestFile));

}
int GetRequestParam(LPSTR strParam,LPCSTR Requeststring)
{
	char *str=(char*)strstr(Requeststring,"\?");
	if(str==NULL)
	 return -1;
	str++;
	while(*str!='\0')
	*strParam++=*str++;
	*strParam='\0';

	return (strlen(strParam));

}
int GetMessageHeader(LPSTR strValue,LPCSTR msgHeader,LPCSTR strData)
{
	if(strData==NULL)
		return -1;

	char tempContent[256];
	sprintf(tempContent,"\r\n%s ",msgHeader);
	size_t len=strlen(tempContent);
	char *str1=(char*)strstr(strData,tempContent);
	if(str1==NULL)
		return -1;

	char *p=&(*(str1+len));
	while(*p!='\r'&&*(p+1)!='\n')
		*strValue++=*p++;
	*strValue='\0';
	return (strlen(strValue));

}
int GetBoundary(LPSTR strBoundary,LPCSTR strRecv)
{
    char strContentType[256];
	GetMessageHeader(strContentType,"Content-Type:",strRecv);
    char *tempstr=" boundary=";
	size_t len=strlen(tempstr);
	char *str1=(char*)strstr(strContentType,tempstr);
	if(str1==NULL)
		return -1;

	char *p=&(*(str1+len));
	while(*p!='\0')
		*strBoundary++=*p++;
	*strBoundary='\0';
	return (strlen(strBoundary));
}
int GetPostData(LPSTR strData,int n,LPCSTR strRecv)
{
    char *tempstr="\r\n\r\n";
	size_t len=strlen(tempstr);
	char *str1=(char*)strstr(strRecv,tempstr);
	
    char *p=&(*(str1+len));
    int i=0;
    for(;i<n;i++)
     strData[i]=*p++;
     return n;
}
int GetSaveFileName(LPSTR strName,LPCSTR strData)
{
    char ContentDisposition[80];
    GetMessageHeader(ContentDisposition,"Content-Disposition:",strData);
    char *tempstr="filename=\"";
    int len=strlen(tempstr);
    char *str1=strstr(ContentDisposition,tempstr);
    if(str1==NULL)
    return -1;
    char *p=&(*(str1+len));
    while(*p!='\0'&&*p!='\"')
    *strName++=*p++;
    *strName='\0';
    return (strlen(strName)); 
}
int GetSaveData(LPCSTR strData,int n,LPCSTR strBoundary)
{
   char endBoundary[256];
   memset(endBoundary,0,sizeof(endBoundary));
   sprintf(endBoundary,"\r\n--%s--",strBoundary);
   int len1=strlen(endBoundary);

   char *tempstr="\r\n\r\n";

   int  len=strlen(tempstr);
   char *str1=strstr(strData,tempstr);
   char *p=&(*(str1+len));
   char *str2=(char*)search_string(endBoundary,strData,n);
   char FileName[256];
   GetSaveFileName(FileName,strData);

   char ConfigPath[256];
   GetConfigPath(ConfigPath);
   char savePath[256];
   memset(savePath,0,sizeof(savePath));
   GetConfig(savePath, "DownloadTemp", ConfigPath);
   strcat(savePath,"/");
   strcat(savePath,FileName);

   FILE *fp=fopen(savePath,"w+");
   if(fp==NULL)
   {
   char errStr[256];
   sprintf(errStr,"can not open file %s",FileName);
   Err_Out(errStr);
   return -1;
   }
  fwrite(p,(str2-p),1,fp);
  fclose(fp);
  return 0;
}
int ParseData(LPCSTR strData,int n,LPCSTR strBoundary)
{
    char Form_start_Delim[256];
    sprintf(Form_start_Delim,"--%s",strBoundary);
   

    char EndDelim[256];
    sprintf(EndDelim,"\r\n--%s--",strBoundary);

    char Form_end_Delim[256];
    sprintf(Form_end_Delim,"\r\n--%s",strBoundary);

    if(strlen(strData)==0)
    {
        printf("Recv:empty\n");
        return -1;
    }
    char *start=rang_search(Form_start_Delim,strData,&strData[n]);
    char *end=rang_search(EndDelim,strData,&strData[n]);
    while(start!=end)
    {
    
       char *fileStart=rang_search("\r\n\r\n",start+strlen(Form_start_Delim),&strData[n]);
       char *fileEnd=rang_search(Form_end_Delim,fileStart,&strData[n]);

       fileStart+=4;
       char fileName[256];
       int j=0;
       char tempstr[256]="filename=\"";
       char *filename_start=rang_search(tempstr,start,fileEnd);
       filename_start+=strlen(tempstr);
       while(*filename_start!='\"')
       fileName[j++]=*filename_start++;
       fileName[j]='\0';

       if(strlen(fileName)==0)
       {
        printf("empty filename:\n");
       return -1;
       }
       FILE *fp=NULL;
       fp=fopen(fileName,"w+");
    if(fp==NULL)
    {
       char errStr[256];
       sprintf(errStr,"can not open file %s",fileName);
       Err_Out(errStr);
       return -1;
    }
       fwrite(fileStart,(fileEnd-fileStart),1,fp);
       fclose(fp);
       start=fileEnd;
    }
    return 0;
}
int GetValueByString(LPSTR strValue,LPCSTR key_start,LPCSTR value_end,LPCSTR str,int n)
{
if((strValue&&key_start&&value_end&&str)==0)
return -1;
char *start=search_string(key_start,str,n);
char  *end=rang_search(value_end,start,&str[n]);
start+=strlen(key_start);
while(start!=end)
*strValue++=*start++;
*strValue='\0';
}
LPCSTR search_string(LPCSTR des, LPCSTR src, int n)
{
     if((des&&src)==0)
			return NULL;
	int len=strlen(des);

	for(int i=0;i<n-len+1;i++)
	{
		int k=0;
		for(int j=0;j<len;j++)
		{
			if(src[i+j]==des[j])
				k++;
		}
		if(k==len)
			return (&src[i]);
	}
	return NULL;
}
LPSTR rang_search(LPCSTR des,LPCSTR src_start,LPCSTR src_end)
{
	if((des&&src_start&&src_end)==0)
		return NULL;
	char *start=(char*)src_start;
	while(start<=src_end)
	{
		char *p=start;
		char *str=(char*)des;
		while(*str&&*p==*str)
		{
			p++;
			str++;
		}
		if(*str=='\0')
			return start;
		start++;
	}
	return NULL;
}