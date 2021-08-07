
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include "QueueFile.h"
#include "BaseHeader.h"


int QueueFile::fileDescriptor;
FileHeaderStruct *QueueFile::fileHeader;
const char *QueueFile::fileName;


QueueFile::QueueFile(const char *fileName) {
    queueFile = this;
    QueueFile::fileName = fileName;
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
        fileHeader->hasActiveTransfer = false;
        pwrite64(QueueFile::fileDescriptor, fileHeader, sizeof *fileHeader, 0);
    }
    objectsSet.clear();
    fileHeader->lastObjectPtr = 0;
    headerFileField.ptr = 0;
    headerFileField.size = sizeof *fileHeader;
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
    objectsSet.insert(queueFile);
    return fileHeader;

}

void QueueFile::writeChanges() {
    fileHeader->hasBackupData = true;
    auto ptr = fileHeader->backupPtr = lseek(QueueFile::fileDescriptor, 0, SEEK_END);
    // backup
    for (auto it: objectsSet) {
        pwrite64(fileDescriptor, &it->headerFileField, sizeof it->headerFileField, ptr);
        ptr += sizeof it->headerFileField;
        DynamicArray<char> tmpBuf(it->headerFileField.size);
        pread64(fileDescriptor, tmpBuf.data, tmpBuf.size, it->headerFileField.ptr);
        pwrite64(fileDescriptor, tmpBuf.data, tmpBuf.size, ptr);
        ptr += tmpBuf.size;
    }
    pwrite64(fileDescriptor, fileHeader, sizeof *fileHeader, 0);
    fsync(fileDescriptor);
    // write new data
    for (auto it: objectsSet) {
        pwrite64(fileDescriptor, it->buf->data, it->buf->size, it->headerFileField.ptr);
    }
    objectsSet.clear();
    fileHeader->hasBackupData = false;
    pwrite64(fileDescriptor, fileHeader, sizeof *fileHeader, 0);
    fsync(fileDescriptor);
    // delete backup data
    truncate(QueueFile::fileName, fileHeader->backupPtr);
}

const char *QueueFile::pull() {
    if (getHeader().objectsCount == 0) return "";
    QueueObject obj(fileHeader->firstObjectPtr, fileHeader->firstObjectSize);
    QueueObject * objNext = nullptr;
    if (!obj.getHeader().isLast) {
        objNext = new QueueObject(obj.getHeader().nextPtr);
        objNext->setHeader()->isFirst = true;
        setHeader()->firstObjectPtr = objNext->getHeader().ptr;
        setHeader()->firstObjectSize = objNext->getHeader().size;
    }
    setHeader()->objectsCount--;
    if (!fileHeader->hasActiveTransfer &&
        (fileHeader->nextObjectPtr - fileHeader->firstObjectPtr) <=
        (fileHeader->firstObjectPtr - sizeof *fileHeader)) {
        setHeader()->nextObjectPtr = sizeof *fileHeader + fileHeader->nextObjectPtr - fileHeader->firstObjectPtr;
        setHeader()->hasActiveTransfer = true;
        setHeader()->transferToPtr = sizeof *fileHeader;
        setHeader()->transferFromPtr = fileHeader->firstObjectPtr;
    }
    if (fileHeader->hasActiveTransfer) {
        if (!obj.getHeader().isLast && obj.getHeader().nextPtr > obj.getHeader().ptr) {
            if (setHeader()->transferFromPtr < obj.getHeader().nextPtr)
                setHeader()->transferFromPtr = obj.getHeader().nextPtr;
        }
    }
    writeChanges();
    delete objNext;
    return obj.data;
}

void QueueFile::transferObjects(int64_t ptr, int64_t size) {

    while (fileHeader->hasActiveTransfer && (fileHeader->transferFromPtr < ptr + size)) {
        QueueObject obj(fileHeader->transferFromPtr);
        setHeader()->transferToPtr = obj.moveTo(fileHeader->transferToPtr);
        if (obj.getHeader().isLast || obj.getHeader().nextPtr < obj.getHeader().ptr)
            setHeader()->hasActiveTransfer = false;
        else
            setHeader()->transferFromPtr = obj.getHeader().nextPtr;
    }
    writeChanges();
}
