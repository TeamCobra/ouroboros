#ifndef _OUROBOROS_BASE_FUNCTION_H_
#define _OUROBOROS_BASE_FUNCTION_H_

#include <ouroboros/data/base.hpp>
#include <ouroboros/function_manager.h>

namespace ouroboros
{
	/**	Class representing function field.
	 *
	 */ 
	class base_function : public var_field
	{
	public:
		
		/**	Constructor.
		 *
		 *	@param [in] aTitle Title of the field.
		 *	@param [in] aDescription Description of the field.
		 *
		 *	@throws std::out_of_range When aValue does not meet range requirements.
		 */
		base_function(
			const std::string& aTitle,
			const std::string& aDescription,
			const std::vector<std::string>& aParameters,
			function_manager &aManager);
		
		/**	Returns the JSON representation of the integer field.
		 * 
		 * @see ouroboros::var_field::get_value()
		 */
		virtual std::string getJSON() const;
		
		/**	Tries to set the field to the JSON representation given.
		 * 
		 * @see ouroboros::var_field::setJSON()
		 */
		bool setJSON(const JSON& aJSON) ;

	private:
		std::vector<std::string> mParameters;
		function_manager *mpManager;
	};
}

#endif//_OUROBOROS_BASE_FUNCTION_H_
