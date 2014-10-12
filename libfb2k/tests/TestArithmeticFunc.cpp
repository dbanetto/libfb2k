#include <unittest++/UnitTest++.h>
#include "libfb2k/libfb2k.h"
#include "libfb2k/Block.h"

SUITE(ArithmeticFunctions)
{
    TEST(add) {
        fb2k::Block blk = fb2k::Block("$add(1,2)");
        TagLib::PropertyMap metadata;

        auto result = blk.eval(metadata);
        CHECK_EQUAL("3", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(3, result.value);

        blk = fb2k::Block("$add(1,2,3)");
        metadata = TagLib::PropertyMap();

        result = blk.eval(metadata);
        CHECK_EQUAL("6", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(6, result.value);

        blk = fb2k::Block("$add(-10,5)");
        metadata = TagLib::PropertyMap();

        result = blk.eval(metadata);
        CHECK_EQUAL("-5", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(-5, result.value);
    }

    TEST(subtract) {
        fb2k::Block blk = fb2k::Block("$sub(1,2)");
        TagLib::PropertyMap metadata;

        auto result = blk.eval(metadata);
        CHECK_EQUAL("-1", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(-1, result.value);

        blk = fb2k::Block("$sub(1,2,3)");
        metadata = TagLib::PropertyMap();

        result = blk.eval(metadata);
        CHECK_EQUAL("-4", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(-4, result.value);

        blk = fb2k::Block("$sub(100,2,3)");
        metadata = TagLib::PropertyMap();

        result = blk.eval(metadata);
        CHECK_EQUAL("95", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(95, result.value);
    }

    TEST(divide) {
        fb2k::Block blk = fb2k::Block("$div(1,2)");
        TagLib::PropertyMap metadata;

        auto result = blk.eval(metadata);
        CHECK_EQUAL("0", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(0, result.value);

        blk = fb2k::Block("$div(100,4)");
        metadata = TagLib::PropertyMap();

        result = blk.eval(metadata);
        CHECK_EQUAL("25", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(25, result.value);

        blk = fb2k::Block("$div(100,2,2)");
        metadata = TagLib::PropertyMap();

        result = blk.eval(metadata);
        CHECK_EQUAL("25", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(25, result.value);

        blk = fb2k::Block("$div(10,0)");
        metadata = TagLib::PropertyMap();

        result = blk.eval(metadata);
        CHECK_EQUAL("10", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(10, result.value);
    }

    TEST(multiplication) {
        fb2k::Block blk = fb2k::Block("$mul(1,2)");
        TagLib::PropertyMap metadata;

        auto result = blk.eval(metadata);
        CHECK_EQUAL("2", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(2, result.value);

        blk = fb2k::Block("$mul(100,4)");
        metadata = TagLib::PropertyMap();

        result = blk.eval(metadata);
        CHECK_EQUAL("400", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(400, result.value);

        blk = fb2k::Block("$mul(100,0)");
        metadata = TagLib::PropertyMap();

        result = blk.eval(metadata);
        CHECK_EQUAL("0", result.result);
        CHECK_EQUAL(false, result.success);
        CHECK_EQUAL(0, result.value);
    }

}
