
#ifndef OBJECTSQUEUEFILE_QUEUEOBJECT_H
#define OBJECTSQUEUEFILE_QUEUEOBJECT_H

#include <cinttypes>
#include <iostream>
#include "DynamicArray.h"
#include "BaseHeader.h"


#include "json.hpp"

struct ObjectHeaderStruct {
    int64_t ptr;
    int64_t size;
    int64_t prevPtr;
    int64_t prevSize;
    int64_t nextPtr;
    int64_t nextSize;
    bool isFirst;
    bool isLast;

    nlohmann::json toJson() {
        return nlohmann::json({{"ptr",      ptr},
                               {"size",     size},
                               {"prevPtr",  prevPtr},
                               {"prevSize", prevSize},
                               {"nextPtr",  nextPtr},
                               {"nextSize", nextSize},
                               {"isFirst",  isFirst},
                               {"isLast",   isLast}});
    }
};

class QueueObject : BaseHeader {
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

    int64_t moveTo(int64_t ptr);

    ~QueueObject();

    ObjectHeaderStruct getHeader();
    void toLog ()
    {
        std::string x1 (to_string(getHeader().toJson()));
        std::string x2 (data);
        std::cout << x1 << std::endl;
        std::cout << x2 << std::endl << std::endl;

    }

    ObjectHeaderStruct *setHeader();


};


#include <cstdint>
#include "DynamicArray.h"

#endif //OBJECTSQUEUEFILE_QUEUEOBJECT_H
