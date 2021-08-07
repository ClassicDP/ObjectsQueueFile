#include <iostream>
#include "QueueObject.h"
#include "QueueFile.h"


int main() {
    QueueFile queueFile ("123.db");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !");
    queueFile.push("Hello, World!  !0");

    std::cout << queueFile.pull() << std::endl;
    std::cout << queueFile.pull() << std::endl;
    std::cout << queueFile.pull() << std::endl;
    std::cout << queueFile.pull() << std::endl;
    std::cout << queueFile.pull() << std::endl;
    std::cout << queueFile.pull() << std::endl;
    std::cout << queueFile.pull() << std::endl;
    std::cout << queueFile.pull() << std::endl;
    return 0;
}
