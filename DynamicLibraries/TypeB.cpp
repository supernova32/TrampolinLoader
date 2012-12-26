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

boolean TypeB::open(const char *name, const char *param){
    
}

boolean TypeB::close(){
    
}

size_t TypeB::read(void *buffer, int count){
    
}

size_t TypeB::write(const void *buffer, int count){
    
}
