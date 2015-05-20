#ifndef _OUROBOROS_BASE_HPP_
#define _OUROBOROS_BASE_HPP_

#include <ouroboros/data/JSON.h>

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <map>
#include <stdexcept>
#include <list>

namespace ouroboros
{
	/**	Abstract base class from which all fields are derived. Keeps track of
	 *	the title and description of the field.
	 *
	 */
	class base_field
	{
	public:

		/**	Constructor.
		 *
		 *	@param [in] aTitle Title of the field.
		 *	@param [in] aDescription Description of the field.
		 *
		 */
		base_field(
			const std::string& aTitle,
			const std::string& aDescription);

		/**	Virtual destructor.
		 *
		 */
		virtual ~base_field() = 0;

		/**	Returns the title of the field.
		 *
		 * @returns Title of the field.
		 */
		std::string getTitle() const;

		/**	Returns the description of the field.
		 *
		 * @returns description of the field.
		 */
		std::string getDescription() const;

		/**	Sets the title of the field.
		 *
		 * @param [in] aTitle New title for the field.
		 * @post Title of the field has been set to the given parameter.
		 */
		void setTitle(const std::string& aTitle);

		/**	Sets the description of the field.
		 *
		 * @param [in] aTitle New description for the field.
		 * @post Description of the field has been set to the given parameter.
		 */
		void setDescription(const std::string& aDescription);

		/**	Returns the JSON representation of the field. Even though it is
		 *	declared abstract, it has a default implementation available. It
		 *	returns the title and description of the base_field as follows:
		 *
		 *			{ "title" : "TITLE", "description" : "DESCRIPTION" }
		 *
		 * @returns The JSON representation of the field.
		 */
		virtual std::string getJSON() const = 0;

	private:
		std::string mTitle;
		std::string mDescription;
	};
	
	/**	Base class for all variable fields. Implements interface for returning
	 * 	the JSON representation of its data.
	 *
	 */
	class var_field : public base_field
	{
	public:

		/**	Constructor.
		 *
		 *	@param [in] aTitle Title of the field.
		 *	@param [in] aDescription Description of the field.
		 */
		var_field(
			const std::string& aTitle,
			const std::string& aDescription);

		/**	Virtual destructor.
		 *
		 */
		virtual ~var_field() {};

		/**	Tries to set the object to the JSON received.
		 *
		 *	Supported fields:
		 *		title - string\n
		 *		description - string\n
		 *
		 *
		 *	Example JSON object accepted:
		 * 
		 *			{ "title" : "foo", "description" : "bar" }
		 *			{ "title" : "foo" }
		 *			{ "description" : "bar" }
		 *
		 * @returns True upon success, false otherwise.
		 */
		virtual bool setJSON(const JSON& aJSON) = 0;
	};

	/**	Class representing a collection of groups and items.
	 *
	 *	@tparam T Type of the items in the group and any nested groups.
	 */
	template <class T>
	class group : public base_field
	{
	public:

		/**	Constructor.
		 *
		 *	@param [in] aTitle Title of the field.
		 *	@param [in] aDescription Description of the field.
		 */
		group(const std::string& aTitle, const std::string& aDescription);

		/**	Destructor.
		 *
		 */
		virtual ~group() {};

		/**	Adds the given field to the group.
		 *
		 *	@param [in] apField Pointer to the field to add to the group. If the
		 *		pointer is NULL, nothing happens.
		 *
		 *	@post Group has associated the given field with itself. If the
		 *		parameter is NULL, nothing happened.
		 */
		void add(T *apField);

		/**	Adds the given group to the group.
		 *
		 *	@param [in] apField Pointer to the group to add to the group. If
		 *		the pointer is NULL, nothing happens.
		 *
		 *	@post Group has associated the given group with itself if the
		 *		parameter is not NULL, else nothing happened.
		 */
		void add(group<T> *apField);

		/**	Removes the given field from the group.
		 *
		 *	@param [in] aName Name of the field to remove.
		 *
		 *	@returns A pointer to the removed item, or NULL if no item was
		 *		removed.
		 *	@post Group has removed the field given from itself if it was found.
		 */
		T* removeItem(const std::string& aName);

		/**	Removes the given group from the group.
		 *
		 *	@param [in] aName Name of the group to remove.
		 *
		 *	@returns A pointer to the removed group, or NULL if no gruop was
		 *		removed.
		 *	@post Group has removed the group given from itself. If the group
		 *		does not exist, nothing happens.
		 */
		group<T>* removeGroup(const std::string& aName);

		//@{
		/**	Finds the given field in the group.
		 *
		 *	@param [in] aName Name of the field to find.
		 *
		 *	@returns Pointer to the field specified to be found by its name if
		 *		it was found. NULL is returned otherwise.
		 */
		T *findItem(const std::string& aName);
		const T *findItem(const std::string& aName) const;
		//@}

		//@{
		/**	Finds the given group in the group.
		 *
		 *	@param [in] aName Name of the group to find.
		 *
		 *	@returns Pointer to the group specified to be found by its name if
		 *		it was found. NULL is returned otherwise.
		 */
		group<T> *findGroup(const std::string& aName);
		const group<T> *findGroup(const std::string& aName) const;
		//@}

		/**	Gets the number of groups and items found within the group.
		 *
		 *	@returns The number of groups and items found within the group.
		 */
		std::size_t getSize() const;

		/**	Returns the JSON representation of the field.
		 *
		 *	Each subclass of var_field is in charge of defining the output of
		 *	this function.
		 *
		 *	@see base_field::getJSON for more details.
		 *
		 *	@returns The JSON representation of the field.
		 */
		std::string getJSON() const;

	private:
		std::list<std::string> mInsertOrder;
		std::map<std::string, T*> mItems;
		std::map<std::string, group<T>*> mGroups;
	};
}

#include "base.ipp"

#endif//_OUROBOROS_BASE_HPP_
