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
        
public:
    Dispatcher();
    Dispatcher(std::string name, std::string param);
    
    Interface *getInstance(const char *name, const char *param);
    
    static Dispatcher* instance;
    Dispatcher(const Dispatcher&);
    ~Dispatcher();
    
    virtual void Initialize(const char *configFile);
    virtual void RegisterBuilder(InterfaceBuilder *builder);
    virtual bool open(const char *name, const char *param);
    virtual bool close();
    virtual size_t read(void *buffer, size_t count);
    virtual size_t write(const void *buffer, size_t count);
    
    Interface* getInterface(const char *name, const char *param);
    std::vector<InterfaceBuilder *> builders;
    const char *local_name;
    const char *local_param;
    Interface* local_interface;
    
    virtual Dispatcher& getDispatcherInstance();
};


#endif
