
// Bryan Jeremy
// CSC275 C/C++ Programming II
// Assignment: Multi-threading - The Space Race
// 10AUG21

#include "About.h"
#include <iostream>
using namespace std;

void About::appInfo()
{
	cout << "\n\n\t\t*** RockeTTech testing day ***\n\n";

	cout << "\tRockeTTech has been tasked with defending our" << "\n";
	cout << "\tcountry from intercontinental offensive maneuvers." << "\n";
	cout << "\tAs part of their contract requirements, RockeTTech" << "\n";
	cout << "\tsoftware must have a feature that aborts a launch," << "\n";
	cout << "\ta feature that disables further launches and one that" << "\n";
	cout << "\twill transfer launch control in case of emergency." << "\n\n";

	cout << "\tToday... is Space Cadet Opie's first day on the job." << "\n";
	cout << "\tOpie is nestled in his office on the launch pad, " << "\n";
	cout << "\teagerly awaiting today's events.  At the main base," << "\n"; 
	cout << "\this boss Fonzie is hesitant to relinquish control of" << "\n";
	cout << "\tsuch a lucrative contract to the fresh recruit, but" << "\n";
	cout << "\tknows Opie can handle it." << "\n\n";
		
	system("pause >nul | echo. \tContinue...");	// WinOS specific cmd to pause this application
	system("CLS");								// WinOS specific cmd to clear the console
}
