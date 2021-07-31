//
// Created by dmitry on 30.07.2021.
//

#ifndef OBJECTSQUEUEFILE_FILEHEADER_H
#define OBJECTSQUEUEFILE_FILEHEADER_H


#include <cstdint>
#include "BackupStack.h"


struct FileHeaderData {
    int64_t nextObjectSize;
    int64_t objectsCount;
    int64_t backupPtr;
    bool hasBackupData;
};

class FileHeader {
private:
    FileHeaderData fileHeaderData;
    FileField fileField;


public:
    FileHeader();
    FileHeaderData getHeader ();
    FileHeaderData * setHeader ();

};


#endif //OBJECTSQUEUEFILE_FILEHEADER_H
