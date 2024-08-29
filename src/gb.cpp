#include "gb.h"

int gb::emu_run(int argc, char* argv[])
{
	//Check for ROM File
	if (argc < 2)
	{
		std::cout << "Incorrect Usage: \n" << "   emu <rom_file>\n" << std::endl;
		return -1;
	}

	//Try Loading ROM into Cartridge

	//Initialize Componenets (SDL, TTF, CPU)
	SDL_Init(SDL_INIT_VIDEO);
	cpu cpu;

	running = true;
	paused = false;
	ticks = 0;

	//Main Loop
	while (running)
	{
		if (paused)
		{
			SDL_Delay(10);
			continue;
		}

		//cpu step
		if (!cpu.step())
		{
			std::cerr << "Halting: CPU error" << std::endl;
			return -1;
		}

		ticks += 1;
	}

	return 0;
}
