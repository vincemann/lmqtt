
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
#include <errno.h>
#include<stdio.h>
#include<stdlib.h>



// der gil isn gil
int remove_directory(const char *path) {
    DIR *d = opendir(path);
    size_t path_len = strlen(path);
    int r = -1;

    if (d) {
        struct dirent *p;

        r = 0;
        while (!r && (p=readdir(d))) {
            int r2 = -1;
            char *buf;
            size_t len;

            /* Skip the names "." and ".." as we don't want to recurse on them. */
            if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
                continue;

            len = path_len + strlen(p->d_name) + 2;
            buf = (char*) malloc(len);

            if (buf) {
                struct stat statbuf;

                snprintf(buf, len, "%s/%s", path, p->d_name);
                if (!stat(buf, &statbuf)) {
                    if (S_ISDIR(statbuf.st_mode))
                        r2 = remove_directory(buf);
                    else
                        r2 = unlink(buf);
                }
                free(buf);
            }
            r = r2;
        }
        closedir(d);
    }

    if (!r)
        r = rmdir(path);

    return r;
}

// pr terminal resolved by host
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
                    buffer[length] = '\0';
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

unsigned char FileDataManager::exists(char* dir, char* file){
    char* filePath = FileDataManager::combinePaths(dir,file);
    struct stat st = {0};

    if (stat(filePath, &st) == -1) {
        return 0;
//        if (errno == EFAULT){
//            return 0;
//        }else{
//            printf("%s\n", strerror(errno));
//            throw MsgException("Invalid File exception");
//        }
    }else{
        return 1;
    }
}

int FileDataManager::store(const char *targetDir, const char *name,const char *content) {
    char* filePath = FileDataManager::combinePaths(targetDir,name);
    FILE *fp = fopen(filePath,"w+");
    delete filePath;
    if(fp == 0){
        throw MsgException(Utils::formatToCharP("Cant open file %s\n",filePath));
    }
    if(fprintf(fp,"%s", content)< 0){
        throw MsgException(Utils::formatToCharP("Unable to saveMsg file %s\n",filePath));

    }
    fflush(fp);
//    int fd = open(entry->d_name, O_WRONLY | O_CREAT);
//    int len = strlen(content);
//    write(fp,content,len);
    fclose(fp);
    return 0;
}

void FileDataManager::remove(char *file) {
    remove_directory(file);
}
