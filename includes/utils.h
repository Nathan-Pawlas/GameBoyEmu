#pragma once
#include <stdint.h>
#include <iostream>
#include <map>


#define NO_IMPL {std::clog << "NOT YET IMPLEMENTED" << std::endl; exit(-5);}

#define BIT(a,n) ((a & (1 << n)) ? 1 : 0)
#define BIT_SET(a, n, on) { if (on) a |= (1 << n); else a &= ~(1 << n); }