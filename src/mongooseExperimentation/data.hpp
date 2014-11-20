#ifndef _OUROBOROS_DATA_HPP_
#define _OUROBOROS_DATA_HPP_

#include <set>
#include <string>
#include <memory>
#include <vector>

namespace ouroboros
{
	namespace detail
	{
		template <class T>
		class Identifier
		{
		public:
			Identifier(const T& aID);
			bool operator==(const T& aIdentifier);
			T getID();
		private:
			T mID;
		};
	}

	class Field
	{
	public:
		Field(const std::string& aName);
		~Field() = default;

		std::string getName();
		bool operator==(const Field& aField);

	private:
		detail::Identifier<std::string> mIdentifier;
		//
	};

	class Group
	{
	public:
		Group(const std::string& aName);
		~Group() = default;

		std::string getName();
		bool operator==(const Group& aGroup);

		void insertField(std::unique_ptr<Field>&& apField);
		Field& getField(const std::string& aName);
		void removeField(const std::string& aName);

		void insertGroup(const std::unique_ptr<Group>&& apGroup);
		Group& getGroup(const std::string& aName);
		void deleteGroup(const std::string& aName);

	private:
		detail::Identifier<std::string> mIdentifier;
		std::vector<std::unique_ptr<Field>> &mFields;
	};

}

#endif//_OUROBOROS_DATA_HPP_
