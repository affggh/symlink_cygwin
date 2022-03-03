/*
Copyright by affggh GPLv3
*/

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef USINGWIN32API
#define USINGWIN32API
#endif

#ifdef USINGWIN32API
#include <Windows.h>
#endif

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "arg less than 1\n Usage:%s <linktarget> <file>\n", argv[0]);
        return 1;
    }
    if(argc < 3)
    {
        fprintf(stderr, "file not defined...\n");
        return 1;
    }
	if(access(argv[2], 0)==0)
	{
		remove(argv[2]); // if exist file then delete it
	}
    FILE *fp;
    int i;
    i = 0;
    char ch[128];
    strcpy(ch, argv[1]);
    fp = fopen(argv[2], "w+");
    fprintf(fp, "!<symlink>\xff\xfe");
    for(i=0;i<strlen(ch);i++)
    {
        fputc(ch[i], fp);
        fputc(0, fp);
    }
	for(i=0;i<2;i++)
	{
		fputc(0, fp); // fill two /x00
	}
	#ifdef USINGWIN32API // 要不然太慢了
	SetFileAttributesA(argv[2], FILE_ATTRIBUTE_SYSTEM); // need include Windows.h
	#else
	char cmd[] = "attrib +s ";
	strcat(cmd, argv[2]);
	system(cmd);
	#endif
    fclose(fp);
	return 0;
}