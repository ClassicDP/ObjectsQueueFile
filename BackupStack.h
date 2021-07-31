//
// Created by dmitry on 31.07.2021.
//

#ifndef OBJECTSQUEUEFILE_BACKUPSTACK_H
#define OBJECTSQUEUEFILE_BACKUPSTACK_H


#include <cstdint>
#include "StackList.h"


struct FileField {
    int64_t start;
    int64_t size;
};


class BackupStack  {
    StackList <FileField> stackList;
public:
    void push (FileField fileField);
    FileField pop ();

};


#endif //OBJECTSQUEUEFILE_BACKUPSTACK_H
