#include "JSON.hpp"
#include <frozen.h>

namespace ouroboros
{
	/*
	 * 
	 *	"{ "type" : "base_string",
	 *	"base" : { "title" : "title", "description" : "desc"}, 
	 *	"value" : "text",
	 *	"pattern" : "Pattern",
	 *	"length" : 1,
	 *	"range" : [ 0, 10 ] };
	 */
	template<>
	base_string read_JSON<base_string>(const std::string& aString)
	{
		json_token *tok, *arr = parse_json2(aString.c_str(), aString.length());
		base_string result("", "", "", "", 1, {0,0});
		if (arr)
		{
			tok = find_json_token(arr, "base.title");
			std::string title(tok->ptr, tok->len);
			tok = find_json_token(arr, "base.description");
			std::string description(tok->ptr, tok->len);
			tok = find_json_token(arr, "value");
			std::string value(tok->ptr, tok->len);
			tok = find_json_token(arr, "pattern");
			std::string pattern(tok->ptr, tok->len);
			tok = find_json_token(arr, "length");
			std::string slength(tok->ptr, tok->len);
			tok = find_json_token(arr, "range[0]");
			std::string smin(tok->ptr, tok->len);
			tok = find_json_token(arr, "range[1]");
			std::string smax(tok->ptr, tok->len);
			int length;
			std::size_t min, max;
			result = base_string(title, description, value, pattern, length, {min, max});
		}
		free(arr);
		return result;
	}
	
	template<>
	base_integer read_JSON<base_integer>(const std::string& aString)
	{
		base_integer result("","",1, {0,10});
		return result;
	}
	
}