
#ifndef OBJECTSQUEUEFILE_QUEUEOBJECT_H
#define OBJECTSQUEUEFILE_QUEUEOBJECT_H

#include <cinttypes>
#include "DynamicArray.h"
#include "HeaderBuf.h"

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

class QueueObject: HeaderBuf {
    ObjectHeaderStruct *header;
    bool headerOnly;


public:
    const char *data;

    QueueObject(int64_t ptr, int64_t size);
    // load only header
    QueueObject(int64_t ptr);
    QueueObject(const char *data, QueueObject *parentObject = nullptr);

    ~QueueObject();
    ObjectHeaderStruct getHeader();
    ObjectHeaderStruct * setHeader();


};



#include <cstdint>
#include "DynamicArray.h"

#endif //OBJECTSQUEUEFILE_QUEUEOBJECT_H
