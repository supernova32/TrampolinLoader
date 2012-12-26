//
//  TypeA.cpp
//  DynamicLibraries
//
//  Created by Patricio Cano on 12/22/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#include "TypeA.h"
#include "Interface.h"

extern "C" {
    Interface *getInterfaceObjectC() {
        return new TypeA();
    }
}

Interface *getInterfaceObjectCPP() {
    return new TypeA();
}

bool TypeA::open(const char *name, const char *param){
    std::cout
    << "Hello i am TypeA: open methode. Name: " << name
    << " Parameter: " << param;
    return true;    
}

bool TypeA::close(){
    std::cout
    << "Hello i am TypeA: close methode.";
    return true;    
}

size_t TypeA::read(void *buffer, size_t count){
    std::cout
    << "Hello i am TypeA: read methode. Count: " << count;
    
}

size_t TypeA::write(const void *buffer, size_t count){
    std::cout
    << "Hello i am TypeA: write methode. Count: " << count;
    
}

