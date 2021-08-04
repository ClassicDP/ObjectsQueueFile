
#include <cstring>
#include <unistd.h>
#include "QueueObject.h"
#include "QueueFile.h"

BackupStack QueueFile::backupStack;

QueueObject::QueueObject(const char *data) {
    int sizeOfData = 0;
    while (data[sizeOfData ++]) {}
    auto sizeOfBuf = sizeOfData + sizeof *header;
    buf = new DynamicArray<char>(sizeOfBuf);
    header = reinterpret_cast<ObjectHeaderStruct *>(buf->data);
    this->data = buf->data + sizeof *header;
    memcpy((void *) this->data, data, sizeOfData);
    fileField.start = -1;
    header->size = sizeOfData;
}

QueueObject::~QueueObject() {


}

ObjectHeaderStruct QueueObject::getHeader() {
    return *header;
}

ObjectHeaderStruct *QueueObject::setHeader() {
    if (fileField.start > 0) QueueFile::backupStack.push(fileField);
    return header;
}

void QueueObject::write(int64_t parentPtr = 0, int64_t parentSize = 0) {
    if (parentPtr) {
        header->prevPtr = parentPtr;
        header->prevSize = parentSize;
        header->isFirst = false;
    } else header->isFirst = true;
    header->ptr =  QueueFile::getHeader().nextObjectPtr;
    pwrite64(QueueFile::fileDescriptor,  buf->data, buf->size, header->ptr);
}

QueueObject::QueueObject(int64_t ptr, int64_t size) {
    buf = new DynamicArray<char> (size + sizeof *header);
    pread64(QueueFile::fileDescriptor, buf->data, buf->size, ptr);
    header = reinterpret_cast<ObjectHeaderStruct *>(buf->data);
    this->data = buf->data + sizeof *header;
}


