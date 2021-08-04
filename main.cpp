#include <iostream>
#include "QueueObject.h"


int main() {
    auto obj = new QueueObject("Hello, World!  !");

    std::cout << obj->setHeader()->size << std::endl;
    return 0;
}
