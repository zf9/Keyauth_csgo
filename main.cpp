#include "Login.h"

int main()
{
	SetConsoleTitleA(XorStr("Loader Name").c_str());
	int LoginBool = 1;


	ConnectingStatus();

	if (LoginBool == 1)
	{
		LoginKey();
	}
	else if (LoginBool == 2)
	{
		LoginUserPass();
	}

	Sleep(-1);
}
