#include "libfb2k/Block.h"

#include <iostream>
#include <sstream>

using namespace fb2k;

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

std::vector<Function> Block::getFunctions()
{
	return this->functions;
}

std::string Block::getFormattedText()
{
	return this->formatted_statement;
}

enum ParsingState {
	READING = 0,
	FUNCTION_NAME = 10,
	FUNCTION_ARGS = 11
};

int Block::parse(std::string statement)
{
	std::stringstream parsed;

	this->raw_statement = statement;
	Function building;
	int args_index = 0;
	int scope = 0;
	ParsingState state = READING;
	for (auto itr = statement.begin(); itr < statement.end(); itr++ )
	{
		char cur = *itr;
		char last = (itr != statement.begin() ? *(itr - 1) : '\0' );
		char peek = (itr != statement.end() ? *(itr + 1) : '\0' );

		//Start of function
		if (cur == '$' && !(peek == '$' || last == '$') && state == READING)
		{
			building = Function();
			building.name = "";
			building.args = std::vector<std::string>();
			building.args.push_back("");
			args_index = 0;
			state = FUNCTION_NAME;
		} else if (state == FUNCTION_NAME)
		{
			if (cur == '(' && !(peek == '(' || last == '('))
			{
				state = FUNCTION_ARGS;
				scope = 1;
			} else {
				building.name += cur;
			}
		} else if (state == FUNCTION_ARGS)
		{
			if (cur == '(')
			{
				scope++;
			} else if (cur == ')')
			{
				scope--;
				if (scope == 0)
				{
					this->functions.push_back(building);
					parsed << "{" << this->functions.size() - 1 << "}";
					state = READING;
				}
			}
			if (scope == 1 && cur == ',')
			{
				args_index++;
				building.args.push_back("");
			} else {
					building.args[args_index] += cur;
			}
		} else {
			//Double $ in raw is equal to one in formated
			if (!(cur == '$' && peek == '$'))
				parsed << cur;
		}

#ifdef DEBUG_VERB
	std::cout << "Last : " << last << " Current : " << cur << " Next : " << peek << " State : " << state << " Scope : " << scope << std::endl;
#endif

	}

	this->formatted_statement = parsed.str();

#ifdef DEBUG
	std::cout << "Formated : " << formatted_statement << std::endl;
	for (auto f : this->functions)
	{
		std::cout << "Function : " << f.name << std::endl;
		for (auto arg : f.args)
		{
			std::cout << "\tArg : " << arg << std::endl;
		}
	}
#endif
	return 0;
}