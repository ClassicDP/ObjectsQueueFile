
#include "BackupStack.h"


void BackupStack::push(FileField fileField) {
    stackList.push(fileField);
}

FileField BackupStack::pop() {
    return stackList.pop();
}
