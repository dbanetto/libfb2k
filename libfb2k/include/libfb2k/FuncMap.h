#ifndef FUNCMAP_H
#define FUNCMAP_H

#include <map> // Base class: std::map
#include "libfb2k/Function.h"

namespace fb2k
{
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
