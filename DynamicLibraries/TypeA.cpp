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

boolean TypeA::open(const char *name, const char *param){
    
}

boolean TypeA::close(){
    
}

size_t TypeA::read(void *buffer, int count){
    
}

size_t TypeA::write(const void *buffer, int count){
    
}

