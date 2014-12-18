#ifndef _OUROBOROS_JSON_HPP_
#define _OUROBOROS_JSON_HPP_

#include <string>
#include <frozen.h>

namespace ouroboros
{
	class JSON
	{
	public:
		JSON();
		JSON(const std::string& aJSON);
		~JSON();
		
		bool exists(const std::string& aPath) const;
		std::string get(const std::string& aPath) const;
	private:
		json_token *mpArr;
	};
}

#endif//_OUROBOROS_JSON_HPP_