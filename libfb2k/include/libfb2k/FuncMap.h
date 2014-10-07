#ifndef FUNCMAP_H
#define FUNCMAP_H

#include <map> // Base class: std::map
#include <string>
#include <vector>
#include "libfb2k/Block.h"
#include <tag.h>

namespace fb2k
{
	// FIXME : GET BETTER NAMES!
	typedef BlockResult (*FB2KFunction) (TagLib::PropertyMap metadata , std::vector<Block> args);
	typedef std::pair<std::string, FB2KFunction> FuncPair;

	class FuncMap : public std::map<std::string, FB2KFunction>
	{

		public:
			FuncMap();
			virtual ~FuncMap();

	};
	// FIXME : Should this be a static global?
	static FuncMap FunctionMap;
}

#endif // FUNCMAP_H
