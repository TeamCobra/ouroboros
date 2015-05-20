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
		 *	@param [in] aString String to split.
		 *	@param [in] aDelim Delimiter to use for splitting.
		 *
		 *	@returns Vector containing tokens resulting from the splitting.
		 */
		std::vector<std::string> split(
			const std::string& aString, const std::string& aDelim);

		/**	Takes the given name and normalizes by lower-casing all characters
		 *		and replacing spaces with underscores.
		 *
		 *	@param [in] aName String to normalize.
		 *
		 *	@returns Normalized string.
		 */
		std::string normalize_name(const std::string& aName);

		/**	Generates a random string using the given string as a basis.
		 *
		 *	@param [in] aBase String to use as a basis.
		 *	@param [in] aPool String to use as a pool of characters that may be
		 *		used for generating random strings.
		 *	@param [in] aNAppend Number of random characters to append.
		 *
		 *	@returns A random string based on aBase. It will look like:
		 *
		 *			aBase:###
		 * 		Where ### represent the random characters appended.
		 *
		 */
		std::string generate_random_string(
			const std::string& aBase, const std::string& aPool,
			std::size_t aNAppend);
	}
}

#endif//_OUROBOROS_MISC_H_
