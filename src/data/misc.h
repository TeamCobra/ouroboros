#ifndef _OUROBOROS_MISC_H_
#define _OUROBOROS_MISC_H_

#include <vector>
#include <string>

namespace ouroboros
{
	namespace detail
	{
		/**	Splits the given string into tokens, separated by the given
		 *	delimiter. Consecutive delimiters are not ignored and result in
		 *	empty tokens.
		 *
		 *	@param [in] split aString String to split.
		 *	@param [in] aDelim Delimiter to use for splitting.
		 *
		 *	@returns Vector containing tokens resulting from the splitting.
		 */
		std::vector<std::string> split(
			const std::string& aString, const std::string& aDelim);
	}
}

#endif//_OUROBOROS_MISC_H_
