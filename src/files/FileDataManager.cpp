
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


char *FileDataManager::find(char *startDir, char *name)
{
    dirent *entry = 0;
//    int len = strlen(name);
    DIR *dir = opendir(startDir);
    while ((entry = readdir(dir)) != 0)
    {
        if (!strcmp(entry->d_name, name))
        {
            (void)closedir(dir);
            int fd = open(entry->d_name, O_RDONLY);
            int len = lseek(fd, 0, SEEK_END);
            // todo maybe replace with read ?
            char *data = (char *) mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
            return data;
        }
    }
    (void)closedir(dir);
    return 0;
}

int FileDataManager::store(const char *targetDir, char *name, char *content) {
    int len = strlen(targetDir) + strlen(name) + 1;
    char filePath[len];
    sprintf(filePath,"%s/%s",targetDir,name);
    FILE *fp = fopen(filePath,"a");
    if(fp == nullptr){
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
