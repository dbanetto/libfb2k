#include "libfb2k/FuncMap.h"

using namespace fb2k;

FuncMap::FuncMap() {
	
	// TODO : assert argument sizes: fixed, greater than, less than
	
	//Implicit if
	this->insert(FuncPair("[",
	[](TagLib::PropertyMap data , std::vector<Block> args) {
		auto result = args[0].eval(data);
		if (result.success) {
			// TRUE
			return result;
		} else {
			//FALSE
			return BlockResult();
		}
	}));

	// Basic Conditionals
	this->insert(FuncPair("if",
	[](TagLib::PropertyMap data , std::vector<Block> args) {

		if (args[0].eval(data).success) {
			//TRUE
			return args[1].eval(data);
		} else {
			//FALSE
			return (args.size() == 3 ? args[2].eval(data) : BlockResult());
		}

	}));
	
	// if with guaranteed 3 arguments
	this->insert(FuncPair("if3",
	[](TagLib::PropertyMap data , std::vector<Block> args) {

		if (args[0].eval(data).success) {
			// TRUE
			return args[1].eval(data);
		} else {
			// FALSE
			return args[2].eval(data);
		}

	}));

	// Logical Operators
	// NOTE :  Logical Operators DO NOT return result strings, just a boolean
	// TODO: add implies, equals and equivalent
	this->insert(FuncPair("not",
	[](TagLib::PropertyMap data , std::vector<Block> args) {

		BlockResult rs;
		rs.success = (!args[0].eval(data).success);
		return rs;

	}));

	this->insert(FuncPair("or",
	[](TagLib::PropertyMap data , std::vector<Block> args) {

		BlockResult rs;
		rs.success = args[0].eval(data).success | args[1].eval(data).success;
		return rs;

	}));

	this->insert(FuncPair("xor",
	[](TagLib::PropertyMap data , std::vector<Block> args) {

		BlockResult rs;
		rs.success = args[0].eval(data).success ^ args[1].eval(data).success;
		return rs;

	}));

	this->insert(FuncPair("and",
	[](TagLib::PropertyMap data , std::vector<Block> args) {

		BlockResult rs;
		rs.success = args[0].eval(data).success & args[1].eval(data).success;
		return rs;

	}));
}

FuncMap::~FuncMap() {

}
