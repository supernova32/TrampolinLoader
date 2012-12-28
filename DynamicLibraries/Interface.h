//
//  Interface.h
//  DynamicLibraries
//
//  Created by Patricio Cano on 12/13/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#include <iostream>
#ifndef DynamicLibraries_Interface_h
#define DynamicLibraries_Interface_h

class Interface {
public:
    virtual bool open(const char *name, const char *param) = 0;
    virtual bool close() = 0;
    virtual size_t read(void *buffer, size_t count) = 0;
    virtual size_t write(const void *buffer, size_t count) = 0;
};

class InterfaceBuilder {
public:
    virtual Interface *getInstance(const char *name, const char *param) = 0;
};



#endif
