#ifndef _OUROBOROS_BASE_STRING_H_
#define _OUROBOROS_BASE_STRING_H_

#include "base.hpp"

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
		 *	@param aTitle Title of the field.
		 *	@param aDescription Description of the field.
		 *	@param aValue Contents of the string.
		 *	@param aPattern Pattern to match the content of the string to.
		 *	@param aLength FIXME What is this field for?
		 *	@param aLengthRange Range of the length of the string (inclusive).
		 *
		 *	@throws std::out_of_range When aValue does not meet range requirements.
		 * 	@throws std::invalid_argument When aValue does not meet pattern requirements.
		 */
		base_string(
			const std::string& aTitle,
			const std::string& aDescription,
			const std::string& aValue,
			const std::string& aPattern,
			std::size_t aLength, 
			std::pair<std::size_t, std::size_t> aLengthRange);

		/**	Gets the pattern to match the contents of the string field to.
		 *
		 *	@returns The pattern to match the contents of the string field to.
		 */
		std::string getPattern() const;
		
		/**	Gets the FIXME see constructor for questions.
		 *
		 *	@returns The ?.
		 */
		std::size_t getLength() const;
		
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
		 *	@param aPattern The new pattern to match the contents of the string
		 *		field to.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setPattern(const std::string& aPattern);
		
		/**	Sets the FIXME see constructor for questions.
		 *
		 *	@returns The ?.
		 */
		bool setLength(const std::size_t& aLength);
		
		/**	Sets the minimum length (inclusive) of the string field.
		 *
		 *	@param aMinLength The new minimum length (inclusive) of the string
		 *		field.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setMinLength(const std::size_t& aMinLength);
		
		/**	Sets the maximum length (inclusive) of the string field.
		 *
		 *	@param aMaxLength The new maximum length (inclusive) of the string
		 *		field.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setMaxLength(const std::size_t& aMaxLength);
		
		/**	Sets the pattern to match the contents of the string field to. If
		 *	the new pattern were to invalidate the current string, this function
		 *	call fails, unless the new value specified matches the new pattern.
		 *
		 *	@param aPattern The new pattern to match the contents of the string
		 *		field to.
		 *	@param aNewValue An optional new value to update the string to.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setPattern(
			const std::string& aPattern,
			const std::string& aNewValue);
		
		/**	Sets the FIXME see constructor for questions.
		 *
		 *	@returns The ?.
		 */
		bool setLength(
			const std::size_t& aLength,
			const std::string& aNewValue);
		
		/**	Sets the minimum length (inclusive) of the string field.
		 *
		 *	@param aMinLength The new minimum length (inclusive) of the string
		 *		field.
		 *	@param aNewValue An optional new value to update the string to.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setMinLength(
			const std::size_t& aMinLength,
			const std::string& aNewValue);
		
		/**	Sets the maximum length (inclusive) of the string field.
		 *
		 *	@param aMaxLength The new maximum length (inclusive) of the string
		 *		field.
		 *	@param aNewValue An optional new value to update the string to.
		 *
		 *	@returns True upon success, false upon failure. Upon failure, no
		 *		change took place in the system.
		 */
		bool setMaxLength(
			const std::size_t& aMaxLength,
			const std::string& aNewValue);
		
		/**	Sets the current string value of the string field.
		 *
		 *	@param aValue The new string value.
		 * 
		 */
		bool setString(const std::string& aValue);
		
		/**	Returns the JSON representation of the string field.
		 * 
		 * @see ouroboros::var_field::getJSON()
		 */
		virtual std::string getJSON() const override;
		
		/**	Tries to set the object to the JSON received.
		 *
		 * @see ouroboros::var_field::setJSON()
		 */
		virtual bool setJSON(const JSON& aJSON) override;

	private:
		std::string mPattern;
		std::size_t mLength;
		std::pair<std::size_t, std::size_t> mLengthRange;
		
		std::string mValue;
		
		bool checkValidity (const std::string& aString);
	};
}

#endif//_OUROBOROS_BASE_STRING_H_