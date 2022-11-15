#include "DataCollector.h"
#include <atlbase.h> 
#include "trend.h"
#include "ActionLogger.h"
#include "GlobalVariables.h"

using namespace System;
using namespace System::Windows::Forms;

int main(array<String^>^ arr) {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	DataCollectorApp::DataCollector frm;
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

