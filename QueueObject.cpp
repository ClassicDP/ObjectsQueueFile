
#include <cstring>
#include <unistd.h>
#include "QueueObject.h"
#include "QueueFile.h"



std::set <HeaderBuf*> QueueFile::objectsSet;
QueueFile * QueueFile::queueFile;

QueueObject::QueueObject(const char *data, QueueObject *parentObject) {
    int sizeOfData = 0;
    while (data[sizeOfData ++]) {}
    auto sizeOfBuf = sizeOfData + sizeof *header;
    buf = new DynamicArray<char>(sizeOfBuf);
    header = reinterpret_cast<ObjectHeaderStruct *>(buf->data);
    this->data = buf->data + sizeof *header;
    memcpy((void *) this->data, data, sizeOfData);
    header->ptr =  QueueFile::getHeader().nextObjectPtr;
    header->size = sizeOfData;

    if (parentObject) {
        header->prevPtr = parentObject->header->ptr;
        header->prevSize = parentObject->header->size;
        header->isFirst = false;
        parentObject->setHeader()->nextPtr = header->ptr;
        parentObject->setHeader()->nextSize = header->size;
        parentObject->setHeader()->isFirst = false;
    } else {
        header->isFirst = true;
        QueueFile::queueFile->setHeader()->firstObjectPtr = header->ptr;
        QueueFile::queueFile->setHeader()->firstObjectSize = header->size;
    }
    pwrite64(QueueFile::fileDescriptor,  buf->data, buf->size, header->ptr);
    QueueFile::queueFile->setHeader()->nextObjectPtr = header->ptr + buf->size;
    QueueFile::queueFile->setHeader()->lastObjectPtr = header->ptr;
    QueueFile::queueFile->setHeader()->lastObjectSize = header->size;

}

QueueObject::~QueueObject() {

}

ObjectHeaderStruct QueueObject::getHeader() {
    return *header;
}

ObjectHeaderStruct *QueueObject::setHeader() {
    bufHeader.ptr = header->ptr;
    bufHeader.size = sizeof *header;
    QueueFile::objectsSet.insert(this);
    return header;
}


QueueObject::QueueObject(int64_t ptr, int64_t size) {
    buf = new DynamicArray<char> (size + sizeof *header);
    pread64(QueueFile::fileDescriptor, buf->data, buf->size, ptr);
    header = reinterpret_cast<ObjectHeaderStruct *>(buf->data);
    this->data = buf->data + sizeof *header;
    headerOnly = false;
}

QueueObject::QueueObject(int64_t ptr) {
    buf = new DynamicArray<char> (sizeof *header);
    bufHeader.ptr = ptr;
    bufHeader.size = buf->size;
    pread64(QueueFile::fileDescriptor, buf->data, buf->size, ptr);
    header = reinterpret_cast<ObjectHeaderStruct *>(buf->data);
    headerOnly = true;
}



