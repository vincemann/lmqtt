
#include <dirent.h>
#include "FileLocator.h"
#include <string.h>

char* FileLocator::findFileData(char* dirPath, char* name) 
{
    dirent* dp= 0;
    int len = strlen(name);
    DIR* dir = opendir(dirPath);
    while ((dp = readdir(dir)) != 0){
        if (!strcmp(dp->d_name, name)) {
                (void)closedir(dir);
                int fd = open("filename", O_RDONLY);
                int len = lseek(fd, 0, SEEK_END);
                char *data = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
                return data;
        }
    }
    (void)closedir(dir);
    return 0;
}
