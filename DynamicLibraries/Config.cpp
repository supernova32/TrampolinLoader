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
        outputFile << "//Use \"//\" to mark a comment.\n";
        outputFile.close();
        
        
        cout << "\nDone...\n";
        
    } else {
        
        cout << "Loading propertys...\nContent:\n";
        
        ifstream ifs(configFile);
        
        string temp;
        
        int i = 0;
        
        // read file line by line
        while (getline(ifs, temp)) {
            
            string sub;
            int pos = temp.find("//");
            
            
            // Exclude kommentar
            if ((pos > 0) && !(temp == "")) {
                cout << i << ": " << temp << ".\n";
                this->fileVector.push_back(&temp);
                
                i=i+2;
                
            } else
                if ((pos < 0) && !(temp == "")) {
                    // if pos = -1 ther is no kommentar
                    cout << i << ": " << temp << ".\n";
                    
                    int posEqual = temp.find(" : ");
                    
                    this->fileVector.push_back(&temp);
                    
                    i=i+2;
                }
            
        }
        
        
        
        cout << "\n";
        fclose(pFile);
        cout << "Closing file...\n";
        
    }
    
    
}


Config::~Config() {
}