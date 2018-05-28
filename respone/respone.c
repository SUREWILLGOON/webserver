#include "respone.h"

void SendHomePage(int client)
{
    char strFile[256];
    char ConfigPath[256];
    GetConfigPath(ConfigPath);
    GetConfig(strFile, "Homepage", ConfigPath);

    char FileType[20];
    int ret = GetFileTypeByFile(FileType, ".html", strFile);

    char FilePath[256];
    char RootPath[256];
    GetWebRoot(RootPath);
    strcpy(FilePath, RootPath);
    strcat(FilePath, "/");
    strcat(FilePath, strFile);

    if (ret == -1)
        sendAnyFile(client, "text/html", FilePath);
    else
        sendAnyFile(client, FileType, FilePath);
}
void sendRespone(int client, LPCSTR strRecv)
{

    char RequesetHeader[10240];
    GetRequestHeader(RequesetHeader, strRecv);
    char strMethod[20];
    GetMethod(strMethod, RequesetHeader);
    char RequestString[10240];
    GetRequestString(RequestString, RequesetHeader);
   
    char strFile[256];
    GetRequestFile(strFile, RequestString);
    char FilePath[256];
     
    GetHttpFilePath(FilePath, strFile);
    if (strcasecmp(strMethod, "GET") == 0)
    {
        if ((strlen(strFile)<1))
        {
            SendHomePage(client);
            return;
        }
        char strParam[256];
        if (GetRequestParam(strParam, RequestString) > 0)
        {
            sendGetPage(client, strParam);
            return;
        }

        FILEINFO file_inf;
        getFileInfo(FilePath, &file_inf);
        if (file_inf.isExist == -1)
        {
            sendNotFound(client);
            return;
        }

        if (file_inf.isExist == 0 && file_inf.type == 1)
        {
            ShowDirectory(client, FilePath);
            return;
        }

        if (file_inf.isExist == 0 && file_inf.type == 2)
        {
            char FileType[256];
            char extName[20];
            GetExtName('.', extName, strFile);
            int ret = GetFileTypeByFile(FileType, extName, strFile);
           
            if(strcasecmp(extName,".cgi")==0)
            {
            execute_cgi(client, FilePath, strParam);
            return;
            }
            if(ret == -1)
                sendAnyFile(client, "text/html", FilePath);
            else
                sendAnyFile(client, FileType, FilePath);
                return;
        }

    }

    if (strcasecmp(strMethod, "POST") == 0)
    {
        char strContentLength[10];
        char strContentType[256];
        char strType[128];
        GetMessageHeader(strContentType, "Content-Type:", strRecv);
        char *str=strstr(strContentType,"; ");
        if(str!=NULL)
        *str='\0';
        GetMessageHeader(strContentLength, "Content-Length:", strRecv);
        int n = atoi(strContentLength);
        char strPost[MB_BYTE];
        if(strcmp(strContentType,"application/x-www-form-urlencoded")==0)
        {
            char *str=(char*)strstr(strRecv,"\r\n\r\n");
            str+=4;
            int i;
            for( i=0;i<n;i++)
            strPost[i]=*str++;
            strPost[i]='\0';
            sendPostPage(client, strPost);
            return;
        }
        if(strcmp(strContentType,"multipart/form-data")==0)
        {
            if(GetPostData(strPost, n, strRecv)==0)
            {
             sendBadRequest(client);
             return;
            }
            char strBoundary[256];
            GetBoundary(strBoundary, strRecv);
            if(ParseData(strPost,n, strBoundary)==-1)
            {
                sendBadRequest(client);
                return;
            }
            execute_cgi(client, FilePath, strPost);
            return;
        }
       sendBadRequest(client);
        return;
    }
    sendUnimplemented(client);
}
void sendResponeHeader(int client)
{
    char buf[1024];
    strcpy(buf, RESOPONE_OK);
    send(client, buf, strlen(buf), 0);
    strcpy(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
}
void sendTextFile(int client, LPCSTR FileName)
{
    sendTextHeader(client);
    sendFile(client, FileName);
}
void sendBinaryFile(int client, LPCSTR FileName)
{
    sendBinaryHeader(client, FileName);
    sendFile(client, FileName);
}
void sendBinaryHeader(int client, LPCSTR FileName)
{
    char buf[1024];
    sendResponeHeader(client);
    char TypeBuf[256];
    GetFileType(TypeBuf, FileName);
    sprintf(buf, "Content-Type: %s\r\n", TypeBuf);
    send(client, buf, strlen(buf), 0);
    strcpy(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
}
void sendTextHeader(int client)
{
    char buf[1024];
    sendResponeHeader(client);
    sprintf(buf, WEB_TEXT);
    send(client, buf, strlen(buf), 0);
    strcpy(buf, "Content-Encoding:identity\r\n");
    send(client, buf, strlen(buf), 0);
    strcpy(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
}

void sendAnyFileHeader(int client, LPCSTR FileType, LPCSTR FileName)
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    sendResponeHeader(client);
    int size = GetFileLength(FileName);
    sprintf(buf, "Content-length: %d\r\n", size);
    sprintf(buf, "%sContent-Type: %s\r\n", buf, FileType);
    sprintf(buf, "%sContent-Range: bytes 0-%d/%d\r\n", buf, size, (size + 1));
    sprintf(buf, "%s\r\n", buf);
    send(client, buf, strlen(buf), 0);
}
void sendAnyFile(int client, LPCSTR FileType, LPCSTR FileName)
{
    sendAnyFileHeader(client, FileType, FileName);
    sendFile(client, FileName);
}
void sendFile(int client, LPCSTR FileName)
{
    int filed = open(FileName, O_RDONLY);
    struct stat stat_buf;
    fstat(filed, &stat_buf);
    sendfile(client, filed, NULL, stat_buf.st_size);
    close(filed);
}

void sendNotFound(int client)
{
    char buf[1024];
    sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<h1>404 Not Found</h1>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<P>can not acess the resource</P>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<P>because the resource is unavailable or nonexistent.</P>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

void sendPostPage(int client, LPCSTR strParam)
{
    char buf[1024];
    sprintf(buf, RESOPONE_OK);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Post Page</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);

    sprintf(buf, "<BODY><P>%s</p>\r\n", strParam);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

void sendGetPage(int client, LPCSTR strParam)
{
    char buf[1024];
    sprintf(buf, RESOPONE_OK);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Get Page</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>%s</p>\r\n", strParam);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}
void sendBadRequest(int client)
{
    char buf[1024];
    sprintf(buf, RESOPONE_OK);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Can not accesss</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><h1>404 Bad Request,please check your request string!</h1>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}
void sendUnimplemented(int client)
{
    char buf[1024];
    sprintf(buf, UNKNOW_METHOD);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, WEB_TEXT);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sendFile(client, "notfound.html");
}
void sendCannotAccess(client)
{
    char buf[1024];
    sprintf(buf, RESOPONE_OK);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Can not accesss</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>You can not access  the web server!</p>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}
void ShowDirectory(int client, LPCSTR fileName)
{
    DIR *dp;
    struct dirent *dirp;

    if ((dp = opendir(fileName)) == NULL)
    {
        char errstr[256];
        sprintf(errstr, "can not open the file %s", fileName);
        sendNotFound(client);
        Writelog(errstr);
        return;
    }

    char buf[1024];
    sprintf(buf, RESOPONE_OK);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>show dir</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY>");
    send(client, buf, strlen(buf), 0);
    char FilePath[256];
    while ((dirp = readdir(dp)) != NULL)
    {
        struct stat filestat;
        sprintf(FilePath, "%s/%s", fileName, dirp->d_name);

        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        int ret = stat(FilePath, &filestat);
        sprintf(buf, "<li>\r\n");
        send(client, buf, strlen(buf), 0);

        char RootPath[256];
        GetWebRoot(RootPath);
        strcat(RootPath, "/");
        if (strcmp(fileName, RootPath) > 0)
        {
            char ExtDir[20];
            GetExtName('/', ExtDir, fileName);
            if(strstr(dirp->d_name,"/"))
            sprintf(buf, "<a href=\"%s%s\">", ExtDir, dirp->d_name);
            else
            sprintf(buf, "<a href=\"%s/%s\">", ExtDir, dirp->d_name);
            send(client, buf, strlen(buf), 0);
        }
        else
        {
            sprintf(buf, "<a href=\"/%s\">", dirp->d_name);
            send(client, buf, strlen(buf), 0);
        }
        if (ret != -1 && S_ISDIR(filestat.st_mode))
        {
            sprintf(buf, "<img src=\"dir.png\" />%s\r\n", dirp->d_name);
            send(client, buf, strlen(buf), 0);
        }
        if (ret != -1 && S_ISREG(filestat.st_mode))
        {
            sprintf(buf, "<img src=\"file.png\" />%s\r\n", dirp->d_name);
            send(client, buf, strlen(buf), 0);
        }
        sprintf(buf, "</li>\r\n");
        send(client, buf, strlen(buf), 0);
    }
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
    closedir(dp);
}
void execute_cgi(int client, LPCSTR fileName, LPCSTR query_string)
{
    char query_env[256];
    sprintf(query_env, "QUERY_STRING=%s", query_string);
    putenv(query_env);
    pid_t pid;
    int status;
    int cgi_out[2];
    pipe(cgi_out);
    pid = fork();
    if (pid == 0)
    {
        close(cgi_out[0]);
        dup2(cgi_out[1], STDOUT_FILENO);
        execl(fileName, (char *)0);
        exit(0);
    }
    else
    {
        close(cgi_out[1]);
        char buf[256];
        char strRespone[256];
        char c;
        int i = 0;
        while (read(cgi_out[0], &c, 1))
            buf[i++] = c;
        buf[i] = '\0';
        if (strlen(buf) == 0)
            canNotExecv_cgi(client);
        else
            sendRespone_cgi(client, buf);
    }
    waitpid(pid, &status, 0);
}
void sendRespone_cgi(int client, LPCSTR strRespone)
{
    char buf[1024];
    sprintf(buf, RESOPONE_OK);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "%s", strRespone);
    send(client, buf, strlen(buf), 0);
}
void getFileInfo(LPCSTR strPath, FILEINFO *file_inf)
{
    struct stat file_stat;
    if (stat(strPath, &file_stat) < 0)
    {
        file_inf->isExist = -1;
        strcpy(file_inf->path, "");
        file_inf->type = 0;
    }

    if (S_ISDIR(file_stat.st_mode))
    {
        file_inf->isExist = 0;
        strcpy(file_inf->path, strPath);
        file_inf->type = 1;
    }
    if (S_ISREG(file_stat.st_mode))
    {
        file_inf->isExist = 0;
        strcpy(file_inf->path, strPath);
        file_inf->type = 2;
    }
}
void GetWebRoot(LPSTR path)
{
    char currentPath[256];
    getcwd(currentPath, sizeof(currentPath));
    strcat(currentPath, "/");

    char ConfigPath[256];
    GetConfigPath(ConfigPath);
    char Path[256];
    GetConfig(Path, "wwwroot", ConfigPath);
    char FilePath[256];
    strcpy(FilePath, currentPath);
    strcat(FilePath, Path);
    strcpy(path, FilePath);
}
void GetHttpFilePath(LPSTR filepath, LPCSTR filename)
{
    char webRoot[256];
    GetWebRoot(webRoot);
    strcat(webRoot, filename);
    strcpy(filepath, webRoot);
}
void canNotExecv_cgi(int client)
{
    char buf[1024];
    sprintf(buf, RESOPONE_OK);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Can not execute</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><h1> can not execute  the CGI  script!</h1>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<p>because the CGI script is unavailable or nonexistent.</p>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}