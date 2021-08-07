//
// Created by dmitry on 04.08.2021.
//

#ifndef OBJECTSQUEUEFILE_HEADERBUF_H
#define OBJECTSQUEUEFILE_HEADERBUF_H

#include "DynamicArray.h"
typedef struct {
    int64_t ptr;
    int64_t size;} BufHeader;
struct HeaderBuf {
    DynamicArray<char> *buf = nullptr;
    BufHeader bufHeader;
    ~HeaderBuf() {
        delete buf;
    }
};


#endif //OBJECTSQUEUEFILE_HEADERBUF_H
