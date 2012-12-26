//
//  TypeB.cpp
//  DynamicLibraries
//
//  Created by Patricio Cano on 12/22/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#include "TypeB.h"
#include "Interface.h"

extern "C" {
    Interface *getInterfaceObjectC() {
        return new TypeB();
    }
}

Interface *getInterfaceObjectCPP() {
    return new TypeB();
}

bool TypeB::open(const char *name, const char *param){
    std::cout
    << "Hello i am TypeB: open methode. Name: " << name
    << " Parameter: " << param;
    return true;    
}

bool TypeB::close(){
    std::cout
    << "Hello i am TypeB: close methode.";
    return true;    
}

size_t TypeB::read(void *buffer, size_t count){
    std::cout
    << "Hello i am TypeB: read methode. Count: " << count;
    
}

size_t TypeB::write(const void *buffer, size_t count){
    std::cout
    << "Hello i am TypeB: write methode. Count: " << count;
    
}
