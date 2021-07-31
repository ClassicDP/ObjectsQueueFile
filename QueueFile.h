//
// Created by dmitry on 30.07.2021.
//

#ifndef OBJECTSQUEUEFILE_QUEUEFILE_H
#define OBJECTSQUEUEFILE_QUEUEFILE_H


#include "BackupStack.h"

class FileHeader;
class QueueFile {
    FileHeader *fileHeader;

public:
    static int fileDescriptor;
    static BackupStack backupStack;
    const char * fileName;
    QueueFile (const char * fileName);
    ~QueueFile();


};


#endif //OBJECTSQUEUEFILE_QUEUEFILE_H
