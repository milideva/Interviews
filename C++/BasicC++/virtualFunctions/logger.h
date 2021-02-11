#pragma once
#include <iostream>

#ifdef DOLOG

#define LOG std::cout << __PRETTY_FUNCTION__ <<'\n'

#else

#define LOG

#endif
