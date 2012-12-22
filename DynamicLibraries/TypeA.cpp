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
