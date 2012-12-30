//
//  main.cpp
//  TrampolinLoader
//
//  Created by Patricio Cano on 12/13/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#include <iostream>
#include "../DynamicLibraries/Dispatcher.h"
#include <dlfcn.h>

int main(int argc, const char * argv[])
{

    void *handle = dlopen("libDispatcher.dylib", RTLD_NOW);
    if ( handle == NULL ) {
        std::cerr << dlerror() << std::endl;
        exit(1);
    }
    std::cerr << "Dispatcher loaded at address: " << handle << std::endl;
    
    Dispatcher *(*factory)();
    
    *((void **)&factory) = dlsym(handle, "getDispatcherObjectC");
    
    if ( factory == NULL ) {
        std::cerr << dlerror() << std::endl;
        exit(1);
    }
    
    std::cerr << "Function from Dispatcher loaded at address: " << ((void *)factory) << std::endl;
    Dispatcher *object = (*factory)();
    std::cerr << "Dispatcher Object loaded at address: " << ((void *)object) << std::endl;
    object->Initialize("/Users/pato/Studium/HFT/Sem\ 4/PROG3/TrampolinLoader/TrampolinLoader/config.txt");
    object->open("me", "you");
    object->close();
    return 0;
}

