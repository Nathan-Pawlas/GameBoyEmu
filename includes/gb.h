#pragma once
#include "utils.h"
#include "cpu.h"
#include <SDL.h>


class gb
{
public:
	int emu_run(int argc, char* argv[]);

	static void cycle(int num);

private:
	bool running;
	bool paused;
	uint64_t ticks;
};
