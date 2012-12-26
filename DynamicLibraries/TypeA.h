//
//  TypeA.h
//  DynamicLibraries
//
//  Created by Patricio Cano on 12/13/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#include <iostream>
#include "Interface.h"
#ifndef DynamicLibraries_TypeA_h
#define DynamicLibraries_TypeA_h

class TypeA: public Interface{
    bool open(const char *name, const char *param);
    bool close();
    size_t read(void *buffer, size_t count);
    size_t write(const void *buffer, size_t count);
};



#endif
