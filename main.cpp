#include <iostream>
#include "QueueObject.h"
#include "QueueFile.h"


int main() {
    QueueFile queueFile ("123.db");
    queueFile.push("Hello, World! 1 !");
    queueFile.push("Hello, World! 2 !");
    queueFile.push("Hello, World! 3 !");
    queueFile.push("Hello, World! 4 !");
    queueFile.push("Hello, World! 5 !");
    queueFile.push("Hello, World! 6 !");
    queueFile.push("Hello, World! 7 !");
    queueFile.push("Hello, World! 8 !");

    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    return 0;
}
