#ifndef LIBFB2K_ERROR_H
#define LIBFB2K_ERROR_H

#include <string>
#include <stdexcept>

namespace fb2k
{
	class FB2KError  : public std::runtime_error
	{
		public:
			FB2KError(const std::string& msg)
				: std::runtime_error(msg) {};
	};

	class InvaildFuntionName : public FB2KError
	{
		public:
			InvaildFuntionName(const std::string& msg)
				: FB2KError(msg) {};
	};

	class SyntaxError : public FB2KError
	{
		public:
			SyntaxError(const std::string& msg)
				: FB2KError(msg) {};
	};
};
#endif // LIBFB2K_ERROR_H
