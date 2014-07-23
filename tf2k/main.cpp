#include <iostream>
#include "libfb2k.h"

int main(int argc, char **argv)
{
	std::cout << "libfb2k version : " << LIBFB2K_VERSION << std::endl;

	std::cout << "Arguments >" <<std::endl;
	for (int i = 0; i < argc; i++)
	{
		std::cout << '\t' << i << " : " << argv[i] <<std::endl;
	}

	return 0;
}
