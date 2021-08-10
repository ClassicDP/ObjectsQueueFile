#include <iostream>
#include "QueueObject.h"
#include "QueueFile.h"

void toLog(std::basic_string<char> str) {
    std::cout <<str << std::endl;
}
template<typename T>
const char* getClassName(T) {
    return typeid(T).name();
}

struct A {} a;


int main() {

    QueueFile queueFile ("123.db");
    std::cout << getClassName(queueFile)<< std::endl;
    queueFile.toLog();
    queueFile.push("Hello, World! 1 !");
    queueFile.toLog();
    queueFile.push("Hello, World! 2 !");
    queueFile.toLog();
    queueFile.push("Hello, World! 3 !");
    queueFile.toLog();
    queueFile.push("Hello, World! 4 !");
    queueFile.toLog();
    queueFile.push("Hello, World! 5 !");
    queueFile.toLog();
    queueFile.push("Hello, World! 6 !");
    queueFile.toLog();
    queueFile.push("Hello, World! 7 !");
    queueFile.toLog();

    queueFile.push("Hello, World! 8 !");
    queueFile.toLog();

    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    queueFile.toLog();
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    queueFile.toLog();
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    queueFile.toLog();
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    queueFile.toLog();
    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    queueFile.toLog();

    queueFile.push("Hello, World! 9 !");
    queueFile.toLog();

    queueFile.push("Hello, World! 10 !");
    queueFile.toLog();

    queueFile.push("Hello, World! 11 !");
    queueFile.toLog();

    queueFile.push("Hello, World! 12 !");
    queueFile.toLog();

    queueFile.push("Hello, World! 13 !");
    queueFile.toLog();

    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    queueFile.toLog();

    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    queueFile.toLog();

    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    queueFile.toLog();

    std::cout << queueFile.pull() <<" " << queueFile.getHeader().objectsCount<< std::endl;
    queueFile.toLog();


    return 0;
}
