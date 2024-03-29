project(UtilEase)
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

link_libraries(pthread rt m)

AUX_SOURCE_DIRECTORY(. src)
AUX_SOURCE_DIRECTORY(log src)
AUX_SOURCE_DIRECTORY(locker src)
ADD_EXECUTABLE(main ${src})