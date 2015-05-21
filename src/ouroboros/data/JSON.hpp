#ifndef _OUROBOROS_JSON_HPP_
#define _OUROBOROS_JSON_HPP_

#include <ouroboros/data/base.hpp>

#include <string>
#include <frozen/frozen.h>

namespace ouroboros
{
	namespace detail
	{
		std::string getJSONElement
			json_token *arr, const std::string& aElement);

		template<typename number>
		number extractNumber(const std::string& aString);
	}

	std::map<std::string, std::string> readJSON(const std::string& aJSON);
}

#include "JSON.ipp"

#endif//_OUROBOROS_JSON_HPP_
