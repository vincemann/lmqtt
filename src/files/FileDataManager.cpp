
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include "FileDataManager.h"


char *FileDataManager::find(char *startDir, char *name)
{
    dirent *entry = 0;
    int len = strlen(name);
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

int FileDataManager::store(char *targetDir, char *name, char *content) {
    dirent *entry = 0;
    int len = strlen(name);
    DIR *dir = opendir(targetDir);
    while ((entry = readdir(dir)) != 0)
    {
        if (!strcmp(entry->d_name, name))
        {
            (void)closedir(dir);
            int fd = open(entry->d_name, O_RDONLY);
            int len = strlen(content);
            write(fd,content,len);
            return 0;
        }
    }
    (void)closedir(dir);
}
