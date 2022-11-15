#ifndef COMINI_H
#define COMINI_H

#include <Windows.h>
#include <Urlmon.h>   // for URLOpenBlockingStreamW()
#include <atlbase.h>  // for CComPtr
#include <iostream>
#pragma comment( lib, "Urlmon.lib" )


struct ComInit
{
    HRESULT hr;
    ComInit() : hr(::CoInitialize(nullptr)) {}
    ~ComInit() { if (SUCCEEDED(hr)) ::CoUninitialize(); }
};

#endif 