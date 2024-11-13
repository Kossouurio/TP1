#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Gun.h"

int main()
{
    bool running = true;

	Gun gun(6, 120, false, false, 0.5f, 0.2f, 0.0f, 0.0f);
	
	float Deltatime = 0.1f;

    while (running)
    {
		gun.Update(Deltatime);
		gun.HandleInput();
        Sleep(500);
    }
    return 0;
}

