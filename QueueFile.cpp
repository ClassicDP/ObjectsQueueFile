//
// Created by dmitry on 30.07.2021.
//

#include <cstdio>
#include <fcntl.h>
#include "QueueFile.h"
#include "BackupStack.h"


int QueueFile::fileDescriptor;

QueueFile::QueueFile(const char *fileName) {
    this->fileName = fileName;
    remove(fileName);
    QueueFile::fileDescriptor = open(fileName, O_RDWR | O_CREAT, 0777);

}

QueueFile::~QueueFile() {

}
