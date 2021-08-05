//
// Created by dmitry on 04.08.2021.
//

#ifndef OBJECTSQUEUEFILE_HEADERBUF_H
#define OBJECTSQUEUEFILE_HEADERBUF_H

#include "DynamicArray.h"
struct HeaderBuf {
    DynamicArray<char> *buf;
    struct {
        int64_t ptr;
        int64_t size;
    } bufHeader;
};


#endif //OBJECTSQUEUEFILE_HEADERBUF_H
