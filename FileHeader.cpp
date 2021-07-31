//
// Created by dmitry on 30.07.2021.
//

#include <cstdio>
#include <unistd.h>
#include "FileHeader.h"
#include "QueueFile.h"
#include "BackupStack.h"
BackupStack QueueFile::backupStack;

FileHeader::FileHeader() {

    auto fSize = lseek(QueueFile::fileDescriptor, 0, SEEK_END);
    if (sizeof fileHeaderData <= fSize) {
        pread64(QueueFile::fileDescriptor, &fileHeaderData, sizeof fileHeaderData, 0);
    } else {
        fileHeaderData.hasBackupData = false;
        fileHeaderData.objectsCount = 0;
        pwrite64(QueueFile::fileDescriptor, &fileHeaderData, sizeof fileHeaderData, 0);
    }
    fileField.size = sizeof fileHeaderData;
    fileField.start = 0;
}

FileHeaderData FileHeader::getHeader() {
    return fileHeaderData;
}

FileHeaderData *FileHeader::setHeader() {
    QueueFile::backupStack.push(fileField);
    return &fileHeaderData;
}
