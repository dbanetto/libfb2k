#include <unittest++/UnitTest++.h>
#include "libfb2k/FuncMap.h"
#include "libfb2k/Block.h"

using namespace fb2k;

SUITE(FunctionMap)
{
    TEST(EnablingFunctions) {
        FuncMap map;
        map.clear();
        CHECK_EQUAL(0, map.size());

        map.enableBoolFuncs();
        CHECK_EQUAL(4, map.size());

        map.enableControlFuncs();
        CHECK_EQUAL(8, map.size());

        map.enableMathsFuncs();
        CHECK_EQUAL(15, map.size());
    }

    TEST(Contructor) {
        FuncMap map = FuncMap(false);
        CHECK_EQUAL(0, map.size());

        map = FuncMap(true);
        CHECK_EQUAL(15, map.size());

        map = FuncMap();
        CHECK_EQUAL(15, map.size());
    }

    TEST(InsertExisting) {
        FuncMap map(false);
        map.enableBoolFuncs();
        CHECK_THROW(map.insert(Func("not",
        [](TagLib::PropertyMap data , std::vector<Block> args) {
            return BlockResult();
        },
        [](unsigned int argscount) {
            return true;
        })), FB2KError);
    }

    TEST(InsertNullFunctions) {
        FuncMap map;
        CHECK_THROW(map.insert(Func("example",nullptr, nullptr)), FB2KError);
        CHECK_THROW(map.insert(Func("example",
        [](TagLib::PropertyMap data , std::vector<Block> args) {
            return BlockResult();
        }, nullptr)), FB2KError);
        CHECK_THROW(map.insert(Func()), FB2KError);
    }
}
