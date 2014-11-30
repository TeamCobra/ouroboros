#include <string>
#include <memory>
#include <algorithm>
#include <utility>
#include "base.hpp"

namespace ouroboros
{
	//Have this verify that our code generator is generating valid structures
	bool validateStructure();

	base_field::base_field(const std::string& aTitle, const std::string& aDescription)
	:mTitle(aTitle), mDescription(aDescription)
	{}

	base_field::~base_field() {}

	std::string base_field::getTitle() const
	{
		return mTitle;
	}

	std::string base_field::getDescription() const
	{
		return mDescription;
	}

	void base_field::setTitle(const std::string& aTitle)
	{
		mTitle = aTitle;
	}

	void base_field::setDescription(const std::string& aDescription)
	{
		mDescription = aDescription;
	}


	var_field::var_field(const std::string& aTitle, const std::string& aDescription)
	:base_field(aTitle, aDescription)
	{}

	std::string var_field::getValue() const
	{
			return std::string(
				"{ \"title\" : \"" + this->getTitle() + "\", "
				"\"description\" : \"" + this->getDescription() + "\" }");
	}

/*
	class group
	{
	public:
		group() = default;
		virtual ~group() = default;

		void add(std::unique_ptr<base_field>&& aField);
		std::unique_ptr<base_field>&& remove();

		base_field *get(std::size_t aIndex) const;
		base_field *find(std::string aName) const;

		std::size_t getSize() const;
	};
*/

	base_string::base_string(const std::string& aTitle, const std::string& aDescription, const std::string& aValue, const std::string& aPattern, std::size_t aLength, std::size_t aMinLength, std::size_t aMaxLength)
	:var_field(aTitle, aDescription), mPattern(aPattern), mLength(aLength), mMinLength(aMinLength), mMaxLength(aMaxLength), mValue(aValue)
	{}

	std::string base_string::getPattern() const
	{
		return mPattern;
	}

	std::size_t base_string::getLength() const
	{
		return mLength;
	}

	std::size_t base_string::getMinLength() const
	{
		return mMinLength;
	}

	std::size_t base_string::getMaxLength() const
	{
		return mMaxLength;
	}
	
	std::string base_string::getValue() const
	{
			return std::string(
				"{ \"base\" : " + var_field::getValue() + ", \"value\" : \"" + mValue + "\" }");
	}

	void base_string::setPattern(const std::string& aPattern)
	{
		mPattern = aPattern;
	}

	void base_string::setLength(const std::size_t& aLength)
	{
		mLength = aLength;
	}

	void base_string::setMinLength(const std::size_t& aMinLength)
	{
		mMinLength = aMinLength;
	}

	void base_string::setMaxLength(const std::size_t& aMaxLength)
	{
		mMaxLength = aMaxLength;
	}

	base_integer::base_integer(
		const std::string& aTitle,
		const std::string& aDescription,
		int aValue,
		const std::pair<int,int>& aRange)
	:var_field(aTitle, aDescription), mValue(aValue)
	{
		mRange.first = std::min(aRange.first, aRange.second);
		mRange.second = std::max(aRange.first, aRange.second);
		
	}
	
	std::pair<int,int> base_integer::getInclusiveRange() const
	{
		return mRange;
	}

	void base_integer::setInclusiveRange(const std::pair<int,int>& aRange)
	{
		mRange = aRange;
	}
	
	std::string base_integer::getValue() const
	{
			return std::string(
				"{ \"base\" : " + var_field::getValue() + ", \"value\" : " + std::to_string(mValue) + " }");
	}
}
