//
//  Dispatcher.h
//  DynamicLibraries
//
//  Created by Patricio Cano on 12/13/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#include "Interface.h"
#include <iostream>
#ifndef DynamicLibraries_Dispatcher_h
#define DynamicLibraries_Dispatcher_h

class Dispatcher { public:
    static void Initialize(const char *configFile);
    static void RegisterBuilder(InterfaceBuilder *builder);
    Dispatcher();
    bool open(const char *name, const char *param);
    bool close();
    size_t read(void *buffer, size_t count);
    size_t write(const void *buffer, size_t count);
};


#endif
