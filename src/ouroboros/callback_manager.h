#ifndef _OUROBOROS_CALLBACK_MANAGER_H_
#define _OUROBOROS_CALLBACK_MANAGER_H_

#include <ouroboros/rest.h>
#include <map>

namespace ouroboros
{
	/**	This class is meant to become the primary callback manager for the
	 *		system, but right now it only supports "registering" names and
	 *		creating IDs for said names.
	 *
	 */
	class callback_manager
	{
	public:

		/**	Constructor.
		 *
		 */
		callback_manager();

		/**	Registers a callback with the given name.
		 *
		 *	@returns The ID assigned to the callback based on the given name.
		 */
		std::string register_callback(const std::string& aFieldName);

		/**	Unregisters a callback with the given ID.
		 *
		 *	@returns The name of the given string when registered.
		 */
		std::string unregister_callback(const std::string& aID);

	private:
		std::map<std::string, std::string > mIdToCallbacks;
	};
}

#endif//_OUROBOROS_CALLBACK_MANAGER_H_
