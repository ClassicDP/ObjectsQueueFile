//
// Created by dmitry on 04.08.2021.
//

#ifndef OBJECTSQUEUEFILE_BASEHEADER_H
#define OBJECTSQUEUEFILE_BASEHEADER_H

#include "DynamicArray.h"
typedef struct {
    int64_t ptr;
    int64_t size;} HeaderFileField;
struct BaseHeader {
    DynamicArray<char> *buf = nullptr;
    HeaderFileField headerFileField;
    ~BaseHeader() {
        delete buf;
    }
};


#endif //OBJECTSQUEUEFILE_BASEHEADER_H
