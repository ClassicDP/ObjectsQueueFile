#include <iostream>
#include "QueueObject.h"
#include "QueueFile.h"


int main() {
    auto queueFile = QueueFile("123.db");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !0");
    std::cout << queueFile.fileName << std::endl;
    return 0;
}
