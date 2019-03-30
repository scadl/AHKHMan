// AHKHMan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	char a[10] = "";

	cout << "=== AHK_H Manager by scadl===\nStarting Autohotkey.DLL Link..\n";

	HINSTANCE handle = LoadLibrary(L"AutoHotkey.dll");

	typedef UINT (*pahkdll)(LPCWSTR script, LPCWSTR p1, LPCWSTR p2);
	typedef BOOL (*pAhkExec)(LPCWSTR msg);
	typedef BOOL (*pahkReady)(void);

	if (handle == NULL){
		Sleep(10);
		DWORD err = GetLastError();
		cerr << "DLL Link Error: " << err << "\n";
	}
	else 
	{
		
		cout << "Autohotkey.DLL Link OK!\nRunning Functions init...\n";

		pahkdll ahkdll = (pahkdll)GetProcAddress(handle, "ahkdll");
		pAhkExec AhkExec = (pAhkExec)GetProcAddress(handle, "AhkExec");
		pahkReady ahkReady = (pahkReady)GetProcAddress(handle, "ahkReady");

		cout << "Functions initalized: ahkdll, ahkexec, ahkready.\n";
		
		if (AhkExec!=NULL) {
			
			cout << "Cleaning memomry space...\n";
			ahkdll(L"", L"", L"");

			while (!ahkReady()) {
				Sleep(10);
			}
			cout << "AHK core load finished.\nLunching AHK script...\n";

			AhkExec(L"MsgBox(\"HI i am an ahk script runinned by C++ app!\", \"Dynamic AHK\", \"OK\")");
		}
		else
		{
			DWORD err = GetLastError();
			cout << "External func error:" << err << "\n";
		}
		
	}

    cout << "AHK execution finished\nTank you for using my ahk controller!\n"; 
	cin >> a;
}
