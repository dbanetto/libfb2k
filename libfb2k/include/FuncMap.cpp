#include "FuncMap.h"

using namespace fb2k;

FuncMap::FuncMap()
{
	// Basic Conditionals
	this->insert(FuncPair("if",
	[](TagLib::PropertyMap data ,std::vector<Block> args) {

		if(args[0].eval(data).success)
			return args[1].eval(data);
		else
			return (args.size() == 3 ? args[2].eval(data) : BlockResult());

	}));

	this->insert(FuncPair("if3",
	[](TagLib::PropertyMap data ,std::vector<Block> args) {

		if(args[0].eval(data).success)
			return args[1].eval(data);
		else
			return args[2].eval(data);

	}));

	// Logical Operators
	// NOTE :  Logical Operators DO NOT return result strings
	this->insert(FuncPair("not",
	[](TagLib::PropertyMap data ,std::vector<Block> args) {

		BlockResult rs;
		rs.success = (!args[0].eval(data).success);
		return rs;

	}));

	this->insert(FuncPair("or",
	[](TagLib::PropertyMap data ,std::vector<Block> args) {

		BlockResult rs;
		rs.success = args[0].eval(data).success | args[1].eval(data).success;
		return rs;

	}));

	this->insert(FuncPair("xor",
	[](TagLib::PropertyMap data ,std::vector<Block> args) {

		BlockResult rs;
		rs.success = args[0].eval(data).success ^ args[1].eval(data).success;
		return rs;

	}));

	this->insert(FuncPair("and",
	[](TagLib::PropertyMap data ,std::vector<Block> args) {

		BlockResult rs;
		rs.success = args[0].eval(data).success & args[1].eval(data).success;
		return rs;

	}));
}

FuncMap::~FuncMap()
{

}
