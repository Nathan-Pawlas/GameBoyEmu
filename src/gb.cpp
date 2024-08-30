#include "gb.h"
#include "mmu.h"

int gb::emu_run(int argc, char* argv[])
{
	//Check for ROM File
	/*if (argc < 2)
	{
		std::cout << "Incorrect Usage: \n" << "   ./GBEmu <path_rom_file>\n" << std::endl;
		return -1;
	}*/

	//Try Loading ROM into Cartridge

	//Initialize Componenets (SDL, TTF, CPU)
	SDL_Init(SDL_INIT_VIDEO);
	cpu cpu;
	mmu mem;
	cpu.init(&mem);
	cpu.step();
	exit(0);
	if (!mem.load_rom(argv[1]))
	{
		printf("Failed to load ROM: %s\n", argv[1]);
		return -1;
	}

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
			std::cerr << "Halting: CPU not implemented" << std::endl;
			return -1;
		}

		ticks += 1;
	}

	return 0;
}