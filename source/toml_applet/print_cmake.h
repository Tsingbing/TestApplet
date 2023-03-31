#ifndef PRINT_CMAKE_H
#define PRINT_CMAKE_H
#include <iostream>
#include <sstream>
#include <string>

class PrintCmake
{
public:
    PrintCmake();
    ~PrintCmake();
    void print_cmake_version(void) { std::cout << "cmake version: " << _version << std::endl; }

private:
    static const char *_version;
};

const char *PrintCmake::_version = "3.16.3";

PrintCmake::PrintCmake()
{
    std::cout << "print_cmake constructor" << std::endl;
}

PrintCmake::~PrintCmake()
{
    std::cout << "print_cmake destructor" << std::endl;
}

#endif