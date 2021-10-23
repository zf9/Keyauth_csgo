#include "api/KeyAuth.hpp"
#include "MainMenu.h"
#include <iostream>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include "xorstr.hpp"
using namespace KeyAuth;

std::string name = XorStr("Loader");
std::string ownerid = XorStr("WkY5IzEyMTQ=");
std::string secret = XorStr("SW4geW91ciBkcmVhbXMgbmlnZ2VyIG1hbg==");
std::string version = XorStr("1.0");
api KeyAuthApp(name, ownerid, secret, version);

void LoginUserPass()
{
	std::cout << XorStr("\n");
	std::cout << XorStr("   [1] Login\n");
	std::cout << XorStr("   [2] Register\n");
	std::cout << XorStr("   Choose option: ");
	int option;
	std::string username;
	std::string password;
	std::string key;

	std::cin >> option;
	if (option == 1)
	{
		system(XorStr("cls").c_str());
		std::cout << XorStr("\n");
		std::cout << XorStr("   Enter username: ");
		std::cin >> username;
		std::cout << XorStr("   Enter password: ");
		std::cin >> password;
		KeyAuthApp.login(username, password);
	}

	if (option == 2)
	{
		system(XorStr("cls").c_str());
		std::cout << XorStr("\n");
		std::cout << XorStr("   Enter username: ");
		std::cin >> username;
		std::cout << XorStr("   Enter password: ");
		std::cin >> password;
		std::cout << XorStr("   Enter license: ");
		std::cin >> key;
		KeyAuthApp.regstr(username, password, key);
	}
	else
	{
		system(XorStr("cls").c_str());
		LoginUserPass();
	}
}

void LoginKey()
{
	std::string key;
	std::cout << XorStr("\n");
	std::cout << XorStr("   Enter license: ");
	std::cin >> key;
	KeyAuthApp.license(key);
	MenuHeader();
}

void ConnectingStatus()
{
	std::cout << XorStr("\n\n Connecting..");
	KeyAuthApp.init();
	system(XorStr("cls").c_str());
	system(XorStr("color d").c_str());
}