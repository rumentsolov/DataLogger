#ifndef GETDESKTOPPATH_H
#define GETDESKTOPPATH_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <shlobj.h>
#include "ActionLogger.h"

std::string GetDTPath()
{
    std::string buffer;

    TCHAR appData[MAX_PATH];

    if (SUCCEEDED(SHGetFolderPath(NULL,
        CSIDL_FLAG_CREATE,
        NULL,
        SHGFP_TYPE_CURRENT,
        appData)))
    {
        std::wstring wideStr(&appData[0]); //convert to wstring
        std::string buf(wideStr.begin(), wideStr.end()); //and convert to string.

        buffer = buf + "\\";

        //ActionSave(buffer);
    }

    if (buffer != "\\") {
        return buffer;
    }
    else {
        // DESKTOP NOT FOUND
  
    }
    return buffer;
}

#endif 
