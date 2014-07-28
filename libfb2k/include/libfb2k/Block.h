#ifndef LIBFB2K_BLOCK_H
#define LIBFB2K_BLOCK_H

#include <string>
#include <vector>

#define LIBFB2K_CMD_START "$"
#define LIBFB2K_ARGS_START "("
#define LIBFB2K_ARGS_END ")"


namespace fb2k
{
	struct BlockResult {
		std::string result;
		bool success;
	};

	struct Function {
		std::string name;
		std::vector<std::string> args;
	};

	class Block {
		public:
			Block(std::string statement);
			virtual ~Block();

			int parse(std::string statement);
			BlockResult eval();

			std::string getStatement();
			std::string getFormattedText();
			std::vector<fb2k::Function> getFunctions();
		private:
			std::vector<Block> children;
			std::vector<Function> functions;
			std::string raw_statement;
			std::string formatted_statement;
	};
}
#endif // LIBFB2K_BLOCK_H