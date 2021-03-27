//Go to properties > linker > advanced > change Entry Point to "main"
//Go to linker > system > change subsystem to "windows"
#include "stdafx.h"
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	NASmonitor::MyForm form;
	Application::Run(% form);
}