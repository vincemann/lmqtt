#ifndef __FILELOCATOR_H__
#define __FILELOCATOR_H__

#include <dirent.h>

class FileLocator{
    dirent* findFile(char dir, char name);
}

#endif // __FILELOCATOR_H__