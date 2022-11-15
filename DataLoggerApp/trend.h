#ifndef TREND_H
#define TREND_H

#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "GlobalVariables.h"
#include "ActionLogger.h"
#include "Record.h"
#include "ComInit.h"
#include "Processment.h"


int run()
{

    // OPERATING WITH INFO FROM CSV FILE AND CREATE RAW TXT FILE TO PROCESSING WITH

    std::ofstream rawFileStream(rawFile, std::ofstream::binary); // op Stream for raw file

    ComInit init;
    CComPtr<IStream> pStream; // use CComPtr so you don't have to manually call Release()
    HRESULT hr = URLOpenBlockingStreamW(nullptr, L"https://www.rumentsolov.com/gallery/trend.csv", &pStream, 0, nullptr);// Open the HTTP request
    if (FAILED(hr))
    {
        //MessageBox::Show("ERROR: Could not connect. HRESULT: 0x");
        return 1;
    }

    // Download the response and write it to file. Since I don't know how exactly the ComInit splits the stream (Google helped me here) , I write it to txt file and then I work with my file 
    char buffer[128];
    do
    {
        DWORD bytesRead = 0;
        hr = pStream->Read(buffer, sizeof(buffer), &bytesRead);
        if (bytesRead > 0) rawFileStream.write(buffer, bytesRead);

    } while (SUCCEEDED(hr) && hr != S_FALSE);

    if (FAILED(hr))
    {
        //MessageBox::Show("ERROR: Download failed. HRESULT: 0x");
        return 2;
    }

    ActionSave(rawFileString);

    operateTXTFile(); 
    

    return 0;
}


#endif 