// AHKHMan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

using namespace std;
using namespace System;

using namespace AutoHotkey;

int main()
{
	char a[10] = "";

	cout << "=== AHK_H Manager by scadl===\n\n";
	cout << "Searching for AutoHotkey COM Link..\n";

	CoCOMServerClass^ myThread = gcnew CoCOMServerClass;		
	cout << "Autohotkey Interface OK!\n";
		
	cout << "Cleaning memomry space.\n";
	myThread->ahkdll("", "", "");

	while (!myThread->ahkReady()) {
		Sleep(10);
	}
	cout << "AHK core load finished.\n\n";
			
	cout << "Lunching AHK script...\n";
	myThread->ahkExec("MyVar := InputBox(\"HI i am an ahk script runinned by C++ app! `nType something to the input box to send my parent\", \"Dynamic AHK\")");
						
	Object^ varPtr = myThread->ahkgetvar("MyVar", FALSE);
	String^ outVar = varPtr->ToString();
	Console::WriteLine("Got data from AHK thread: {0}", outVar);	
			
	cout << "AHK execution finished\n";
	cout << "Thank you for using my ahk controller!\n";
	cin >> a;
}
