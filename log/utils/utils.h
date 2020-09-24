#ifndef __PHOENIX_HEADER_UTILS_H
#define __PHOENIX_HEADER_UTILS_H

#include <iostream>
#include <fstream>
#include <vector>

#include "types.h"

namespace Phoenix {

class Utils
{
public:
    
///////////////////////////////////////////////////////////////////////////////
/// File Operations
///////////////////////////////////////////////////////////////////////////////


// vector<string> str_vec; print_vec(str_vec);
template <typename T>
static void printVector(std::vector<T>* vec)
{
    // std::cout << "Print vector<" << typeid(vec).name() << ">" << std::endl;
    std::cout << "print vector: ";
    typename std::vector<T>::iterator iter = vec->begin();
    while (iter != vec->end()) {
        std::cout << *iter++ << "  ";
    }
    std::cout << std::endl;
}

template <typename T>
static void printVector(std::vector<T> &vec)
{
    std::cout << "打印vector: ";
    typename std::vector<T>::iterator iter = vec.begin();
    while (iter != vec.end()) {
        std::cout << *iter++ << "\t";
    }
    std::cout << std::endl;
}


private:
    /* data */
    Utils(/* args */) = default;
};





}


#endif