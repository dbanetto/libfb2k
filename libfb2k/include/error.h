#ifndef LIBFB2K_ERROR_H
#define LIBFB2K_ERROR_H

#include <string>
#include <stdexcept>

namespace fb2k {

	class InvaildFuntionName : public std::runtime_error
	{
		public:
			InvaildFuntionName(const std::string& msg)
				: std::runtime_error(msg) {};
	};

	class SyntaxError : public std::runtime_error
	{
		public:
			SyntaxError(const std::string& msg)
				: std::runtime_error(msg) {};
	};
};
#endif // LIBFB2K_ERROR_H