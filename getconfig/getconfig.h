#ifndef __GETCONFIG_HEADER___
#define __GETCONFIG_HEADER___
#include "../common/common.h"
#include "../servertypes.h"
bool IsExist(LPCSTR path);
bool isHasEqual(LPCSTR strLine);
bool IsSpaceLine(LPCSTR strLine);
bool IsNotes(LPCSTR strNotes);
int Trim(LPSTR des, LPCSTR src);
int GetKeyValue(LPSTR value, LPSTR key, LPCSTR szConfig);
int GetConfig(LPSTR value, LPCSTR key, LPCSTR path);

#endif
