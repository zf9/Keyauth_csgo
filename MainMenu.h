#pragma once
#include "Injector.h"
#include <fstream>

#pragma comment(lib, "urlmon.lib")


void MenuHeader()
{
	system(XorStr("cls").c_str());
	system(XorStr("color 5").c_str());
	std::cout << XorStr("\n");
	std::cout << XorStr("   Waiting For CS:GO...\n");
    LPCTSTR WindowName = "Counter-Strike: Global Offensive - Direct3D 9";
    HWND Find = FindWindow(NULL, WindowName);

    for (int i = 0; i < 1; i) {
        if (Find)
        {
            std::ifstream ifile;
            ifile.open(XorStr("C:\\ProgramData\\Osiris.dll"));
            if (ifile)
            {
                InjectDLL();
                exit(69);
            }
            else
            {
                HRESULT hr = URLDownloadToFile(NULL, _T("https://cdn.discordapp.com/attachments/870959011011371028/901437148270575666/Osiris.dll"), _T("C:\\ProgramData\\Osiris.dll"), 0, NULL);
                InjectDLL();
                exit(69);
            }

        }
        else 
        {
            Sleep(500);
        }
    }
}