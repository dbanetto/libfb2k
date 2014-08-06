#include <UnitTest++.h>
#include "libfb2k/libfb2k.h"
#include "libfb2k/Block.h"

SUITE(BlockParsing)
{
	TEST(BlockParse)
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

	TEST(BlockParseExtra)
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

	TEST(BlockParseMulti)
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
		// Add more speical characters or escape characters
		// TODO : Support $$ -> $ when parsed?
		fb2k::Block blk = fb2k::Block("\\$");
		CHECK_EQUAL(blk.getFormattedText(), "$");

		blk = fb2k::Block("\\(\\)");
		CHECK_EQUAL(blk.getFormattedText(), "()");

		blk = fb2k::Block("\\\\");
		CHECK_EQUAL(blk.getFormattedText(), "\\");

		blk = fb2k::Block("\\,");
		CHECK_EQUAL(blk.getFormattedText(), ",");

		blk = fb2k::Block("\\t\\n");
		CHECK_EQUAL(blk.getFormattedText(), "\t\n");
	}

	TEST(BlockUnicodeParse)
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

	TEST(BlockUnicodeParseExtra)
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

	TEST(BlockParseInvaildName)
	{
		CHECK_THROW(fb2k::Block("$f a i l m e ()") , fb2k::InvaildFuntionName);
		CHECK_THROW(fb2k::Block("$友()") , fb2k::InvaildFuntionName);
		CHECK_THROW(fb2k::Block("$.xX~~420^Blaze^it~~Xx.(") , fb2k::InvaildFuntionName);
	}

	TEST(BlockParseInvaildBrackets)
	{
		CHECK_THROW(fb2k::Block("$if(errro") , fb2k::SyntaxError);
		CHECK_THROW(fb2k::Block("$if(e(rrro") , fb2k::SyntaxError);
		CHECK_THROW(fb2k::Block("$if(errro") , fb2k::SyntaxError);
	}

	TEST(BlockParseInvaildEscapeChars)
	{
		// Unsupported Escape Characters
		CHECK_THROW(fb2k::Block("\\0") , fb2k::SyntaxError);
	}

	TEST(BlockParseUnFinished)
	{
		CHECK_THROW(fb2k::Block("$almost") , fb2k::SyntaxError);
		CHECK_THROW(fb2k::Block("$") , fb2k::SyntaxError);
	}

	TEST(BlockParseVariable)
	{
		fb2k::Block blk = fb2k::Block("%variable%");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		std::vector<std::string> var = blk.getVariables();
		CHECK_EQUAL(fn.size(), 0);

		CHECK_EQUAL(var.size(), 1);

		CHECK_EQUAL(var[0], "variable");

		CHECK_EQUAL(blk.getFormattedText(), "[0]");
	}

	TEST(BlockParseMultiVariable)
	{
		fb2k::Block blk = fb2k::Block("%v1% %v2% %v3%");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		std::vector<std::string> var = blk.getVariables();
		CHECK_EQUAL(fn.size(), 0);

		CHECK_EQUAL(var.size(), 3);

		CHECK_EQUAL(var[0], "v1");
		CHECK_EQUAL(var[1], "v2");
		CHECK_EQUAL(var[2], "v3");

		CHECK_EQUAL(blk.getFormattedText(), "[0] [1] [2]");
	}

	TEST(BlockParseVariableFunction)
	{
		fb2k::Block blk = fb2k::Block("$if(true,false) %var%");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		std::vector<std::string> var = blk.getVariables();
		CHECK_EQUAL(fn.size(), 1);

		CHECK_EQUAL(fn[0].name, "if");
		CHECK_EQUAL(fn[0].args.size(), 2);

		CHECK_EQUAL(fn[0].args[0], "true");
		CHECK_EQUAL(fn[0].args[1], "false");

		CHECK_EQUAL(var.size(), 1);

		CHECK_EQUAL(var[0], "var");

		CHECK_EQUAL(blk.getFormattedText(), "{0} [0]");
	}

	TEST(BlockParseAll)
	{
		fb2k::Block blk = fb2k::Block("$if(true,false) %var% \\$ text and 友");
		std::vector<fb2k::Function> fn = blk.getFunctions();
		std::vector<std::string> var = blk.getVariables();
		CHECK_EQUAL(fn.size(), 1);

		CHECK_EQUAL(fn[0].name, "if");
		CHECK_EQUAL(fn[0].args.size(), 2);

		CHECK_EQUAL(fn[0].args[0], "true");
		CHECK_EQUAL(fn[0].args[1], "false");

		CHECK_EQUAL(var.size(), 1);

		CHECK_EQUAL(var[0], "var");

		CHECK_EQUAL(blk.getFormattedText(), "{0} [0] $ text and 友");
	}
}