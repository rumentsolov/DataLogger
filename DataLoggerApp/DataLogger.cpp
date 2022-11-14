#include "DataLogger.h"

#include <atlbase.h> 


#include "trend.h"


using namespace System;
using namespace System::Windows::Forms;

int main(array<String^>^ arr) {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	DataLoggerApp::DataLogger frm;
	Application::Run(% frm);
	return 0;
}

int CALLBACK WinMain(
    __in  HINSTANCE hInstance,
    __in  HINSTANCE hPrevInstance,
	__in  LPSTR lpCmdLine,
    __in  int nCmdShow )

{
    return main(nullptr);
}

