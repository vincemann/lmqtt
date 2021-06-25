
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include "FileDataManager.h"
#include "../MsgException.h"
#include <exception>
#include <cstdio>
#include <Utils.h>





char *FileDataManager::find(const char *startDir,const char *name)
{
    dirent *entry = 0;
    DIR *dir = opendir(startDir);
    while ((entry = readdir(dir)) != 0)
    {
        if (!strcmp(entry->d_name, name))
        {
            char * buffer = 0;
            long length;
            (void)closedir(dir);
            char* filePath = FileDataManager::combinePaths(startDir,name);
            FILE *f = fopen(filePath,"r");
            if (f)
            {
                fseek (f, 0, SEEK_END);
                length = ftell (f);
                fseek (f, 0, SEEK_SET);
                buffer = (char*) malloc (length);
                if (buffer)
                {
                    fread (buffer, 1, length, f);
                }
                fclose (f);
            }else{
                delete filePath;
                throw MsgException(Utils::formatToCharP("Cant open file %s\n",filePath));
            }
            delete filePath;
            return buffer;
        }
    }
    (void)closedir(dir);
    return 0;
}

int FileDataManager::store(const char *targetDir, const char *name,const char *content) {
    char* filePath = FileDataManager::combinePaths(targetDir,name);
    FILE *fp = fopen(filePath,"a");
    delete filePath;
    if(fp == 0){
        throw MsgException(Utils::formatToCharP("Cant open file %s\n",filePath));
    }
    if(fprintf(fp,"%s", content)< 0){
        throw MsgException(Utils::formatToCharP("Unable to store file %s\n",filePath));

    }
    fflush(fp);
//    int fd = open(entry->d_name, O_WRONLY | O_CREAT);
//    int len = strlen(content);
//    write(fp,content,len);
    fclose(fp);
    return 0;
}
