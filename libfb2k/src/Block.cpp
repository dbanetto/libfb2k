#include "libfb2k/Block.h"
#include <iostream>
#include <sstream>
#include <ctype.h>

using namespace fb2k;

/*
 * TODO : Add more characters that should be
 * escaped with a prepeneding : \
 * */
std::string to_escape = "\\(),[]$nt";
/*
 * Character to replace the escaped sequence
 * index of the escaped character is the same as to_escape
 */
std::string to_escaped ="\\(),[]$\n\t";


Block::Block()
{
	this->parsed = false;
	functions = std::vector<Function>();
	variables = std::vector<std::string>();
	this->raw_statement = "";
	this->parsed_statement = "";
}

Block::Block(std::string statement)
{
	this->parse(statement);
}

Block::~Block()
{

}

std::string Block::getStatement()
{
	return this->raw_statement;
}

std::vector<Block::Function> Block::getFunctions()
{
	return functions;
}

std::vector<std::string> Block::getVariables()
{
	return  variables;
}

std::string Block::getFormattedText()
{
	return this->parsed_statement;
}

enum ParsingState {
	READING = 0,
	FUNCTION_NAME = 10,
	FUNCTION_ARGS = 11,
	VARIABLE_NAME = 20
};

int Block::parse(std::string statement)
{
	std::stringstream parsed;

	this->raw_statement = statement;
	Function building;
	std::string arg_building;
	int args_index = 0;
	int scope = 0;

	//keep track of the character position in the string
	int row = 1 , col = 0;

	ParsingState state = READING;

	// Use ' ' instead of '\0' easier to debug
	char  last = ' ',  cur = ' ', next = *(statement.begin());
	bool escaped = false;
	auto itr = statement.begin();
	for(int i = 0; i < statement.length(); i++) {
		escaped = false;
		last = cur;
		cur = next;
		itr++;
		next = (itr == statement.end() ? ' ' : *itr);

		col++;
		if(cur == '\n') {
			row++;
			col = 1;
		}

		// Skip null charaters
		if(cur == '\0')
			continue;

		// Special Characters
		if(cur == '\\') {
			// TODO : refractor this to make it cleaner
			for(int n = 0; n < to_escape.length(); n++) {
				if(next == to_escape[n]) {
					cur = to_escaped[n];
					next = '\0';
					escaped = true;
					break;
				}
			}
			if(!escaped) {
				//Throw unkown escape character Error
				std::stringstream ss;
				ss << "Unkown escape character \\" << next << " at line:" << col << " row:" << row;
				throw fb2k::SyntaxError(ss.str());
			}
		}

		// TODO : add support for [$s()], (implicit if's)
		// TODO : add support for %var%, variables

		// Start of function
		if(cur == LIBFB2K_CMD_START && !escaped && state == READING) {
			building = Function();
			building.name = "";
			arg_building = "";
			building.args = std::vector<Block>();
			state = FUNCTION_NAME;
		} else if(cur == LIBFB2K_VAR_START && !escaped && state == READING) {
			variables.push_back("");
			state = VARIABLE_NAME;
		} else if(state == VARIABLE_NAME) {
			if(cur == LIBFB2K_VAR_END) {
				// TODO : find a better way to represent a 'variable' in the parsed string
				parsed << "[" << variables.size() - 1 << "]";
				args_index++;
				state = READING;
			} else {
				variables[variables.size() - 1] += cur;
			}

		} else if(state == FUNCTION_NAME) {
			if(cur == LIBFB2K_ARGS_START && !escaped) {
				state = FUNCTION_ARGS;
				scope++;
			} else {
				if(isalnum(cur)) {
					building.name += cur;
				} else {
					std::stringstream ss;
					// TODO : Should unicode function names be allowed?
					ss << "Functions names can only contain alphanumerics at line:" << row << " column:" << col << ".";
					throw fb2k::InvaildFuntionName(ss.str());
				}
			}
		} else if(state == FUNCTION_ARGS) {
			if(cur == LIBFB2K_ARGS_START && !escaped) {
				scope++;
			} else if(cur == LIBFB2K_ARGS_END && !escaped) {
				scope--;
				if(scope == 0) {
					building.args.push_back(Block(arg_building));
					arg_building = "";

					this->functions.push_back(building);
					parsed << "{" << functions.size() - 1 << "}";
					state = READING;
				}
			}
			if(scope == 1 && cur == ',' && !escaped) {
				building.args.push_back(Block(arg_building));
				arg_building = "";

			} else {
				arg_building += cur;
			}
		} else {
			// Add all the escape/normal text that is not in a function into the 'parsed' string
			parsed << cur;
		}
#ifdef DEBUG_VERB
		std::cout << "State : " << state << " Scope : " << scope  << " Last : " << last << " Current : " << cur << " Next : " << next << std::endl;
#endif
	}

	// Post parse error checking
	if(scope != 0)
		throw fb2k::SyntaxError("Mismatch of brackets");

	if(state != READING)
		throw fb2k::SyntaxError("State did not reslove");

	this->parsed_statement = parsed.str();

#ifdef DEBUG
	std::cout << "Formated : " << parsed_statement << std::endl;
	int n = 0;
	for(auto f : this->functions) {
		std::cout << "Function " << n++ << " : " << f.name << std::endl;
		for(auto arg : f.args) {
			std::cout << "\tArg : " << arg.getStatement() << std::endl;
		}
	}
	if (this->variables.size() != 0) {
		n = 0;
		std::cout << "Variables :" << std::endl;
		for(auto var : this->variables) {
			std::cout << "\t" << n++ << " : " << var << std::endl;
		}
	}


#endif
	this->parsed = true;
	return 0;
}

BlockResult Block::eval()
{
	BlockResult result;

	result.success = true;
	result.result = this->raw_statement;

	return result;
}

