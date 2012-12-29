//
// Config.cpp
// DynamicLibraries
//
// Created by Patricio Cano on 12/28/12.
// Copyright (c) 2012 Patricio Cano. All rights reserved.
//

#include "Config.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>

using namespace std;

Config::Config(const char *configFile) {
    
    FILE * pFile;
    
    pFile = fopen(configFile, "r");
    if (pFile == NULL) {
        perror("Error opening property file");
        cout << "\nCreating and writing default property.\n";
        
        ofstream outputFile;
        outputFile.open(configFile);
        
        outputFile << "Property .//File\n";
        outputFile << "//Use this File to setup the lib\n";
        outputFile << "//Use \"//\" to mark an kommentar.\n";
        outputFile.close();
        
        
        cout << "\nDone...\n";
        
    } else {
        
        cout << "Loading propertys...\nContent:\n ------ \n\n";
        
        ifstream ifs(configFile);
        
        string temp;
        
        int i = 0;
        
        // read file line by line
        while (getline(ifs, temp)) {
            
            string sub;
            int pos = temp.find("//");
            
            
            // Exclude kommentar
            if ((pos > 0) && !(temp == "")) {
                // if pos > 0 ther is a kommentar in this line
                // del kommentar
                sub = temp.substr(0, pos);
                
                cout << i << ": " << sub << ".\n";
                
                int posEqual = sub.find(" = ");
                
                string subName;
                string subPara;
                
                subName = sub.substr(0, posEqual);
                char *tmp = new char[subName.size() + 1];
                tmp[subName.size()] = 0;
                memcpy(tmp, subName.c_str(), subName.size());
                fileArr[i] = *tmp;
                
                
                
                subPara = sub.substr(posEqual, sub.size() - 1);
                char *sb = new char[subPara.size() + 1];
                sb[subPara.size()] = 0;
                memcpy(sb, subPara.c_str(), subPara.size());
                fileArr[i+1] = *sb;
                
                i=i+2;
                
            } else
                if ((pos < 0) && !(temp == "")) {
                    // if pos = -1 ther is no kommentar
                    cout << i << ": " << temp << ".\n";
                    
                    int posEqual = temp.find(" = ");
                    
                    string subName;
                    string subPara;
                    
                    
                    
                    subName = temp.substr(0, posEqual);
                    char *tmp = new char[subName.size() + 1];
                    tmp[subName.size()] = 0;
                    memcpy(tmp, subName.c_str(), subName.size());
                    fileArr[i] = *tmp;
                    
                    
                    
                    subPara = temp.substr(posEqual, temp.size() - 1);
                    char *sb = new char[subPara.size() + 1];
                    sb[subPara.size()] = 0;
                    memcpy(sb, subPara.c_str(), subPara.size());
                    fileArr[i+1] = *sb;
                    
                    i=i+2;
                } // if pos = 0 ther is only kommentar
            
        }
        
        
        
        cout << "\n\n------\n";
        fclose(pFile);
        cout << "Closing file...\n";
        
    }
    
    
}

const char stringToChar(std::string temp) {
    
    char *tmp = new char[temp.size() + 1];
    tmp[temp.size()] = 0;
    memcpy(tmp, temp.c_str(), temp.size());
    
    return *tmp;
}

Config::Config(const Config& orig) {
}

Config::~Config() {
}