//
// Created by Ari Trachtenberg on 3/15/17.
//

#include "myBloom.h"
#include <cstring>
#include <iostream>
#include <string>

myBloom::myBloom(int mm) : Bloom(mm) { filter = new char[length]; memset(filter, '_', length);}

myBloom::myBloom(std::string newFilter) : myBloom(newFilter.length()) { strncpy(filter,newFilter.c_str(),length); }

void myBloom::insert(std::string item) { filter[item[0]%length] = 'X'; }

bool myBloom::exists(std::string item) {
    
    return filter[item[0]%length]=='X';
}
//i added a comment


std::string myBloom::output() { return std::string(filter, length); }

myBloom::~myBloom() { delete[] filter; }
