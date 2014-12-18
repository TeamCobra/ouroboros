#include "JSON.hpp"
#include <frozen.h>

namespace ouroboros
{
	/*
	 * 
	 * "{ \"base\" : " + var_field::getValue() + ", " +
			"\"value\" : \"" + mValue + "\" ," +
			"\"pattern\" : \"" + mPattern + "\" ," +
			"\"length\" : " + std::to_string(mLength) + " ," +
			"\"range\" : [" + std::to_string(mLengthRange.first) + ", "
				+ std::to_string(mLengthRange.first) + "] }");
	 * 
	 * 
	 * 
	 * 
	 */
	template<>
	base_string read_JSON<base_string>(const std::string& aString)
	{
		json_token *tok, *arr = parse_json2(aString.c_str(), aString.length());
		
		if (arr)
		{
			tok = find_json_token(arr, "value");
			std::string value(tok->ptr, tok->len);
			tok = find_json_token(arr, "pattern");
			std::string pattern(tok->ptr, tok->len);
			tok = find_json_token(arr, "length");
			std::string length(tok->ptr, tok->len);
			tok = find_json_token(arr, "range[0]");
			std::string min(tok->ptr, tok->len);
			tok = find_json_token(arr, "range[1]");
			std::string max(tok->ptr, tok->len);
			
		}
		free(arr);
		
	}
	
	template<>
	base_integer read_JSON<base_integer>(const std::string& aString)
	{
		
	}
	
}