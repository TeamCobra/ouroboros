#include "base.hpp"

#include <string>
#include <memory>
#include <algorithm>
#include <utility>
#include <stdexcept>


namespace ouroboros
{
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

	base_string::base_string(
		const std::string& aTitle,
		const std::string& aDescription,
		const std::string& aValue,
		const std::string& aPattern,
		std::size_t aLength,
		std::pair<std::size_t, std::size_t> aLengthRange)
	:var_field(aTitle, aDescription), mPattern(aPattern), mLength(aLength), 
		mLengthRange(aLengthRange), mValue(aValue)
	{
		//check string pattern TODO
		
		//check string size range
		if (mLengthRange.first > mValue.length() || mLengthRange.second < mValue.length())
		{
			throw std::out_of_range("Length of value is outside of the range specified!");
		}
		
	}

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
		return mLengthRange.first;
	}

	std::size_t base_string::getMaxLength() const
	{
		return mLengthRange.second;
	}
	
	std::string base_string::getValue() const
	{
		return std::string(
			"{ \"base\" : " + var_field::getValue() + ", \"value\" : \"" + mValue + "\" }");
	}

	bool base_string::setPattern(const std::string& aPattern, const std::string& aNewValue)
	{
		bool success = true;
		//TODO check if new pattern matches current strings, and/or new string
		mPattern = aPattern;
		return success;
	}

	bool base_string::setLength(const std::size_t& aLength, const std::string& aNewValue)
	{
		bool success = true;
		mLength = aLength;
		return success;
	}

	bool base_string::setMinLength(const std::size_t& aMinLength, const std::string& aNewValue)
	{
		if (aMinLength > mLengthRange.second)
			return false;
		
		if (!aNewValue.empty() && aNewValue.length() >= aMinLength && aNewValue.length() <= mLengthRange.second)
		{
			mValue = aNewValue;
			mLengthRange.first = aMinLength;
		}
		else if(mValue.length() >= aMinLength)
		{
			mLengthRange.first = aMinLength;
		}
		else
		{
			return false;
		}
		return true;
	}

	bool base_string::setMaxLength(const std::size_t& aMaxLength, const std::string& aNewValue)
	{
		if (aMaxLength < mLengthRange.first)
			return false;
		
		if (!aNewValue.empty() && aNewValue.length() <= aMaxLength && aNewValue.length() >= mLengthRange.first)
		{
			mValue = aNewValue;
			mLengthRange.second = aMaxLength;
		}
		else if(mValue.length() <= aMaxLength)
		{
			mLengthRange.second = aMaxLength;
		}
		else
		{
			return false;
		}
		return true;
	}
	
	void base_string::setString(const std::string& aString)
	{
		mValue = aString;
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
