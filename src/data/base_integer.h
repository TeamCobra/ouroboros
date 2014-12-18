#ifndef _OUROBOROS_BASE_INTEGER_H_
#define _OUROBOROS_BASE_INTEGER_H_

#include "base.hpp"

namespace ouroboros
{
	/**	Class representing an integer field.
	 *
	 */ 
	class base_integer : public var_field
	{
	public:
		
		/**	Default constructor.
		 *
		 */
		base_integer();
		
		/**	Constructor.
		 *
		 *	@param aTitle Title of the field.
		 *	@param aDescription Description of the field.
		 *	@param aValue Contents of the integer field..
		 *	@param aRange A pair of values specifying the valid range
		 *		(inclusive) for the integer (lower first, higher second).
		 *
		 *	@throws std::out_of_range When aValue does not meet range requirements.
		 */
		base_integer(
			const std::string& aTitle,
			const std::string& aDescription,
			int aValue,
			const std::pair<int,int>& aRange);

		/**	Gets the inclusive range of values accepted by the field.
		 *
		 *	@returns The inclusive range of values accepted by the field.
		 */
		std::pair<int,int> getInclusiveRange() const;

		/**	Sets the inclusive range of values accepted by the field.
		 *
		 *	@param aPair The inclusive range of values accepted by the field,
		 *		with the lower number first, and the higher number second.
		 *
		 *	@returns True if setting the new range succeeded, false otherwise.
		 */
		bool setInclusiveRange(const std::pair<int,int>& aPair);
		
		/**	Sets the number held by the field.
		 *
		 *	@param aInt The new number to give to the field.
		 *
		 *	@returns True if setting the new range succeeded, false otherwise.
		 */
		bool setNumber(int aNum);
		
		/**	Sets the inclusive range of values accepted by the field.
		 *
		 *	@param aPair The inclusive range of values accepted by the field,
		 *		with the lower number first, and the higher number second.
		 *	@param aValue The new Value to set the field to, should the new
		 *		range be beyond what the current value can handle.
		 *
		 *	@returns True if setting the new range succeeded, false otherwise.
		 */
		bool setInclusiveRange(
			const std::pair<int,int>& aRange, int aValue);
		
		/**	Returns the JSON representation of the integer field.
		 * 
		 * @see ouroboros::var_field::get_value()
		 */
		virtual std::string getValue() const override;
		
		/**	Tries to set the field to the JSON representation given.
		 * 
		 * @see ouroboros::var_field::setJSON()
		 */
		bool setJSON(const JSON& aJSON) override;

	private:
		std::pair<int, int> mRange;
		int mValue;
		
		bool checkValidity (int aInt);
	};
}

#endif//_OUROBOROS_BASE_INTEGER_H_