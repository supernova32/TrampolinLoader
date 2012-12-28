//
//  Config.h
//  DynamicLibraries
//
//  Created by Patricio Cano on 12/28/12.
//  Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#ifndef DynamicLibraries_Config_h
#define DynamicLibraries_Config_h
#include <string>

class Config {
public:
    Config(const char *configFile);
    Config(const Config& orig);
    virtual ~Config();
    char fileArr[32];
    std::string *getFiles();
private:
    
};



#endif
