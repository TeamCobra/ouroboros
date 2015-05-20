#ifndef _OUROBOROS_BASE_BOOLEAN_H_
#define _OUROBOROS_BASE_BOOLEAN_H_

#include "base.hpp"

namespace ouroboros
{
	/**	Class representing an integer field.
	 *
	 */
	class base_boolean : public var_field
	{
	public:

		/**	Default constructor.
		 *
		 */
		base_boolean();

		/**	Constructor.
		 *
		 *	@param [in] aTitle Title of the field.
		 *	@param [in] aDescription Description of the field.
		 *	@param [in] aValue Contents of the integer field..
		 *	@param [in] aRange A pair of values specifying the valid range
		 *		(inclusive) for the integer (lower first, higher second).
		 *
		 *	@throws std::out_of_range When aValue does not meet range
		 *		requirements.
		 */
		base_boolean(
			const std::string& aTitle,
			const std::string& aDescription,
			bool aValue);

		/**	Sets the value held by the field.
		 *
		 *	@param [in] aValue The new value to give to the field.
		 *
		 */
		void setValue(bool aValue);

		/**	Gets the value held by the field.
		 *
		 *	The JSON representation outputs all the information held by the
		 *	base_boolean. Example:
		 *
		 *		{ "type" : "boolean", "title" : "TITLE",
		 *			"description" : "DESCRIPTION", "value" : "false" }
		 *
		 *	@param [in] aInt The new number to give to the field.
		 *
		 *	@returns The field's current value;
		 */
		bool getValue();

		/**	Returns the JSON representation of the integer field.
		 *
		 *	@see var_field::getJSON for more details.
		 */
		virtual std::string getJSON() const ;

		/**	Tries to set the field to the JSON representation given.
		 *
		 *	Supported fields:
		 * 
		 *		title - string\n
		 *		description - string\n
		 *		value - "true" or "false"\n
		 *
		 *	Example JSON inputs:
		 *
		 *			{ "title" : "foo", "description" : "bar", "value" : "true" }
		 *			{ "value" : "false" }
		 *
		 * @see var_field::setJSON() for more details.
		 */
		bool setJSON(const JSON& aJSON) ;

	private:
		bool mValue;
	};
}

#endif//_OUROBOROS_BASE_BOOLEAN_H_
