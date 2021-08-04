
#ifndef OBJECTSQUEUEFILE_QUEUEOBJECT_H
#define OBJECTSQUEUEFILE_QUEUEOBJECT_H

#include <cinttypes>
#include "BackupStack.h"
#include "DynamicArray.h"
struct ObjectHeaderStruct {
    int64_t ptr;
    int64_t size;
    int64_t prevPtr;
    int64_t prevSize;
    int64_t nextPtr;
    int64_t nextSize;
    bool isFirst;
    bool isLast;
};

class QueueObject {
    QueueObject(int64_t ptr, int64_t size);

    ObjectHeaderStruct *header;
    FileField fileField;
public:
    const char *data;
    explicit QueueObject(const char *data);
    QueueObject(int64_t ptr);
    ~QueueObject();
    ObjectHeaderStruct getHeader();
    ObjectHeaderStruct * setHeader();


    DynamicArray<char> * buf;


    void write(int64_t parentPtr, int64_t parentSize);

};



#include <cstdint>
#include "BackupStack.h"
#include "DynamicArray.h"

#endif //OBJECTSQUEUEFILE_QUEUEOBJECT_H
