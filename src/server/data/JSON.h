#ifndef _OUROBOROS_JSON_HPP_
#define _OUROBOROS_JSON_HPP_

#include <string>
#include <frozen/frozen.h>

namespace ouroboros
{
	class JSON
	{
	public:
		/**	Default constructor. Initializes an empty JSON object.
		 * 
		 */
		JSON();
		
		/**	Constructor. Tries to parse given string as a JSON object.
		 *
		 *	@param [in] aJSON String to be parsed into object.
		 * 
		 *	@post If aJSON is a valid JSON string, it will be parsed into the
		 *		object. If it isn't, the constructed object will be empty.
		 */
		JSON(const std::string& aJSON);
		
		/**	Destructor.
		 * 
		 */
		~JSON();
		
		/**	Checks whether a given path in the JSON object exists.
		 *
		 *	@param [in] aPath Path of JSON element to try to locate.
		 *
		 *	@returns True if the JSON element was found, false otherwise.
		 */
		bool exists(const std::string& aPath) const;
		
		/**	Gets the JSON element found at the given path.
		 *
		 *	@param [in] aPath Path of JSON element to get.
		 *
		 *	@returns String representation of the JSON element. An empty string
		 *		is returned if no element was found.
		 */
		std::string get(const std::string& aPath) const;
		
		/**	Checks whether the JSON object is empty.
		 *
		 *	@returns True if the JSON object is empty, false otherwise.
		 */
		bool empty() const;

	private:
		json_token *mpArr;
	};
}

#endif//_OUROBOROS_JSON_HPP_
