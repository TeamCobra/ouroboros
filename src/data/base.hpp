#ifndef _OUROBOROS_BASE_HPP_
#define _OUROBOROS_BASE_HPP_

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <map>

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
		 *	@param aTitle Title of the field.
		 *	@param aDescription Description of the field.
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
		 * @param aTitle New title for the field.
		 * @post Title of the field has been set to the given parameter.
		 */
		void setTitle(const std::string& aTitle);
		
		/**	Sets the description of the field.
		 *
		 * @param aTitle New description for the field.
		 * @post Description of the field has been set to the given parameter.
		 */
		void setDescription(const std::string& aDescription);

	private:
		std::string mTitle;
		std::string mDescription;
	};

	/**	Base class for all variable fields. Implements interface for returning
	 * 	the JSON representation of its data. (TODO Specify JSON format).
	 * 
	 */
	class var_field : public base_field
	{
	public:
		
		/**	Constructor.
		 *
		 *	@param aTitle Title of the field.
		 *	@param aDescription Description of the field. 
		 */
		var_field(
			const std::string& aTitle,
			const std::string& aDescription);

		/**	Virtual destructor.
		 * 
		 */
		virtual ~var_field() = default;

		/**	Returns the JSON representation of the field. Even though it is
		 *	declared abstract, it has a default implementation available (TODO
		 *	describe what it is).
		 *
		 * @returns The JSON representation of the field.
		 */
		virtual std::string getValue() const = 0;
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
		 *	@param aTitle Title of the field.
		 *	@param aDescription Description of the field. 
		 */
		group(const std::string& aTitle, const std::string& aDescription);

		/**	Destructor.
		 * 
		 */
		virtual ~group() = default;

		//TODO Specify move, copy constructors and assignment operator
		
		/**	Adds the given field to the group. FIXME Who's responsibility is to keep track of the lifecycle of the pointer?
		 * 
		 *	@param apField Pointer to the field to add to the group.
		 * 
		 *	@post Group has associated the given field with itself.
		 */
		void add(T *apField);
		
		/**	Adds the given group to the group. FIXME Who's responsibility is to keep track of the lifecycle of the pointer?
		 * 
		 *	@param apField Pointer to the group to add to the group.
		 * 
		 *	@post Group has associated the given group with itself.
		 */
		void add(group<T> *apField);
		
		/**	Removes the given field from the group.
		 * 
		 *	@param aName Name of the field to remove.
		 * 
		 *	@post Group has removed the field given from itself. If the field
		 *		does not exist, nothing happens.
		 */
		T* removeItem(const std::string& aName);
		
		/**	Removes the given group from the group.
		 * 
		 *	@param aName Name of the group to remove.
		 * 
		 *	@post Group has removed the group given from itself. If the group
		 *		does not exist, nothing happens.
		 */
		group<T>* removeGroup(const std::string& aName);

		///@{
		/**	Finds the given field in the group.
		 * 
		 *	@param aName Name of the field to find.
		 * 
		 *	@returns Pointer to the field specified to be found by its name if
		 *		it was found. std::nullptr is returned otherwise.
		 */
		T *findItem(const std::string& aName);
		const T *findItem(const std::string& aName) const;
		///@}
		
		///@{
		/**	Finds the given group in the group.
		 * 
		 *	@param aName Name of the group to find.
		 * 
		 *	@returns Pointer to the group specified to be found by its name if
		 *		it was found. std::nullptr is returned otherwise.
		 */
		group<T> *findGroup(const std::string& aName);
		const group<T> *findGroup(const std::string& aName) const;
		///@}
		
		/**	Gets the number of groups and items found within the group.
		 *
		 *	@returns The number of groups and items found within the group.
		 */
		std::size_t getSize() const;

	private:
		std::map<std::string, T*> mItems;
		std::map<std::string, group<T>*> mGroups;
	};

	/**	Class representing a string field.
	 * 
	 */
	class base_string : public var_field
	{
	public:
		/**	Constructor.
		 *
		 *	@param aTitle Title of the field.
		 *	@param aDescription Description of the field.
		 *	@param aValue Contents of the string.
		 *	@param aPattern Pattern to match the content of the string to. (FIXME should this be matched in the constructor too and throw and exception if it is bad?)
		 *	@param aLength FIXME What is this field for?
		 *	@param aMinLength Minimum length of the string (inclusive). (FIXME What happens if the original value is too small?)
		 *	@param aMaxLength Maximum length of the string (exclusive). (FIXME What happens if the original value is too small?)
		 */
		base_string(
			const std::string& aTitle,
			const std::string& aDescription,
			const std::string& aValue,
			const std::string& aPattern,
			std::size_t aLength, 
			std::size_t aMinLength,
			std::size_t aMaxLength);

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

		/**	Sets the pattern to match the contents of the string field to.
		 *
		 *	@param aPattern The new pattern to match the contents of the string
		 *		field to.
		 */
		void setPattern(const std::string& aPattern);
		
		/**	Sets the FIXME see constructor for questions.
		 *
		 *	@returns The ?.
		 */
		void setLength(const std::size_t& aLength);
		
		/**	Sets the minimum length (inclusive) of the string field. FIXME What should happen if the current string violates the new minimum?
		 *
		 *	@param aMinLength The new minimum length (inclusive) of the string
		 *		field.
		 */
		void setMinLength(const std::size_t& aMinLength);
		
		/**	Sets the maximum length (inclusive) of the string field. FIXME What should happen if the current string violates the new maximum?
		 *
		 *	@param aMaxLength The new maximum length (inclusive) of the string
		 *		field.
		 */
		void setMaxLength(const std::size_t& aMaxLength);
		
		/**	Sets the current string value of the string field.
		 *
		 *	@param aMinLength The new string value.
		 */
		void setString(const std::string& aValue);
		
		/**	Returns the JSON representation of the string field.
		 * 
		 * @see ouroboros::var_field::get_value()
		 */
		virtual std::string getValue() const override;

	private:
		std::string mPattern;
		std::size_t mLength;
		std::size_t mMinLength;
		std::size_t mMaxLength;
		
		std::string mValue;
	};
	/**	Class representing an integer field.
	 *
	 */ 
	class base_integer : public var_field
	{
	public:
		
		/**	Constructor.
		 *
		 *	@param aTitle Title of the field.
		 *	@param aDescription Description of the field.
		 *	@param aValue Contents of the integer field..
		 *	@param aRange A pair of values specifying the valid range
		 *		(inclusive) for the integer (lower first, higher second). FIXME What if the value specified does not meet the range requirement?
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
		 */
		void setInclusiveRange(const std::pair<int,int>& aPair);
		
		/**	Returns the JSON representation of the integer field.
		 * 
		 * @see ouroboros::var_field::get_value()
		 */
		virtual std::string getValue() const override;

	private:
		std::pair<int, int> mRange;
		int mValue;
	};
}

#include "base.ipp"

#endif//_OUROBOROS_BASE_HPP_
