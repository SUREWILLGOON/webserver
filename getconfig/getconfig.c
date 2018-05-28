#include "getconfig.h"
bool IsExist(LPCSTR path)
{
	if (access(path, 0) == -1)
		return false;
	return true;
}
bool isHasEqual(LPCSTR strLine)
{
	char *p = (char *)strLine;
	int n = 0;
	if (strlen(strLine) < 3)
		return false;
	while (*p != '\0')
	{
		if (*p == '=')
			n++;
		p++;
	}
	if (n != 1)
		return false;

	int k = 0;
	p = (char *)strLine;
	while (*p != '\0')
	{
		if (*p == '=')
			break;
		k++;
		p++;
	}
	if (k <= 0 || k >= strlen(strLine))
		return false;

	return true;
}

bool IsSpaceLine(LPCSTR strLine)
{
	char *p = (char *)strLine;
	int n = 0;
	while (*p != '\0')
	{
		if (*p != '\r' || *p != '\n')
			n++;
		p++;
	}
	if (n == 0)
		return true;

	return false;
}
bool IsNotes(LPCSTR strNotes)
{
	char *p = (char *)strNotes;
	int n = 0;
	while (*p != '\0')
	{
		if (*p == '#')
			return true;
		p++;
	}
	return false;
}

int Trim(LPSTR des, LPCSTR src)
{
	if (src == NULL)
		return -1;
	LPSTR p = (char *)src;
	while (*p != '\0')
	{
		if (isalpha(*p) || *p == '=' || isdigit(*p) || *p == '.' || *p == '/' || *p == ';' || *p == '-')
			*des++ = *p;
		p++;
	}
	*des = '\0';
}
int GetKeyValue(LPSTR value, LPSTR key, LPCSTR szConfig)
{
	LPSTR p = (char *)szConfig;
	int nPos = 0;

	while (*p != '\0')
	{
		if (*p == '=')
			break;
		nPos++;
		p++;
	}

	if (nPos == 0)
		return 0;

	p = (char *)szConfig;
	int i;
	for (i = 0; i < nPos; i++)
		key[i] = p[i];
	key[i] = '\0';

	int j = 0;
	for (i = nPos + 1; i < strlen(szConfig); i++)
		value[j++] = p[i];
	value[j] = '\0';

	return 1;
}
int GetConfig(LPSTR value, LPCSTR key, LPCSTR path)
{
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
		return -1;
	char buf[MAX_PATH];
	char temp[MAX_PATH];
	char key_buf[MAX_PATH];
	char value_buf[MAX_PATH];
	while (fgets(buf, MAX_PATH, fp) != NULL)
	{
		Trim(temp, buf);
		if (!IsSpaceLine(temp) && !IsNotes(temp) && isHasEqual(temp))
		{
			GetKeyValue(value_buf, key_buf, temp);
			if (strcmp(key_buf, key) == 0)
			{
				strcpy(value, value_buf);
				return 0;
			}
		}
	}
	return -1;
}
