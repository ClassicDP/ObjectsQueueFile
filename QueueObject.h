
#ifndef OBJECTSQUEUEFILE_QUEUEOBJECT_H
#define OBJECTSQUEUEFILE_QUEUEOBJECT_H

#include <cinttypes>
#include "DynamicArray.h"
#include "BaseHeader.h"

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

class QueueObject: BaseHeader {
    ObjectHeaderStruct *objectHeader;
    bool headerOnly;


public:
    const char *data;

    // load object from file
    QueueObject(int64_t ptr, int64_t size);
    // load only objectHeader
    explicit QueueObject(int64_t ptr);
    // create new object, write to file
    explicit QueueObject(const char *string, QueueObject *parentObject = nullptr);

    ~QueueObject();
    ObjectHeaderStruct getHeader();
    ObjectHeaderStruct * setHeader();


};



#include <cstdint>
#include "DynamicArray.h"

#endif //OBJECTSQUEUEFILE_QUEUEOBJECT_H
