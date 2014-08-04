#include <UnitTest++.h>
#include "libfb2k/libfb2k.h"
#include "libfb2k/Block.h"

SUITE(BlockParsing)
{
	TEST(BlockSimpleParse)
	{
		fb2k::Block blk = fb2k::Block("$if(true,then,false)");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		CHECK_EQUAL(fn.size(), 1);
		CHECK_EQUAL(fn[0].name, "if");
		CHECK_EQUAL(fn[0].args.size(), 3);

		CHECK_EQUAL(fn[0].args[0], "true");
		CHECK_EQUAL(fn[0].args[1], "then");
		CHECK_EQUAL(fn[0].args[2], "false");

		CHECK_EQUAL(blk.getFormattedText(), "{0}");
	}

	TEST(BlockSimpleParseExtra)
	{
		fb2k::Block blk = fb2k::Block("$if(true,then,false) other text");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		CHECK_EQUAL(fn.size(), 1);
		CHECK_EQUAL(fn[0].name, "if");
		CHECK_EQUAL(fn[0].args.size(), 3);

		CHECK_EQUAL(fn[0].args[0], "true");
		CHECK_EQUAL(fn[0].args[1], "then");
		CHECK_EQUAL(fn[0].args[2], "false");


		CHECK_EQUAL(blk.getFormattedText(), "{0} other text");
	}

	TEST(BlockSimpleParseMulti)
	{
		fb2k::Block blk = fb2k::Block("$if(true,then,false) $func(false,not,stuff)");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		CHECK_EQUAL(fn.size(), 2);

		CHECK_EQUAL(fn[0].name, "if");
		CHECK_EQUAL(fn[0].args.size(), 3);

		CHECK_EQUAL(fn[0].args[0], "true");
		CHECK_EQUAL(fn[0].args[1], "then");
		CHECK_EQUAL(fn[0].args[2], "false");

		CHECK_EQUAL(fn[1].name, "func");
		CHECK_EQUAL(fn[1].args.size(), 3);

		CHECK_EQUAL(fn[1].args[0], "false");
		CHECK_EQUAL(fn[1].args[1], "not");
		CHECK_EQUAL(fn[1].args[2], "stuff");


		CHECK_EQUAL(blk.getFormattedText(), "{0} {1}");
	}

	TEST(BlockSpeicalChars)
	{
		//Add more speical characters
		fb2k::Block blk = fb2k::Block("$$");

		CHECK_EQUAL(blk.getFormattedText(), "$");
	}

	TEST(BlockSimpleUnicodeParse)
	{
		fb2k::Block blk = fb2k::Block("$if(♡,馬鹿,バカ)");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		CHECK_EQUAL(fn.size(), 1);
		CHECK_EQUAL(fn[0].name, "if");
		CHECK_EQUAL(fn[0].args.size(), 3);

		CHECK_EQUAL(fn[0].args[0], "♡");
		CHECK_EQUAL(fn[0].args[1], "馬鹿");
		CHECK_EQUAL(fn[0].args[2], "バカ");

		CHECK_EQUAL(blk.getFormattedText(), "{0}");
	}

	TEST(BlockSimpleUnicodeParseExtra)
	{
		fb2k::Block blk = fb2k::Block("$if(♡,馬鹿,バカ) 友");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		CHECK_EQUAL(fn.size(), 1);
		CHECK_EQUAL(fn[0].name, "if");
		CHECK_EQUAL(fn[0].args.size(), 3);

		CHECK_EQUAL(fn[0].args[0], "♡");
		CHECK_EQUAL(fn[0].args[1], "馬鹿");
		CHECK_EQUAL(fn[0].args[2], "バカ");

		CHECK_EQUAL(blk.getFormattedText(), "{0} 友");
	}

	TEST(BlockSimpleParseInvaildName)
	{
		CHECK_THROW(fb2k::Block("$f a i l m e (true,then,false)") , fb2k::InvaildFuntionName);
	}

	TEST(BlockSimpleParseInvaildBrackets)
	{
		CHECK_THROW(fb2k::Block("$if(errro") , fb2k::SyntaxError);
		CHECK_THROW(fb2k::Block("$if(e(rrro") , fb2k::SyntaxError);
		CHECK_THROW(fb2k::Block("$if(errro") , fb2k::SyntaxError);
	}
}


