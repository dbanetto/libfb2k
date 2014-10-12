#include <UnitTest++.h>
#include "libfb2k/libfb2k.h"
#include "libfb2k/Block.h"

SUITE(ControlFlowFunctions)
{

    TEST(IF) {
        fb2k::Block blk = fb2k::Block("$if(%artist%,true,false)");

        TagLib::PropertyMap metadata;
        TagLib::StringList ls;
        ls.append("Foobar");
        metadata.insert("artist", ls);

        auto result = blk.eval(metadata);
        CHECK_EQUAL("true", result.result);
        CHECK_EQUAL(false, result.success);

        blk = fb2k::Block("$if(%artist%,true)");
        result = blk.eval(metadata);
        CHECK_EQUAL("true", result.result);
        CHECK_EQUAL(false, result.success);

        blk = fb2k::Block("$if(null,true,false)");
        result = blk.eval(metadata);
        CHECK_EQUAL("false", result.result);
        CHECK_EQUAL(false, result.success);

        blk = fb2k::Block("$if(null,true)");
        result = blk.eval(metadata);
        CHECK_EQUAL("", result.result);
        CHECK_EQUAL(false, result.success);
    }

    TEST(IMPLICT_IF) {
        fb2k::Block blk = fb2k::Block("[%artist%]");

        TagLib::PropertyMap metadata;
        TagLib::StringList ls;
        ls.append("Foobar");
        metadata.insert("artist", ls);

        auto result = blk.eval(metadata);
        CHECK_EQUAL("Foobar", result.result);
        CHECK_EQUAL(true, result.success);

        blk = fb2k::Block("[artist]");
        result = blk.eval(metadata);
        CHECK_EQUAL("", result.result);
        CHECK_EQUAL(false, result.success);

        blk = fb2k::Block("[artist %artist%]");
        result = blk.eval(metadata);
        CHECK_EQUAL("artist Foobar", result.result);
        CHECK_EQUAL(true, result.success);
    }

    TEST(IF2) {
        fb2k::Block blk = fb2k::Block("$if2(%artist%,then)");

        TagLib::PropertyMap metadata;
        TagLib::StringList ls;

        auto result = blk.eval(metadata);
        CHECK_EQUAL("then", result.result);
        CHECK_EQUAL(false, result.success);

        ls.append("Foobar");
        metadata.insert("artist", ls);

        result = blk.eval(metadata);
        CHECK_EQUAL("Foobar", result.result);
        CHECK_EQUAL(true, result.success);
    }

    TEST(IF3) {
        fb2k::Block blk = fb2k::Block("$if3(%artist%,%title%,then)");

        TagLib::PropertyMap metadata;
        TagLib::StringList ls;

        auto result = blk.eval(metadata);
        CHECK_EQUAL("then", result.result);
        CHECK_EQUAL(false, result.success);


        ls.append("Foobar");
        metadata.insert("artist", ls);

        result = blk.eval(metadata);
        CHECK_EQUAL("Foobar", result.result);
        CHECK_EQUAL(true, result.success);

        ls = TagLib::StringList();
        ls.append("Test");
        metadata.insert("title", ls);
        result = blk.eval(metadata);
        CHECK_EQUAL("Foobar", result.result);
        CHECK_EQUAL(true, result.success);

        metadata.erase("artist");
        result = blk.eval(metadata);
        CHECK_EQUAL("Test", result.result);
        CHECK_EQUAL(true, result.success);
    }
}
