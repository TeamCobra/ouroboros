#ifndef _OUROBOROS_BASE_HPP_
#define _OUROBOROS_BASE_HPP_

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <map>

namespace ouroboros
{
	//Have this verify that our code generator is generating valid structures
	bool validateStructure();

	class base_field
	{
	public:
		base_field(
			const std::string& aTitle,
			const std::string& aDescription);
		virtual ~base_field() = 0;

		std::string getTitle() const;
		std::string getDescription() const;

		void setTitle(const std::string& aTitle);
		void setDescription(const std::string& aDescription);
	private:
		std::string mTitle;
		std::string mDescription;
	};

	class var_field : public base_field
	{
	public:
		var_field(
			const std::string& aTitle,
			const std::string& aDescription);

		virtual ~var_field() = default;

		virtual std::string getValue() const = 0; //has a default implementation available.
	};

	template <class T>
	class group : base_field
	{
	public:
		group(const std::string& aTitle, const std::string& aDescription);
		virtual ~group() = default;

		void add(T *apField);
		void add(group<T> *apField);
		T* removeItem(const std::string& aName);
		group<T>* removeGroup(const std::string& aName);

		T *findItem(const std::string& aName);
		group<T> *findGroup(const std::string& aName);
		const T *findItem(const std::string& aName) const;
		const group<T> *findGroup(const std::string& aName) const;

		std::size_t getSize() const;
		
	private:
		std::string aTitle;
		std::map<std::string, T*> mItems;
		std::map<std::string, group<T>*> mGroups;
	};

	class base_string : public var_field
	{
	public:
		base_string(
			const std::string& aTitle,
			const std::string& aDescription,
			const std::string& aValue,
			const std::string& aPattern,
			std::size_t aLength, std::size_t aMinLength,
			std::size_t aMaxLength);

		std::string getPattern() const;
		std::size_t getLength() const;
		std::size_t getMinLength() const;
		std::size_t getMaxLength() const;

		void setPattern(const std::string& aPattern);
		void setLength(const std::size_t& aLength);
		void setMinLength(const std::size_t& aMinLength);
		void setMaxLength(const std::size_t& aMaxLength);
		
		virtual std::string getValue() const override;

	private:
		std::string mPattern;
		std::size_t mLength;
		std::size_t mMinLength;
		std::size_t mMaxLength;
		
		std::string mValue;
	};

	class base_integer : public var_field
	{
	public:
		base_integer(
			const std::string& aTitle,
			const std::string& aDescription,
			int aValue,
			const std::pair<int,int>& aRange);

		std::pair<int,int> getInclusiveRange() const;

		void setInclusiveRange(const std::pair<int,int>& aPair);
		
		
		virtual std::string getValue() const override;

	private:
		std::pair<int, int> mRange;
		
		int mValue;
	};
}

#include "base.ipp"

#endif//_OUROBOROS_BASE_HPP_
