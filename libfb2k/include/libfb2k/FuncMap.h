#ifndef FUNCMAP_H
#define FUNCMAP_H

#include "libfb2k/Block.h"
#include <vector>
#include <tpropertymap.h>

#include <map> // Base class: std::map

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

class FuncMap : public std::map<std::string, Func>
{
public:
    FuncMap();
    FuncMap ( bool enableDefaults );
    virtual ~FuncMap();
    bool check ( std::string name, std::vector<Block> args );
    void insert ( Func function );

    //TODO : Make "function packs" that can be enabled/disabled on the fly
    void enableBoolFuncs();
    void enableMathsFuncs();
    void enableControlFuncs();
private:
    void insertOverride ( Func function );
};
// FIXME : Should this be a static global?
static FuncMap FunctionMap;
}

#endif // FUNCMAP_H
