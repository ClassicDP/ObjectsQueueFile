cmake_minimum_required(VERSION 3.19)
project(ObjectsQueueFile)

set(CMAKE_CXX_STANDARD 14)

add_executable(ObjectsQueueFile main.cpp QueueFile.cpp QueueFile.h FileHeader.cpp FileHeader.h LoopDiskArray.cpp LoopDiskArray.h BackupStack.cpp BackupStack.h StackList.cpp StackList.h)