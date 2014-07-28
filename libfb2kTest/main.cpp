#include <UnitTest++.h>
#include "libfb2k/libfb2k.h"
#include "libfb2k/Block.h"

// run all tests
int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}

SUITE(BlockParsing)
{
	TEST(BlockSimpleParse)
	{
		fb2k::Block blk = fb2k::Block("$if(true,then,false)");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		CHECK(fn.size() == 1);
		CHECK(fn[0].name == "if");
		CHECK(fn[0].args.size() == 3);

		CHECK(fn[0].args[0] == "true");
		CHECK(fn[0].args[1] == "then");
		CHECK(fn[0].args[2] == "false");

		CHECK(blk.getFormattedText() == "{0}");
	}

	TEST(BlockSimpleParseExtra)
	{
		fb2k::Block blk = fb2k::Block("$if(true,then,false) other text");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		CHECK(fn.size() == 1);
		CHECK(fn[0].name == "if");
		CHECK(fn[0].args.size() == 3);

		CHECK(fn[0].args[0] == "true");
		CHECK(fn[0].args[1] == "then");
		CHECK(fn[0].args[2] == "false");


		CHECK(blk.getFormattedText() == "{0} other text");
	}

	TEST(BlockSimpleParseMulti)
	{
		fb2k::Block blk = fb2k::Block("$if(true,then,false) $if(false,not,stuff)");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		CHECK(fn.size() == 2);

		CHECK(fn[0].name == "if");
		CHECK(fn[0].args.size() == 3);

		CHECK(fn[0].args[0] == "true");
		CHECK(fn[0].args[1] == "then");
		CHECK(fn[0].args[2] == "false");

		CHECK(fn[1].name == "if");
		CHECK(fn[1].args.size() == 3);

		CHECK(fn[1].args[0] == "false");
		CHECK(fn[1].args[1] == "not");
		CHECK(fn[1].args[2] == "stuff");


		CHECK(blk.getFormattedText() == "{0} {1}");
	}

	TEST(BlockSpeicalChars)
	{
		//Add more speical characters
		fb2k::Block blk = fb2k::Block("$$");

		CHECK(blk.getFormattedText() == "$");
	}
}