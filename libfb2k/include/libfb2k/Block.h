#ifndef LIBFB2K_BLOCK_H
#define LIBFB2K_BLOCK_H

#include <string>
#include <vector>


#include "error.h"

#define LIBFB2K_CMD_START '$'

#define LIBFB2K_ARGS_START '('
#define LIBFB2K_ARGS_END ')'

#define LIBFB2K_VAR_START '%'
#define LIBFB2K_VAR_END '%'

namespace fb2k
{
	struct BlockResult {
		std::string result;
		bool success;
	};

	class Block {
		public:
			struct Function {
				std::string name;
				std::vector<Block> args;
			};
			Block();
			Block(std::string statement);
			virtual ~Block();

			int parse(std::string statement);
			BlockResult eval();

			std::string getStatement();
			std::string getFormattedText();
			std::vector<Function> getFunctions();
			std::vector<std::string> getVariables();

			bool isParsed();
		private:
			std::vector<Function> functions;
			std::vector<std::string> variables;

			std::string raw_statement;
			std::string parsed_statement;

			bool parsed;
	};
}
#endif // LIBFB2K_BLOCK_H