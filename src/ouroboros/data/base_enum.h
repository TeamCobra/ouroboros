#ifndef _OUROBOROS_BASE_ENUM_H_
#define _OUROBOROS_BASE_ENUM_H_

#include <ouroboros/data/base.hpp>

#include <map>

namespace ouroboros
{
	/**	Class representing an integer field.
	 *
	 */
	class base_enum : public var_field
	{
	public:

		/**	Default constructor.
		 *
		 */
		base_enum();

		/**	Constructor.
		 *
		 *	@param [in] aTitle Title of the field.
		 *	@param [in] aDescription Description of the field.
		 *	@param [in] aValue Contents of the integer field..
		 *	@param [in] aRange A pair of values specifying the valid range
		 *		(inclusive) for the integer (lower first, higher second).
		 *
		 *	@throws std::out_of_range When aValue does not meet range requirements.
		 */
		base_enum(
			const std::string& aTitle,
			const std::string& aDescription,
			const std::string& aValue,
			const std::map<std::string, int>& aEnums);

		base_enum(
			const std::string& aTitle,
			const std::string& aDescription,
			int aValue,
			const std::map<std::string, int>& aEnums);

		/**	Sets the number held by the field.
		 *
		 *	@param [in] aInt The new number to give to the field.
		 *
		 *	@returns True if setting the new range succeeded, false otherwise.
		 */
		bool setValue(const std::string& aEnum);
		bool setValue(int aEnum);

		/**	Returns the integer value of the requested Enum.
		 *
		 *	@returns The integer value of the requested Enum.
		 */
		int getValue() const;
		
		/**	Returns the string representation of the requested Enum.
		 *
		 *	@returns The string representation of the requested Enum.
		 */
		std::string getString() const;

		/**	Returns the JSON representation of the integer field.
		 *
		 *	Example JSON output:
		 *
		 *			{ "title" : "foo", "description" : "bar", "value" : "E0",
		 *				"enums" : { "E0" : 0, "E1" : 1, "E2" : 2 } }
		 *
		 * @see ouroboros::var_field::get_value()
		 */
		virtual std::string getJSON() const;

		/**	Tries to set the field to the JSON representation given.
		 *
		 *	Supported fields:
		 * 
		 *		title - string\n
		 *		description - string\n
		 *		value - an enum string\n
		 *
		 *	Example JSON inputs:
		 *
		 *			{ "title" : "foo", "description" : "bar", "value" : "E0" }
		 *			{ "value" : "E1" }
		 *
		 * @see ouroboros::var_field::setJSON()
		 */
		bool setJSON(const JSON& aJSON);

	private:
		int mValue;
		mutable std::map<int, std::string> mValueMap;
		mutable std::map<std::string, int> mEnumMap;

		bool checkValidity (const std::string& aEnum) const;
		bool checkValidity (int aEnum) const;
	};
}

#endif//_OUROBOROS_BASE_ENUM_H_
