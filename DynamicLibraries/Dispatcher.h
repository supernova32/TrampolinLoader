//
//  Dispatcher.h
//  DynamicLibraries
//
//  Created by Patricio Cano on 12/13/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#include "Interface.h"
#include <iostream>
#include <vector>
#ifndef DynamicLibraries_Dispatcher_h
#define DynamicLibraries_Dispatcher_h

class Dispatcher: public InterfaceBuilder {
    
private:
//    Dispatcher();
//    
//    static Dispatcher* instance;
//    Dispatcher(const Dispatcher&);
//    ~Dispatcher();
    
public:
    Dispatcher();
    Dispatcher(const char *name, const char *param);
    
    Interface *getInstance(const char *name, const char *param);
    
    static Dispatcher* instance;
    Dispatcher(const Dispatcher&);
    ~Dispatcher();
    
    // given funktions
    virtual void Initialize(const char *configFile);
    virtual void RegisterBuilder(InterfaceBuilder *builder);
    virtual bool open(const char *name, const char *param);
    virtual bool close();
    virtual size_t read(void *buffer, size_t count);
    virtual size_t write(const void *buffer, size_t count);
    
    // new
    Interface* getInterface(const char *name, const char *param);
    static std::vector<InterfaceBuilder *> builders;
    const char *local_name;
    const char *local_param;
    Interface* local_interface;
    
    // Singelton
    static Dispatcher& getDispatcherInstance();
    //static void destroy();
    
//public:
//    static void Initialize(const char *configFile);
//    static void RegisterBuilder(InterfaceBuilder *builder);
//    Dispatcher();
//    bool open(const char *name, const char *param);
//    bool close();
//    size_t read(void *buffer, size_t count);
//    size_t write(const void *buffer, size_t count);
};


#endif
