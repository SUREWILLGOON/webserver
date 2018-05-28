#include "common.h"
void TrimSpace(LPSTR des, LPSTR src)
{
  while (*src != '\0')
  {
    if (*src != ' ')
      *des++ = *src;
    src++;
  }
}
void Err_Out(LPCSTR strOut)
{
  fprintf(stderr, "%s : %s\n", strOut, strerror(errno));
  Writelog(strOut);
  exit(0);
}
void error_die(const char *sc)
{
    syslog(LOG_CRIT,sc);
}
int GetFileLength(LPCSTR strPath)
{
  FILE *fp = NULL;
  long size = 0;
  fp = fopen(strPath, "rb");
  char buf[256];
  if (fp == NULL)
  {
    sprintf(buf, "open file %s error!", strPath);
    fclose(fp);
    Err_Out(buf);
  }
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fclose(fp);
  return size;
}
int forReachDir(LPCSTR Dir)
{
 /* DIR *dp;
  struct dirent *entry;
  struct stat statbuf;
  if ((dp = opendir(Dir) )== NULL)
    return -1;
  chdir(Dir);
  while ((entry = readdir(dp)) != NULL)
    printf(entry->d_name);*/
  return 0;
}

