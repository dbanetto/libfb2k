#include <UnitTest++.h>
#include "libfb2k/libfb2k.h"
#include "libfb2k/Block.h"

SUITE(BlockParsing)
{
	TEST(BlockParse)
	{
		fb2k::Block blk = fb2k::Block("$if(true,then,false)");
		auto fn = blk.getFunctions();
		CHECK_EQUAL(1, fn.size());	
		CHECK_EQUAL("if" ,fn[0].name);
		CHECK_EQUAL(fn[0].args.size(), 3);

		CHECK_EQUAL("true", fn[0].args[0].getStatement());
		CHECK_EQUAL("then", fn[0].args[1].getStatement());
		CHECK_EQUAL("false", fn[0].args[2].getStatement());

		CHECK_EQUAL("{0}",blk.getFormattedText());
	}

	TEST(BlockParseExtra)
	{
		fb2k::Block blk = fb2k::Block("$if(true,then,false) other text");
		auto fn = blk.getFunctions();
		CHECK_EQUAL(1, fn.size());
		CHECK_EQUAL("if", fn[0].name);
		CHECK_EQUAL(3, fn[0].args.size());

		CHECK_EQUAL("true", fn[0].args[0].getStatement());
		CHECK_EQUAL("then", fn[0].args[1].getStatement());
		CHECK_EQUAL("false", fn[0].args[2].getStatement());


		CHECK_EQUAL("{0} other text", blk.getFormattedText());
	}

	TEST(BlockParseMulti)
	{
		fb2k::Block blk = fb2k::Block("$if(true,then,false) $func(false,not,stuff)");
		auto fn = blk.getFunctions();
		CHECK_EQUAL(2, fn.size());

		CHECK_EQUAL("if", fn[0].name);
		CHECK_EQUAL(3, fn[0].args.size());

		CHECK_EQUAL("true", fn[0].args[0].getStatement());
		CHECK_EQUAL("then", fn[0].args[1].getStatement());
		CHECK_EQUAL("false", fn[0].args[2].getStatement());

		CHECK_EQUAL("func", fn[1].name);
		CHECK_EQUAL(3, fn[1].args.size());

		CHECK_EQUAL("false", fn[1].args[0].getStatement());
		CHECK_EQUAL("not", fn[1].args[1].getStatement());
		CHECK_EQUAL("stuff", fn[1].args[2].getStatement());


		CHECK_EQUAL("{0} {1}", blk.getFormattedText());
	}

	TEST(BlockSpeicalChars)
	{
		// Add more speical characters or escape characters
		// TODO : Support $$ -> $ when parsed?
		fb2k::Block blk = fb2k::Block("\\$");
		CHECK_EQUAL("$", blk.getFormattedText());

		blk = fb2k::Block("\\(\\)");
		CHECK_EQUAL("()", blk.getFormattedText());

		blk = fb2k::Block("\\\\");
		CHECK_EQUAL("\\", blk.getFormattedText());

		blk = fb2k::Block("\\,");
		CHECK_EQUAL(",", blk.getFormattedText());

		blk = fb2k::Block("\\t\\n");
		CHECK_EQUAL("\t\n", blk.getFormattedText());
	}

	TEST(BlockUnicodeParse)
	{
		fb2k::Block blk = fb2k::Block("$if(♡,馬鹿,バカ)");
		auto fn = blk.getFunctions();
		CHECK_EQUAL(1, fn.size());
		CHECK_EQUAL("if", fn[0].name);
		CHECK_EQUAL(3, fn[0].args.size());

		CHECK_EQUAL("♡", fn[0].args[0].getStatement());
		CHECK_EQUAL("馬鹿", fn[0].args[1].getStatement());
		CHECK_EQUAL("バカ", fn[0].args[2].getStatement());

		CHECK_EQUAL("{0}", blk.getFormattedText());
	}

	TEST(BlockUnicodeParseExtra)
	{
		fb2k::Block blk = fb2k::Block("$if(♡,馬鹿,バカ) 友");
		auto fn = blk.getFunctions();
		CHECK_EQUAL(1, fn.size());
		CHECK_EQUAL("if", fn[0].name);
		CHECK_EQUAL(3, fn[0].args.size());

		CHECK_EQUAL("♡", fn[0].args[0].getStatement());
		CHECK_EQUAL("馬鹿", fn[0].args[1].getStatement());
		CHECK_EQUAL("バカ", fn[0].args[2].getStatement());

		CHECK_EQUAL("{0} 友", blk.getFormattedText());
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
		auto fn = blk.getFunctions();
		std::vector<std::string> var = blk.getVariables();
		CHECK_EQUAL(0, fn.size());

		CHECK_EQUAL(1, var.size());

		CHECK_EQUAL("variable", var[0]);

		CHECK_EQUAL("[0]", blk.getFormattedText());
	}

	TEST(BlockParseMultiVariable)
	{
		fb2k::Block blk = fb2k::Block("%v1% %v2% %v3%");
		auto fn = blk.getFunctions();
		std::vector<std::string> var = blk.getVariables();
		CHECK_EQUAL(0, fn.size());

		CHECK_EQUAL(3, var.size());

		CHECK_EQUAL("v1", var[0]);
		CHECK_EQUAL("v2", var[1]);
		CHECK_EQUAL("v3", var[2]);

		CHECK_EQUAL("[0] [1] [2]", blk.getFormattedText());
	}

	TEST(BlockParseVariableFunction)
	{
		fb2k::Block blk = fb2k::Block("$if(true,false) %var%");
		auto fn = blk.getFunctions();
		std::vector<std::string> var = blk.getVariables();
		CHECK_EQUAL(1, fn.size());

		CHECK_EQUAL("if", fn[0].name);
		CHECK_EQUAL(2, fn[0].args.size());

		CHECK_EQUAL("true", fn[0].args[0].getStatement());
		CHECK_EQUAL("false", fn[0].args[1].getStatement());

		CHECK_EQUAL(1, var.size());

		CHECK_EQUAL("var", var[0]);

		CHECK_EQUAL("{0} [0]", blk.getFormattedText());
	}

	TEST(BlockParseAll)
	{
		fb2k::Block blk = fb2k::Block("$if(true,false) %var% \\$ text and 友");
		auto fn = blk.getFunctions();
		std::vector<std::string> var = blk.getVariables();
		CHECK_EQUAL(1, fn.size());

		CHECK_EQUAL("if", fn[0].name);
		CHECK_EQUAL(2, fn[0].args.size());

		CHECK_EQUAL("true", fn[0].args[0].getStatement());
		CHECK_EQUAL("false", fn[0].args[1].getStatement());

		CHECK_EQUAL(1, var.size());

		CHECK_EQUAL("var", var[0]);

		CHECK_EQUAL("{0} [0] $ text and 友", blk.getFormattedText());
	}
}
