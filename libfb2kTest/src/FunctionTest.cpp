#include <UnitTest++.h>
#include "libfb2k/libfb2k.h"
#include "libfb2k/Block.h"

SUITE(LogicalFunctions)
{
	TEST(IF) {
		fb2k::Block blk = fb2k::Block("$if(%artist%,true,false)");

		TagLib::PropertyMap metadata;
		TagLib::StringList ls;
		ls.append("Foobar");
		metadata.insert("artist",ls);

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

	TEST(NOT) {
		fb2k::Block blk = fb2k::Block("$not(%artist%)");

		TagLib::PropertyMap metadata;
		TagLib::StringList ls;
		ls.append("Foobar");
		metadata.insert("artist",ls);

		auto result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(false, result.success);

		blk = fb2k::Block("$not(artist)");
		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(true, result.success);

		blk = fb2k::Block("$not(%null%)");
		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(true, result.success);
	}

	TEST(OR) {
		fb2k::Block blk = fb2k::Block("$or(%artist%,%album%)");

		TagLib::PropertyMap metadata;

		auto result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(false, result.success);

		TagLib::StringList ls;
		ls.append("Foobar");
		metadata.insert("artist",ls);

		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(true, result.success);

		metadata.insert("album",ls);
		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(true, result.success);

		metadata.erase("artist");
		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(true, result.success);

	}

	TEST(XOR) {
		fb2k::Block blk = fb2k::Block("$xor(%artist%,%album%)");

		TagLib::PropertyMap metadata;

		auto result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(false, result.success);

		TagLib::StringList ls;
		ls.append("Foobar");
		metadata.insert("artist",ls);

		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(true, result.success);

		metadata.insert("album",ls);
		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(false, result.success);

		metadata.erase("artist");
		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(true, result.success);
	}

	TEST(AND) {
		fb2k::Block blk = fb2k::Block("$and(%artist%,%album%)");

		TagLib::PropertyMap metadata;

		auto result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(false, result.success);

		TagLib::StringList ls;
		ls.append("Foobar");
		metadata.insert("artist",ls);

		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(false, result.success);

		metadata.insert("album",ls);
		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(true, result.success);

		metadata.erase("artist");
		result = blk.eval(metadata);
		CHECK_EQUAL("", result.result);
		CHECK_EQUAL(false, result.success);
	}

}
