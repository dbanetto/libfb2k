#ifndef FUNCMAP_H
#define FUNCMAP_H

#include <map> // Base class: std::map
#include <string>
#include <vector>
#include "libfb2k/Block.h"
#include <taglib/tpropertymap.h>

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

	} static FunctionMap;

}

#endif // FUNCMAP_H
