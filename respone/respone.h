#ifndef ___RESPONE_HEADER___
#define ___RESPONE_HEADER___
#include "../common/common.h"
#include "../wrap/wrap.h"
#include "../servertypes.h"
#include "../parse/parseHeader.h"
#include "../log/log.h"
typedef struct _FILEINFO
{
    int isExist;
    char path[MAX_BUF];
    int type;
}FILEINFO;
void SendHomePage(int client);
void sendBadRequest(int client);
void sendRespone(int client,LPCSTR strRecv);
void sendResponeHeader(int client);
void sendTextFile(int client,LPCSTR FileName);
void sendBinaryFile(int client ,LPCSTR FileName);
void sendBinaryHeader(int client ,LPCSTR FileName);
void sendTextHeader(int client);
void sendAnyFileHeader(int client,LPCSTR FileType,LPCSTR FileName);
void sendAnyFile(int client,LPCSTR FileType,LPCSTR FileName);
void sendFile(int client, LPCSTR FileName);
void sendNotFound(int client);
void sendPostPage(int client,LPCSTR strParam);
void sendGetPage(int client ,LPCSTR strParam);
void sendUnimplemented(int client);
void ShowDirectory(int client,LPCSTR fileName);
void execute_cgi(int client,LPCSTR fileName,LPCSTR query_string);
void getFileInfo(LPCSTR strPath,FILEINFO *file_inf);
void GetHttpFilePath(LPSTR filepath,LPCSTR filename);
void GetWebRoot(LPSTR path);
#endif
