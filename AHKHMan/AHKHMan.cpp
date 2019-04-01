// AHKHMan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <msclr/marshal_cppstd.h>
using namespace msclr::interop;

#include "pch.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;



int main()
{
	char a[10] = "";

	cout << "=== AHK_H Manager by scadl===\n\nStarting Autohotkey.DLL Link..\n";

	HINSTANCE handle = LoadLibrary(L"AutoHotkey.dll");

	typedef UINT (*pahkdll)(LPCWSTR script, LPCWSTR p1, LPCWSTR p2);
	typedef BOOL (*pAhkExec)(LPCWSTR msg);
	typedef BOOL (*pahkReady)(void);
	typedef IntPtr (*pGetVar)(LPCWSTR varName, bool VP);

	if (handle == NULL){
		Sleep(10);
		DWORD err = GetLastError();
		cerr << "DLL Link Error: " << err << "\n";
	}
	else 
	{
		
		cout << "Autohotkey.DLL Link OK!\n\nRunning Functions init...\n";

		pahkdll ahkdll = (pahkdll)GetProcAddress(handle, "ahkdll");
		pAhkExec AhkExec = (pAhkExec)GetProcAddress(handle, "AhkExec");
		pahkReady ahkReady = (pahkReady)GetProcAddress(handle, "ahkReady");
		pGetVar ahkGetVar = (pGetVar)GetProcAddress(handle, "ahkgetvar");

		cout << "Functions initalized: ahkdll, ahkexec, ahkready.\n\n";
		
		if (AhkExec!=NULL) {
			
			cout << "Cleaning memomry space.\n";
			ahkdll(L"", L"", L"");

			while (!ahkReady()) {
				Sleep(10);
			}
			cout << "AHK core load finished.\n\nLunching AHK script...\n";

			AhkExec(L"MyVar := InputBox(\"HI i am an ahk script runinned by C++ app! Type something to the input box to send my parent\", \"Dynamic AHK\")");
			if (ahkGetVar != NULL) {				
				IntPtr varPtr = ahkGetVar(L"MyVar", false);
				String^ strVar = Marshal::PtrToStringAuto(varPtr);
				//string outVar = marshal_as< string >(strVar);
				//cout << "Got data from AHK thread: " << to_string(strVar) << endl;
				//Console::WriteLine("Got data from AHK thread: {0}", strVar);
			} else {				
				DWORD err = GetLastError();
				cout << "ahkGetVar not working: " << err << "\n";
			}

		}
		else
		{
			DWORD err = GetLastError();
			cout << "ahkExec error:" << err << "\n";
		}
		
	}

    cout << "AHK execution finished\nTank you for using my ahk controller!\n"; 
	cin >> a;
}
