
#include <dirent.h>
#include "FileLocator.h"

dirent* FileLocator::findFile(char dir, char name) 
{
    len = strlen(name);
    dirp = opendir(dir);
    while ((dp = readdir(dirp)) != NULL)
            if (dp->d_namlen == len && !strcmp(dp->d_name, name)) {
                    (void)closedir(dirp);
                    return dp;
            }
    (void)closedir(dirp);
    return 0;
}
