#include "base.hpp"

#include <string>
#include <memory>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <limits>
#include <data/JSON.h>

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
	
	base_string::base_string()
	:var_field("", ""), mPattern(""), mLength(0), 
		mLengthRange(
			{std::numeric_limits<std::size_t>::min(),
			std::numeric_limits<std::size_t>::max()}),
		mValue("")
	{}

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
		mLengthRange.first = std::min(aLengthRange.first, aLengthRange.second);
		mLengthRange.second = std::max(aLengthRange.first, aLengthRange.second);
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
			"{ \"type\" : \"base_string\", " 
			"\"base\" : " + var_field::getValue() + ", " +
			"\"value\" : \"" + mValue + "\" ," +
			"\"pattern\" : \"" + mPattern + "\" ," +
			"\"length\" : " + std::to_string(mLength) + " ," +
			"\"range\" : [" + std::to_string(mLengthRange.first) + ", "
				+ std::to_string(mLengthRange.second) + "] }");
	}
	
	bool base_string::setJSON(const JSON& aJSON)
	{
		base_string backup(*this);
		bool result = true, found = false;
		if (aJSON.exists("base.title"))
		{
			found = true;
			this->setTitle(aJSON.get("base.title"));
		}
		if (aJSON.exists("base.description"))
		{
			found = true;
			this->setDescription(aJSON.get("base.title"));
		}
		
		if (aJSON.exists("value"))
		{
			found = true;
			if (!this->setString(aJSON.get("value")))
			{
				result = false;
			}
		}
		if (result && aJSON.exists("pattern"))
		{
			found = true;
			if (!this->setPattern(aJSON.get("pattern")))
			{
				result = false;
			}
		}
		if (result && aJSON.exists("length"))
		{
			found = true;
			std::size_t num;
			try
			{
				num = std::stol(aJSON.get("length"));
			}
			catch (std::invalid_argument& e)
			{
				//do not change anything.
				result = false;
			}
			if (!result || !this->setLength(num))
			{
				result = false;
			}
		}
		if (result && aJSON.exists("range[0]") && aJSON.exists("range[1]"))
		{
			found = true;
			std::size_t min, max;
			try
			{
				min = std::stol(aJSON.get("range[0]"));
				max = std::stol(aJSON.get("range[1]"));
			}
			catch (std::invalid_argument& e)
			{
				//do not change anything.
				result = false;
			}
			
			if (!result || !this->setMinLength(min) || !this->setMaxLength(max))
			{
				result = false;
			}
		}
		
		if(!result)
		{
			*this = backup;
		}
		return result && found;
	}

	bool base_string::setPattern(const std::string& aPattern)
	{
		return setPattern(aPattern, mValue);
	}

	bool base_string::setLength(const std::size_t& aLength)
	{
		return setLength(aLength, mValue);
	}

	bool base_string::setMinLength(const std::size_t& aMinLength)
	{
		return setMinLength(aMinLength, mValue);
	}

	bool base_string::setMaxLength(const std::size_t& aMaxLength)
	{
		return setMaxLength(aMaxLength, mValue);
	}
	
	bool base_string::setPattern(const std::string& aPattern, const std::string& aNewValue)
	{
		bool success = true;
		//TODO check if new pattern matches current strings, and/or new string
		mPattern = aPattern;
		
		if (!aNewValue.empty() && checkValidity(aNewValue))
		{
			mValue = aNewValue;
		}
		
		return success;
	}

	bool base_string::setLength(const std::size_t& aLength, const std::string& aNewValue)
	{
		bool success = true;
		
		if (checkValidity(aNewValue))
		{
			mValue = aNewValue;
		}
		
		return success;
	}

	bool base_string::setMinLength(const std::size_t& aMinLength, const std::string& aNewValue)
	{
		if (aMinLength > mLengthRange.second)
			return false;
		
		const std::size_t oldMin = mLengthRange.first;
		mLengthRange.first = aMinLength;
		
		if (checkValidity(aNewValue))
		{
			mValue = aNewValue;
		}
		else if(mValue.length() < aMinLength)
		{
			mLengthRange.first = oldMin;
			return false;
		}
		return true;
	}

	bool base_string::setMaxLength(const std::size_t& aMaxLength, const std::string& aNewValue)
	{
		if (aMaxLength < mLengthRange.first)
			return false;
		
		const std::size_t oldMax = mLengthRange.second;
		mLengthRange.second = aMaxLength;
		
		if (checkValidity(aNewValue))
		{
			mValue = aNewValue;
		}
		else if(mValue.length() > aMaxLength)
		{
			mLengthRange.second = oldMax;
			return false;
		}
		return true;
	}
	
	bool base_string::setString(const std::string& aString)
	{
		if (checkValidity(aString))
		{
			mValue = aString;
			return true;
		}
		return false;
	}
	
	bool base_string::checkValidity (const std::string& aString)
	{
		if ((aString.length() >= mLengthRange.first) &&
			(aString.length() <= mLengthRange.second) &&
			(true /*TODO check for pattern match*/))
		{
			return true;
		}
		return false;
	}

	base_integer::base_integer()
	:var_field("", ""), mValue(0), mRange(
		{std::numeric_limits<int>::min(), std::numeric_limits<int>::max()})
	{}
	
	base_integer::base_integer(
		const std::string& aTitle,
		const std::string& aDescription,
		int aValue,
		const std::pair<int,int>& aRange)
	:var_field(aTitle, aDescription), mValue(aValue)
	{
		if (!setInclusiveRange(aRange))
		{
			throw(std::out_of_range("Given value is out of range!"));
		}
	}
	
	std::pair<int,int> base_integer::getInclusiveRange() const
	{
		return mRange;
	}

	bool base_integer::setInclusiveRange(const std::pair<int,int>& aRange)
	{
		return setInclusiveRange(aRange, mValue);
	}
	
	bool base_integer::setInclusiveRange(const std::pair<int,int>& aRange, int aValue)
	{
		auto orig_range = mRange;
		
		mValue = aValue;
		mRange.first = std::min(aRange.first, aRange.second);
		mRange.second = std::max(aRange.first, aRange.second);
		
		if (checkValidity(aValue))
		{
			mValue = aValue;
			return true;
		}
		
		mRange = orig_range;
		return false;
	}
	
	bool base_integer::setNumber(int aNum)
	{
		if (checkValidity(aNum))
		{
			mValue = aNum;
			return true;
		}
		return false;
	}
	
	std::string base_integer::getValue() const
	{
		return std::string(
			"{ \"base\" : " + var_field::getValue() + ", \"value\" : " + std::to_string(mValue) + " }");
	}
	
	bool base_integer::setJSON(const JSON& aJSON)
	{
		base_integer backup(*this);
		bool result = true, found = false;
		if (aJSON.exists("base.title"))
		{
			found = true;
			this->setTitle(aJSON.get("base.title"));
		}
		if (aJSON.exists("base.description"))
		{
			found = true;
			this->setDescription(aJSON.get("base.title"));
		}
		
		if (aJSON.exists("value"))
		{
			found = true;
			int num;
			try
			{
				num = std::stoi(aJSON.get("value"));
			}
			catch (std::invalid_argument& e)
			{
				//do not change anything.
				result = false;
			}
			if (!result || !this->setNumber(num))
			{
				result = false;
			}
		}
		if (result && aJSON.exists("range[0]") && aJSON.exists("range[1]"))
		{
			found = true;
			int min, max;
			try
			{
				min = std::stoi(aJSON.get("range[0]"));
				max = std::stoi(aJSON.get("range[1]"));
			}
			catch (std::invalid_argument& e)
			{
				//do not change anything.
				result = false;
			}
			
			if (!result || !this->setInclusiveRange({min, max}))
			{
				result = false;
			}
		}
		
		if(!result)
		{
			*this = backup;
		}
		return result && found;
		
	}
	
	bool base_integer::checkValidity (int aInt)
	{
		if (mRange.first <= aInt && aInt <= mRange.second)
		{
			return true;
		}
		return false;
	}
}
