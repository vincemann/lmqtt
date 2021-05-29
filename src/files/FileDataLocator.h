#ifndef __FILELOCATOR_H__
#define __FILELOCATOR_H__

#include <dirent.h>

class FileLocator{
public:
    dirent* findFileData(char* dir, char* name);
};

#endif // __FILELOCATOR_H__