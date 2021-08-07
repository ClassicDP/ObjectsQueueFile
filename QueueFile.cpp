
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include "QueueFile.h"
#include "HeaderBuf.h"


int QueueFile::fileDescriptor;
FileHeaderStruct *QueueFile::fileHeader;


QueueFile::QueueFile(const char *fileName) {
    queueFile = this;
    this->fileName = fileName;
    remove(fileName);
    QueueFile::fileDescriptor = open(fileName, O_RDWR | O_CREAT, 0777);
    buf = new DynamicArray<char>(sizeof *fileHeader);
    fileHeader = reinterpret_cast<FileHeaderStruct *>(buf->data);
    auto fSize = lseek(QueueFile::fileDescriptor, 0, SEEK_END);
    if (sizeof *fileHeader <= fSize) {
        pread64(QueueFile::fileDescriptor, fileHeader, sizeof *fileHeader, 0);
    } else {
        fileHeader->hasBackupData = false;
        fileHeader->objectsCount = 0;
        fileHeader->nextObjectPtr = sizeof *fileHeader;
        fileHeader->loopStartPtr = 0;
        pwrite64(QueueFile::fileDescriptor, fileHeader, sizeof *fileHeader, 0);
    }
    objectsSet.clear();
    fileHeader->lastObjectPtr = 0;
    bufHeader.ptr = 0;
    bufHeader.size = sizeof *fileHeader;
}


void QueueFile::push(const char *object) {
    auto nextPtr = fileHeader->nextObjectPtr;
    auto parentObject = fileHeader->lastObjectPtr ? new QueueObject(fileHeader->lastObjectPtr) : nullptr;
    QueueObject obj(object, parentObject);
    setHeader()->objectsCount++;
    writeChanges();
    delete parentObject;


}

FileHeaderStruct QueueFile::getHeader() {
    return *fileHeader;
}

FileHeaderStruct *QueueFile::setHeader() {
    bufHeader.ptr = 0;
    bufHeader.size = sizeof *fileHeader;
    objectsSet.insert(this);
    return fileHeader;

}

void QueueFile::writeChanges() {
    setHeader()->hasBackupData = true;
    auto ptr = fileHeader->backupPtr = lseek(QueueFile::fileDescriptor, 0, SEEK_END);
    for (auto it: objectsSet) {
        pwrite64(fileDescriptor, &it->bufHeader, sizeof it->bufHeader, ptr);
        ptr += sizeof it->bufHeader;
        DynamicArray<char> tmpBuf(it->bufHeader.size);
        pread64(fileDescriptor, tmpBuf.data, tmpBuf.size, it->bufHeader.ptr);
        pwrite64(fileDescriptor, tmpBuf.data, tmpBuf.size, ptr);
        ptr += tmpBuf.size;
    }
    pwrite64(fileDescriptor, &fileHeader, sizeof *fileHeader, 0);
    fsync(fileDescriptor);
    for (auto it: objectsSet) {
        pwrite64(fileDescriptor, it->buf->data, it->buf->size, it->bufHeader.ptr);
    }
    objectsSet.clear();
    fileHeader->hasBackupData = false;
    pwrite64(fileDescriptor, fileHeader, sizeof *fileHeader, 0);
    fsync(fileDescriptor);
    truncate(fileName, fileHeader->backupPtr);
}

const char *QueueFile::pull() {
    if (getHeader().objectsCount == 0) return "";
    QueueObject obj(fileHeader->firstObjectPtr, fileHeader->firstObjectSize);
    QueueObject objNext(obj.getHeader().nextPtr);
    objNext.setHeader()->isFirst = true;
    setHeader()->firstObjectPtr = objNext.getHeader().ptr;
    setHeader()->firstObjectSize = objNext.getHeader().size;
    setHeader()->objectsCount--;
    writeChanges();
    return obj.data;
}
