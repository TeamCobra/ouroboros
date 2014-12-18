#ifndef _OUROBOROS_JSON_HPP_
#define _OUROBOROS_JSON_HPP_

#include <string>

namespace ouroboros
{
	template<class item>
	item read_JSON(const std::string& aString);
	
	template<>
	base_string read_JSON<base_string>(const std::string& aString);
	
	template<>
	base_integer read_JSON<base_integer>(const std::string& aString);
	
}

#include "JSON.ipp"

#endif//_OUROBOROS_JSON_HPP_