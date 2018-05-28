#ifndef ___COMONMON_HEADER___
#define ___COMONMON_HEADER___
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/param.h>
#include <syslog.h>
#include <stdlib.h>
typedef const char *LPCSTR;
typedef char *LPSTR;
#define MB_BYTE (1024*1024*2)

void TrimSpace(LPSTR des, LPSTR src);
void Err_Out(LPCSTR strOut);
int GetFileLength(LPCSTR strPath);
int forReachDir(LPCSTR Dir);
void error_die(const char *sc);
#endif
