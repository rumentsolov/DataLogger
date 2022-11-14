#ifndef TREND_H
#define TREND_H

#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
        //"ERROR: Could not connect. HRESULT: 0x"
        return 1;
    }

    // Download the response and write it to file.
    char buffer[128];
    do
    {
        DWORD bytesRead = 0;
        hr = pStream->Read(buffer, sizeof(buffer), &bytesRead);
        if (bytesRead > 0) rawFileStream.write(buffer, bytesRead);

    } while (SUCCEEDED(hr) && hr != S_FALSE);

    if (FAILED(hr))
    {
        //"ERROR: Download failed. HRESULT: 0x"
        return 2;
    }


    //"Job Done!" ;

    return 0;
}


#endif 