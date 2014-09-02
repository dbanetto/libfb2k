#include <iostream>

#include "libfb2k/libfb2k.h"
#include "libfb2k/Block.h"

int main(int argc, char **argv)
{
	std::cout << "libfb2k version : " << LIBFB2K_VERSION << std::endl;

	std::cout << "Arguments >" <<std::endl;
	for(int i = 0; i < argc; i++) {
		fb2k::Block blk = fb2k::Block("$if(true,then,$grt(n,n)else) %var% + $not(true) Get your at for the \\$10 fool()");
		std::cout << '\t' << i << " : " << argv[i] <<std::endl;
		std::cout << '\t' << blk.getStatement() << std::endl;
	}

	return 0;
}
