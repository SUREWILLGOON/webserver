#ifndef ___LOG_HEADER___
#define ___LOG_HEADER___
#include "../common/common.h"
#include "../parse/parseHeader.h"
#include "../wrap/wrap.h"
#include "../servertypes.h"
typedef struct tm* pTM;

static int GetMonth(pTM localTime);
static int GetDate(void);
static int GetHour(void);
static int GetMin(void);
static int GetSecond(void);
LPSTR GetstrTime(void);
bool isChangeTime(void);
int Writelog(LPCSTR buf);
int WriteTime(FILE *logfp);
















#endif
