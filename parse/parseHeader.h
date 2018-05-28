#ifndef ___PARSEHEADER_HEADER___
#define ___PARSEHEADER_HEADER___
#include "../common/common.h"
#include "../servertypes.h"
#include "../getconfig/getconfig.h"
int GetConfigPath(LPSTR strConfigPath);
int IsPermittedIP(LPCSTR strHost);
int GetFileType(LPSTR FileType, LPCSTR FileName);
int GetExtName(char cSeparator,LPSTR extName, LPCSTR FileName);
int GetFileTypeByFile(LPSTR typeBuf, LPCSTR strType, LPCSTR strPath);
//date:5.5modify
int GetRequestHeader(LPSTR RequestHeader,LPCSTR strRecv);
int GetMethod(LPSTR Method,LPCSTR RequestHeader);
int GetRequestString(LPSTR Requeststring,LPCSTR RequestHeader );
int GetProtocolVersion(LPSTR ProtocolVersion,LPCSTR RequestHeader);
int GetMessageHeader(LPSTR strValue,LPCSTR msgHeader,LPCSTR strData);
int GetRequestParam(LPSTR strParam,LPCSTR Requeststring);
int GetRequestFile(LPSTR strRequestFile,LPCSTR Requeststring);
int GetBoundary(LPSTR strBoundary,LPCSTR strRecv);
int GetPostData(LPSTR strData,int n,LPCSTR strRecv);
int GetSaveFileName(LPSTR strName,LPCSTR strData);
int GetSaveData(LPCSTR strData,int n,LPCSTR strBoundary);
int ParseData(LPCSTR strData,int n,LPCSTR strBoundary);
int GetValueByString(LPSTR strValue,LPCSTR key_start,LPCSTR value_end,LPCSTR str,int n);
LPCSTR search_string(LPCSTR des, LPCSTR src, int n);
LPSTR rang_search(LPCSTR des,LPCSTR src_start,LPCSTR src_end);

#endif
