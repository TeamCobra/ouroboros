#ifndef _OUROBOROS_DATASTORE_H_
#define _OUROBOROS_DATASTORE_H_

#include <ouroboros/data/base.hpp>

#include <string>
#include <vector>

namespace ouroboros
{
	/**	Implementation of the data_store concept (TODO: document concepts used
	 * 	somewhere). This implementation takes in a "root" group which it uses to
	 * 	keep track of the variables of the system.
	 *
	 *	@tparam T Type of the variables stored in the data_store. T must conform
	 *		to the base_field concept (TODO: document concepts somewhere).
	 */
	template <class T>
	class data_store
	{
	public:

		static const std::string group_delimiter;

		/**	Initializes the data_store by moving a group into its control.
		 *
		 *	@param [in] aRoot Group to be moved (i.e. std::move) into the control of
		 * 		the data_store.
		 *
		 *	@post The data_store has control over the group and the contents of
		 * 		the group can be searched for.
		 */
		data_store(const group<T>& apRoot);

		//@{
		/**	Gets a pointer to the item specified by its group and name in the
		 *		structure.
		 *
		 *	@param [in] aGroup Group name of item.
		 *	@param [in] aName Name of item.
		 *
		 *	@returns A pointer to the element found in the group specified and
		 *		identified by the name specified. Returns std::nullptr if no
		 *		item was found.
		 *
		 */
		T *get(const std::string& aGroup, const std::string& aName);
		const T *get(const std::string& aGroup, const std::string& aName) const;
		//@}

		//@{
		/**	Gets a pointer to the item specified by its group and name in the
		 *		structure.
		 *
		 *	@param [in] aGroup Group name of item.
		 *	@param [in] aName Name of item.
		 *
		 *	@returns A pointer to the element found in the group specified and
		 *		identified by the name specified. Returns std::nullptr if no
		 *		item was found.
		 *
		 */
		group<T> *get(const std::string& aGroup);
		const group<T> *get(const std::string& aGroup) const;
		//@}

	private:
		group<T> mRoot;
	};
}

#include "data_store.ipp"

#endif//_OUROBOROS_DATASTORE_H_
