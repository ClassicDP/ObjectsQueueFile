
#include <cstring>
#include <unistd.h>
#include "QueueObject.h"
#include "QueueFile.h"



std::set <BaseHeader*> QueueFile::objectsSet;
QueueFile * QueueFile::queueFile;

QueueObject::QueueObject(const char *string, QueueObject *parentObject) {
    headerOnly = false;
    int sizeOfData = 0;
    while (string[sizeOfData ++]) {}
    auto sizeOfBuf = sizeOfData + sizeof *objectHeader;
    buf = new DynamicArray<char>(sizeOfBuf);
    objectHeader = reinterpret_cast<ObjectHeaderStruct *>(buf->data);
    data = buf->data + sizeof *objectHeader;
    memcpy((void *) data, string, sizeOfData);
    objectHeader->ptr =  QueueFile::getHeader().nextObjectPtr;
    objectHeader->size = sizeOfData;

    if (parentObject) {
        objectHeader->prevPtr = parentObject->objectHeader->ptr;
        objectHeader->prevSize = parentObject->objectHeader->size;
        objectHeader->isFirst = false;
        parentObject->setHeader()->nextPtr = objectHeader->ptr;
        parentObject->setHeader()->nextSize = objectHeader->size;
    } else {
        objectHeader->isFirst = true;
        QueueFile::queueFile->setHeader()->firstObjectPtr = objectHeader->ptr;
        QueueFile::queueFile->setHeader()->firstObjectSize = objectHeader->size;
    }
    objectHeader->isLast = true;

    pwrite64(QueueFile::fileDescriptor, buf->data, buf->size, objectHeader->ptr);
    QueueFile::queueFile->setHeader()->nextObjectPtr = objectHeader->ptr + buf->size;
    QueueFile::queueFile->setHeader()->lastObjectPtr = objectHeader->ptr;
    QueueFile::queueFile->setHeader()->lastObjectSize = objectHeader->size;


}

QueueObject::~QueueObject() {

}

ObjectHeaderStruct QueueObject::getHeader() {
    return *objectHeader;
}

ObjectHeaderStruct *QueueObject::setHeader() {
    QueueFile::objectsSet.insert(this);
    return objectHeader;
}


QueueObject::QueueObject(int64_t ptr, int64_t size) {
    buf = new DynamicArray<char> (size + sizeof *objectHeader);
    pread64(QueueFile::fileDescriptor, buf->data, buf->size, ptr);
    objectHeader = reinterpret_cast<ObjectHeaderStruct *>(buf->data);
    this->data = buf->data + sizeof *objectHeader;
    headerOnly = false;

}

QueueObject::QueueObject(int64_t ptr) {
    buf = new DynamicArray<char> (sizeof *objectHeader);
    headerFileField.ptr = ptr;
    headerFileField.size = buf->size;
    pread64(QueueFile::fileDescriptor, buf->data, buf->size, ptr);
    objectHeader = reinterpret_cast<ObjectHeaderStruct *>(buf->data);
    headerOnly = true;

}



