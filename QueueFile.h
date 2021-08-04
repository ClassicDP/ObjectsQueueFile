//
// Created by dmitry on 30.07.2021.
//

#ifndef OBJECTSQUEUEFILE_QUEUEFILE_H
#define OBJECTSQUEUEFILE_QUEUEFILE_H


#include <cstdint>
#include "BackupStack.h"




struct FileHeaderStruct {
    int64_t DataPtr;
    int64_t nextObjectPtr;
    int64_t firstObjectSize;
    int64_t firstObjectPtr;
    int64_t loopStartPtr;
    int64_t loopNotTransferredPtr;
    int64_t objectsCount;
    int64_t backupPtr;
    bool hasBackupData;
};


class QueueFile {
    static FileHeaderStruct * fileHeader;
    static FileField fileField;

public:
    static int fileDescriptor;
    static BackupStack backupStack;
    const char * fileName;
    explicit QueueFile (const char * fileName);
    ~QueueFile();
    static FileHeaderStruct getHeader();
    static FileHeaderStruct * setHeader();
    void put(const char * object);


};

#endif //OBJECTSQUEUEFILE_QUEUEFILE_H
