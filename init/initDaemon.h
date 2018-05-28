#ifndef ___INITDAEMON_HEADER___
#define ___INITDAEMON_HEADER___
#include "../wrap/wrap.h"
#include "../parse/parseHeader.h"
#include "../getconfig/getconfig.h"
#include "../servertypes.h"
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
void init();
int GetInitStyle();
void init_as_daemon(void);
#endif
