//
// Created by dmitry on 30.07.2021.
//

#ifndef OBJECTSQUEUEFILE_QUEUEFILE_H
#define OBJECTSQUEUEFILE_QUEUEFILE_H


#include <cstdint>
#include <set>
#include "BaseHeader.h"
#include "QueueObject.h"


struct FileHeaderStruct {
    int64_t nextObjectPtr;
    int64_t lastObjectPtr;
    int64_t lastObjectSize;
    int64_t firstObjectPtr;
    int64_t firstObjectSize;
    int64_t loopStartPtr;
    int64_t loopNotTransferredPtr;
    int64_t objectsCount;
    int64_t backupPtr;
    bool hasBackupData;
};


class QueueFile: BaseHeader {
    static FileHeaderStruct * fileHeader;


public:
    static QueueFile * queueFile;
    static int fileDescriptor;
    static std::set <BaseHeader*> objectsSet;
    const char * fileName;
    explicit QueueFile (const char * fileName);
    static FileHeaderStruct getHeader();
    FileHeaderStruct * setHeader();
    void push(const char * object);
    const char * pull ();
    void writeChanges();

};

#endif //OBJECTSQUEUEFILE_QUEUEFILE_H
