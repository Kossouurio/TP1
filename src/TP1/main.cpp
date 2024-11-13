#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Gun.h"

int main()
{
    bool running = true;

	Gun gun(23, 115, false, false, 2.5f, 0.7f, 0.0f, 0.0f);
	float Deltatime = 0.1f;

    while (running)
    {
		gun.Update(Deltatime);
		gun.HandleInput();

        Sleep(500);
    }
    return 0;
}

