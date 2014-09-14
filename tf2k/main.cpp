#include <iostream>

#include "libfb2k/libfb2k.h"
#include "libfb2k/Block.h"
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <string.h>

int main(int argc, char **argv)
{
	std::string expr, file;
	bool help = false;
	for(int i = 1; i < argc; i++) {
		if(strcmp(argv[i],"-e") == 0 && i + 1 < argc) {
			expr = std::string(argv[i+1]);
			i += 1;
			continue;
		}
		if(strcmp(argv[i],"-f")  == 0 && i + 1 < argc) {
			file = std::string(argv[i+1]);
			i += 1;
			continue;
		}
		if(strcmp(argv[i],"-h")  == 0) {
			help = true;
		}
	}

	if(!(expr.empty() || file.empty() || help)) {
		TagLib::FileRef f(file.c_str());
		try {
			fb2k::Block blk(expr);
			std::cout << blk.eval(f.tag()->properties()).result << std::endl;
		} catch(fb2k::FB2KError& err) {
			std::cout << "Error : " << err.what() << std::endl;
		}
		return 0;
	}

	std::cout << "tf2k" << std::endl;
	std::cout << "Built with " << LIBFB2K_VERSION << std::endl;
	std::cout << std::endl;
	std::cout << "How to use:" << std::endl;
	std::cout << "\t" << "-e\tExpression" << std::endl;
	std::cout << "\t" << "-f\tFile" << std::endl;
	std::cout << "\t" << "-h\tHelp" << std::endl;
	return 0;
}
