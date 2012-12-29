//
//  Dispatcher.cpp
//  DynamicLibraries
//
//  Created by Patricio Cano on 12/22/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#include "Dispatcher.h"
#include "Config.h"
#include <string>
#include <cstdlib>
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
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

extern "C" {
    Dispatcher *getDispatcherObjectC() {
        return new Dispatcher("libTypeA.dylib", "0");//<- added to test. must be removed once config is working
    }
}

Interface* Dispatcher::getInstance(const char *name, const char *param){
    std::cerr << "We are loading the dylib." << std::endl;
    return loadLibrary(name);
}



Dispatcher* Dispatcher::instance = 0;
std::vector<InterfaceBuilder *> Dispatcher::builders = *new std::vector<InterfaceBuilder *>();

Dispatcher::Dispatcher() {
}

Dispatcher::Dispatcher(const char *name, const char *param){
    local_name = name;
    local_param = param;
    builders.insert(builders.begin(), this);//<- added to test. must be removed once config is working
    local_interface = this->getInterface(local_name, local_param);
    std::cerr << "We have a loaded dylib." << std::endl;
}

/**
 * Initalize the registered builder from the config file.
 * But be carefull, all registered builder will be overwritten.
 *
 * @param configFile
 */

static void Initialize(const char *configFile) {
    Config cfg = *new Config(configFile);
    
    for (int i = 0; i < ARRAY_SIZE(cfg.fileArr); i++) {
        //this needs checking!!
        InterfaceBuilder* obj = new Dispatcher(&cfg.fileArr[i], &cfg.fileArr[i]); //<--- Params and name from config should be here!!
        Dispatcher::RegisterBuilder(obj);        
    }
}

/**
 * Register new InterfaceBuilder to the Dispatcher
 *
 *
 * @param builder
 */


static void RegisterBuilder(InterfaceBuilder *builder) {
    Dispatcher::builders.push_back(builder);
}

bool Dispatcher::open(const char *name, const char *param) {
    return local_interface->open(name, param);
}

bool Dispatcher::close() {
    return local_interface->close();
    
}

size_t Dispatcher::read(void *buffer, size_t count) {
    return local_interface->read(buffer, count);
}

size_t Dispatcher::write(const void *buffer, size_t count) {
    return local_interface->write(buffer, count);
}

Interface* Dispatcher::getInterface(const char *name, const char *param) {
    Interface* ifb;
    std::cerr << "We begin to load external lib." << std::endl;
    for (std::vector<InterfaceBuilder *>::iterator it = builders.begin(); it != builders.end(); ++it) {
        std::cerr << "We are in the loop looking for dylib." << std::endl;
        ifb = (*it)->getInstance(name, param);
        if (ifb != nullptr){
            return ifb;
            break;            
        }
    }    
    if (ifb == nullptr)
        exit(1);
    return ifb;    
}

//this might no be necessary
Dispatcher& Dispatcher::getDispatcherInstance() {
    if (!Dispatcher::instance)
        instance = new Dispatcher();
     return *instance;     
    
}

//it doesn't work for some reason.
//void destroy() {
//    delete Dispatcher::instance;
//}
