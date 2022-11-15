#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "GetDesktopPath.h"

std::string  deskTopPath = GetDTPath();
std::string  pathStr = deskTopPath.c_str();
std::string  rawName = "rawfile.txt";
std::string  recordName = "record.txt";

std::string rawFileString = pathStr + rawName;
std::string recordFileString = pathStr + recordName;


const char* rawFile = rawFileString.c_str();
const char* recordFile = recordFileString.c_str();
const char* inputFile = "https://www.rumentsolov.com/gallery/trend.csv";

#endif #pragma once
