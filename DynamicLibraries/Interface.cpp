//
//  Interface.cpp
//  DynamicLibraries
//
//  Created by Patricio Cano on 12/22/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#include "Interface.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
Interface loadLibrary(const char *name){
    HMODULE *handle = LoadLibrary(name);
    if ( handle == NULL ) {
        //TODO: find dlerror equivalent in Windows
        std::cerr << dlerror() << std::endl;
        exit(1);
    }
    std::cerr << "Library loaded at address: " << handle << std::endl;
    
    Interface *(*factory)();
    
    *((void **)&factory) = GetProcAddress(handle, "getInterfaceObjectC");
    
    if ( factory == NULL ) {
        //TODO: find dlerror equivalent in Windows
        std::cerr << dlerror() << std::endl;
        exit(1);
    }
    
    std::cerr << "Function loaded at address: " << ((void *)factory) << std::endl;
    Interface *object = (*factory)();
    std::cerr << "Object loaded at address: " << ((void *)object) << std::endl;
    return object;    
}
#else
#include <dlfcn.h>
Interface* loadLibrary(const char *name){
    void *handle = dlopen(name, RTLD_NOW);
    if ( handle == NULL ) {
        std::cerr << dlerror() << std::endl;
        exit(1);
    }
    std::cerr << "Library loaded at address: " << handle << std::endl;
    
    Interface *(*factory)();
    
    *((void **)&factory) = dlsym(handle, "getInterfaceObjectC");
    
    if ( factory == NULL ) {
        std::cerr << dlerror() << std::endl;
        exit(1);
    }
    
    std::cerr << "Function loaded at address: " << ((void *)factory) << std::endl;
    Interface *object = (*factory)();
    std::cerr << "Object loaded at address: " << ((void *)object) << std::endl;
    return object;    
}
#endif
#include <cstdlib>


Interface* InterfaceBuilder::getInstance(const char *name, const char *param){
    return loadLibrary(name);
}


