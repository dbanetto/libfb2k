#include "libfb2k/FuncMap.h"
#include "libfb2k/error.h"

using namespace fb2k;

FuncMap::FuncMap() {

	// TODO : assert argument sizes: fixed, greater than, less than
	// FIXME: should argument length be verified on parse? So have all errors in parse time, not run-time
	// TODO : Allow for easy addition of additional function blocks, e.g. "Colour functions"

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

		this->insert(FuncPair("if2",
	[](TagLib::PropertyMap data , std::vector<Block> args) {
		// FIXME : This should not be processed here
		if (args.size() != 2) {
			throw InvalidNumberOfArugments("Expected 2 arguments");
		}
		
		auto result = args[0].eval(data);
		if (result.success) {
			//TRUE
			return result;
		} else {
			//FALSE
			return args[1].eval(data);
		}

	}));
	
	// if with guaranteed 3 arguments
	this->insert(FuncPair("if3",
	[](TagLib::PropertyMap data , std::vector<Block> args) {
		// FIXME : This should not be processed here
		if (args.size() < 3) {
			throw InvalidNumberOfArugments("Expected 2 or greater arguments");
		}
		
		// Check a1..aN if true, return 
		for (unsigned int i = 0; i < args.size() - 1; i++) {
			BlockResult result = args[i].eval(data);
			if (result.success) {
				return result;
			}
		}
		// return `else` if a1..aN is all false
		return args[args.size() -1].eval(data);
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
		// FIXME : This should not be processed here
		if (args.size() < 2) {
			throw InvalidNumberOfArugments("Expected 2 or greater arguments");
		}

		BlockResult rs;
		rs.success = false;
		for(auto& arg : args) {
			if (arg.eval(data).success) {
				rs.success = true;
				return rs;
			}
		}
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
		// FIXME : This should not be processed here
		if (args.size() < 2) {
			throw InvalidNumberOfArugments("Expected 2 or greater arguments");
		}

		BlockResult rs;
		rs.success = true;
		for(auto& arg : args) {
			if (!arg.eval(data).success) {
				rs.success = false;
				return rs;
			}
		}
		return rs;

	}));
}

FuncMap::~FuncMap() {

}
