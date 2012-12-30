//
// Config.h
// DynamicLibraries
//
// Created by Patricio Cano on 12/28/12.
// Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#ifndef DynamicLibraries_Config_h
#define DynamicLibraries_Config_h
#include <string>
#include <vector>

class Config {
public:
    Config(const char *configFile);
    virtual ~Config();
    std::vector<std::string *> fileVector;
    std::string *getFiles();
private:
    
};



#endif