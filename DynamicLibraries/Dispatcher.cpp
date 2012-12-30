//
// Dispatcher.cpp
// DynamicLibraries
//
// Created by Patricio Cano on 12/22/12.
// Copyright (c) 2012 Patricio Cano. All rights reserved.
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
    std::cerr << name << std::endl;
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
        return new Dispatcher();
    }
}

Dispatcher *getDispatcherObjectCPP() {
    return new Dispatcher();
}

Interface* Dispatcher::getInstance(const char *name, const char *param){
    std::cerr << "We are loading the dylib." << std::endl;
    return loadLibrary(local_name);
}



Dispatcher* Dispatcher::instance = 0;

Dispatcher::Dispatcher() {
}

Dispatcher::Dispatcher(std::string name, std::string param){
    Dispatcher::local_name = strdup(name.c_str());
    Dispatcher::local_param = strdup(param.c_str());
    
    std::cerr << "We have a loaded lib in Dispatcher." << std::endl;
}



/**
 * Initalize the registered builder from the config file.
 * But be carefull, all registered builder will be overwritten.
 *
 * @param configFile
 */

void Dispatcher::Initialize(const char *configFile) {
    Config *cfg = new Config(configFile);
    std::vector<std::string *>::iterator it = cfg->fileVector.begin();
    for( ; it != cfg->fileVector.end(); ++it){
        int posEqual = (*it)->find(" : ");
        std::string subName;
        std::string subPara;        
        
        subName = (*it)->substr(0, posEqual);
        subPara = (*it)->substr(posEqual + 3, (*it)->size() - 1);
        Dispatcher* obj = new Dispatcher(subName, subPara);
        this->RegisterBuilder(obj);
        
    }
}

/**
 * Register new InterfaceBuilder to the Dispatcher
 *
 *
 * @param builder
 */


void Dispatcher::RegisterBuilder(InterfaceBuilder *builder) {
    Dispatcher::builders.push_back(builder);
}

bool Dispatcher::open(const char *name, const char *param) {
    Interface* inf = this->getInterface(this->local_name, this->local_param);
    return inf->open(name, param);
}

bool Dispatcher::close() {
    Interface* inf = this->getInterface(this->local_name, this->local_param);
    return inf->close();
    
}

size_t Dispatcher::read(void *buffer, size_t count) {
    Interface* inf = this->getInterface(this->local_name, this->local_param);
    return inf->read(buffer, count);
}

size_t Dispatcher::write(const void *buffer, size_t count) {
    Interface* inf = this->getInterface(this->local_name, this->local_param);
    return inf->write(buffer, count);
}

Interface* Dispatcher::getInterface(const char *name, const char *param) {
    Interface* ifb;
    std::cerr << "We begin to load external lib." << std::endl;
    for (std::vector<InterfaceBuilder *>::iterator it = builders.begin(); it != builders.end(); it++) {
        std::cerr << "We are in the loop looking for dylib." << std::endl;
        ifb = (*it)->getInstance(name, param);
        
        // in c++0x nullptr is possible...
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
