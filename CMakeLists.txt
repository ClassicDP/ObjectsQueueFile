cmake_minimum_required(VERSION 3.19)
project(ObjectsQueueFile)

set(CMAKE_CXX_STANDARD 14)

add_executable(ObjectsQueueFile json.hpp DynamicArray.h QueueObject.cpp QueueObject.h main.cpp QueueFile.cpp QueueFile.h StackList.h BaseHeader.h)