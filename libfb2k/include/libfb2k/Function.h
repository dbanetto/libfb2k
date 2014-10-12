#ifndef FB2k_FUNCTIONS_H
#define FB2k_FUNCTIONS_H

#include <string>
#include <vector>
#include "libfb2k/Block.h"
#include <tag.h>

namespace fb2k
{
// FIXME : GET BETTER NAMES!
typedef BlockResult ( *FB2KFunction ) ( TagLib::PropertyMap metadata , std::vector<Block> args );
typedef bool ( *FB2KParameterCheck ) ( unsigned int argscount );


struct Func {
    std::string name;
    FB2KFunction eval = nullptr;
    FB2KParameterCheck check = nullptr;
    Func ( std::string name, FB2KFunction eval, FB2KParameterCheck check ) {
        this->name = name;
        this->eval = eval;
        this->check = check;
    }
    Func() {}
};
typedef std::pair<std::string, Func> FuncPair;
};
#endif
