#ifndef _OUROBOROS_BASE_INTEGER_H_
#define _OUROBOROS_BASE_INTEGER_H_

#include <ouroboros/data/base.hpp>

namespace ouroboros
{
	/**	Class representing an integer field.
	 *
	 */
	template<class Number, Number Min, Number Max>
	class base_number : public var_field
	{
	public:

		/**	Default constructor.
		 *
		 */
		base_number();

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
		base_number(
			const std::string& aTitle,
			const std::string& aDescription,
			Number aValue,
			const std::pair<Number, Number>& aRange);

		/**	Gets the inclusive range of values accepted by the field.
		 *
		 *	@returns The inclusive range of values accepted by the field.
		 */
		std::pair<Number, Number> getInclusiveRange() const;

		/**	Sets the inclusive range of values accepted by the field.
		 *
		 *	@param [in] aPair The inclusive range of values accepted by the
		 *		field, with the lower number first, and the higher number
		 *		second.
		 *
		 *	@returns True if setting the new range succeeded, false otherwise.
		 */
		bool setInclusiveRange(const std::pair<Number, Number>& aPair);

		/**	Sets the number held by the field.
		 *
		 *	@param [in] aInt The new number to give to the field.
		 *
		 *	@returns True if setting the new range succeeded, false otherwise.
		 */
		bool setNumber(Number aNum);

		/**	Sets the inclusive range of values accepted by the field.
		 *
		 *	@param [in] aPair The inclusive range of values accepted by the
		 *		field, with the lower number first, and the higher number
		 *		second.
		 *	@param [in] aValue The new Value to set the field to, should the new
		 *		range be beyond what the current value can handle.
		 *
		 *	@returns True if setting the new range succeeded, false otherwise.
		 */
		bool setInclusiveRange(
			const std::pair<Number, Number>& aRange, Number aValue);

		/**	Gets the number held by the field.
		 *
		 *	@returns The number held by the field.
		 */
		Number getNumber() const;


		/**	Returns the JSON representation of the integer field.
		 *
		 *	Example JSON output:
		 *
		 *		{ "type": "signed 32-bit number",
		 *			"absolute range": [ -2147483648, 2147483647 ],
		 *			"title": "A number", "description": "An example number",
		 *			"value": 20, "range": [ -2147483648, 2147483647 ] }
		 *
		 *	@see ouroboros::var_field::get_value()
		 */
		virtual std::string getJSON() const ;

		/**	Tries to set the field to the JSON representation given.
		 *
		 *	If a proposed range invalidates a current value (or vice versa), the
		 *		requested change will not be processed and the function will
		 *		return false.
		 *
		 *	Example JSON input:
		 *		{ "value" : 100 }
		 *		{ "range" : [-100, 500 ] }
		 *
		 *	@see ouroboros::var_field::setJSON() for more information.
		 */
		bool setJSON(const JSON& aJSON);

	private:
		std::pair<Number, Number> mRange;
		Number mValue;

		bool checkValidity (Number aInt);
	};
}

#include "base_number.ipp"

#endif//_OUROBOROS_BASE_INTEGER_H_
