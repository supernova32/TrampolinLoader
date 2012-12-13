//
//  Dispatcher.h
//  DynamicLibraries
//
//  Created by Patricio Cano on 12/13/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#ifndef DynamicLibraries_Dispatcher_h
#define DynamicLibraries_Dispatcher_h

class Dispatcher { public:
    static Initialize(const char *configFile);
    static RegisterBuilder(InterfaceBuilder *builder);
    Dispatcher();
    boolean open(const char *name, const char *param);
    boolean close();
    size_t read(void *buffer, size_t count);
    size_t write(const void *buffer, size_t count);
};


#endif
