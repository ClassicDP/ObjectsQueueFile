//
// Created by dmitry on 30.07.2021.
//

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include "QueueFile.h"
#include "BackupStack.h"


int QueueFile::fileDescriptor;
FileField QueueFile::fileField;
FileHeaderStruct * QueueFile::fileHeader;


QueueFile::QueueFile(const char *fileName) {
    this->fileName = fileName;
    remove(fileName);
    QueueFile::fileDescriptor = open(fileName, O_RDWR | O_CREAT, 0777);
    fileHeader = new FileHeaderStruct;
    auto fSize = lseek(QueueFile::fileDescriptor, 0, SEEK_END);
    if (sizeof *fileHeader <= fSize) {
        pread64(QueueFile::fileDescriptor, fileHeader, sizeof *fileHeader, 0);
    } else {
        fileHeader->hasBackupData = false;
        fileHeader->objectsCount = 0;
        pwrite64(QueueFile::fileDescriptor, fileHeader, sizeof *fileHeader, 0);
    }
    fileField.size = sizeof *fileHeader;
    fileField.start = 0;

}

QueueFile::~QueueFile() {

}

void QueueFile::put(const char *object) {
    auto nextPtr = fileHeader->nextObjectPtr;


}

FileHeaderStruct QueueFile::getHeader() {
    return *fileHeader;
}

FileHeaderStruct *QueueFile::setHeader() {
    QueueFile::backupStack.push(fileField);
    return fileHeader;
}
