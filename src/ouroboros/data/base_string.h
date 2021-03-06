#ifndef _OUROBOROS_BASE_STRING_H_
#define _OUROBOROS_BASE_STRING_H_

#include <ouroboros/data/base.hpp>

#include <string>
#include <utility>
#include <cstddef>

namespace ouroboros
{
	/**	Class representing a string field.
	 *
	 */
	class base_string : public var_field
	{
	public:

		/**	Default constructor.
		 *
		 */
		base_string();

		/**	Constructor.
		 *
		 *	@param [in] aTitle Title of the field.
		 *	@param [in] aDescription Description of the field.
		 *	@param [in] aValue Contents of the string.
		 *	@param [in] aPattern Pattern to match the content of the string to.
		 *	@param [in] aLengthRange Range of the length of the string
		 *		(inclusive).
		 *
		 *	@throws std::out_of_range When aValue does not meet range
		 *		requirements.
		 *	@throws std::invalid_argument When aValue does not meet pattern
		 *		requirements.
		 */
		base_string(
			const std::string& aTitle,
			const std::string& aDescription,
			const std::string& aValue,
			const std::string& aPattern,
			std::pair<std::size_t, std::size_t> aLengthRange);

		/**	Gets the pattern to match the contents of the string field to.
		 *
		 *	@returns The pattern to match the contents of the string field to.
		 */
		std::string getPattern() const;

		/**	Gets the minimum length of the string field (inclusive).
		 *
		 *	@returns The minimum length of the string field (inclusive).
		 */
		std::size_t getMinLength() const;

		/**	Gets the maximum length of the string field (inclusive).
		 *
		 *	@returns The maximum length of the string field (inclusive).
		 */
		std::size_t getMaxLength() const;

		/**	Sets the pattern to match the contents of the string field to. If
		 *	the new pattern were to invalidate the current string, this function
		 *	call fails.
		 *
		 *	@param [in] aPattern The new pattern to match the contents of the
		 *		string field to.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setPattern(const std::string& aPattern);

		/**	Sets the minimum length (inclusive) of the string field.
		 *
		 *	@param [in] aMinLength The new minimum length (inclusive) of the
		 *		string field.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setMinLength(const std::size_t& aMinLength);

		/**	Sets the maximum length (inclusive) of the string field.
		 *
		 *	@param [in] aMaxLength The new maximum length (inclusive) of the
		 *		string field.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setMaxLength(const std::size_t& aMaxLength);

		/**	Sets the pattern to match the contents of the string field to. If
		 *	the new pattern were to invalidate the current string, this function
		 *	call fails, unless the new value specified matches the new pattern.
		 *
		 *	@param [in] aPattern The new pattern to match the contents of the
		 *		string field to.
		 *	@param [in] aNewValue An optional new value to update the string to.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setPattern(
			const std::string& aPattern,
			const std::string& aNewValue);

		/**	Sets the minimum length (inclusive) of the string field.
		 *
		 *	@param [in] aMinLength The new minimum length (inclusive) of the
		 *		string field.
		 *	@param [in] aNewValue An optional new value to update the string to.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setMinLength(
			const std::size_t& aMinLength,
			const std::string& aNewValue);

		/**	Sets the maximum length (inclusive) of the string field.
		 *
		 *	@param [in] aMaxLength The new maximum length (inclusive) of the
		 *		string field.
		 *	@param [in] aNewValue An optional new value to update the string to.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setMaxLength(
			const std::size_t& aMaxLength,
			const std::string& aNewValue);

		/**	Sets the current string value of the string field.
		 *
		 *	@param [in] aValue The new string value.
		 *
		 */
		bool setString(const std::string& aValue);

		/**	Gets the current string value of the string field.
		 *
		 *	@returns The current string value.
		 *
		 */
		std::string getString() const;


		/**	Returns the JSON representation of the string field.
		 *
		 *	Example JSON output:
		 *
		 *			{ "type": "string", "title": "A string",
		 *				"description": "A test string",	"value": "hello",
		 *				"pattern": ".*", "range": [ 0, 18446744073709552000 ] }
		 *
		 *	@see ouroboros::var_field::getJSON() for more details.
		 */
		virtual std::string getJSON() const;

		/**	Tries to set the object to the JSON received.
		 *
		 *	If a proposed range invalidates a current value (or vice versa), the
		 *		requested change will not be processed and the function will
		 *		return false.
		 *
		 *	Example JSON input:
		 *		{ "value" : "foobar" }
		 *		{ "value" : "test_string", "pattern" : "t.+g" }
		 *		{ "range" : [ 0, 500 ] }
		 *
		 *	@see ouroboros::var_field::setJSON()
		 */
		virtual bool setJSON(const JSON& aJSON);

	private:
		std::string mPattern;
		std::pair<std::size_t, std::size_t> mLengthRange;

		std::string mValue;

		bool checkValidity (const std::string& aString);
	};
}

#endif//_OUROBOROS_BASE_STRING_H_
