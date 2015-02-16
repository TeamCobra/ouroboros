#include "base_string.h"
#include <limits>
#include <sstream>

namespace ouroboros
{
	base_string::base_string()
	:var_field("", ""), mPattern(""), mLength(0),
		mLengthRange(
			std::numeric_limits<std::size_t>::min(),
			std::numeric_limits<std::size_t>::max()),
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
	
	std::string base_string::getJSON() const
	{
		std::stringstream ss;
		std::string len, range_l, range_h;
		ss << mLength;
		len = ss.str();
		ss.clear();
		ss.str("");
		ss << mLengthRange.first;
		range_l = ss.str();
		ss.clear();
		ss.str("");
		ss << mLengthRange.second;
		range_h = ss.str();

		return std::string(
			"{ \"type\" : \"base_string\", "
			"\"base\" : " + var_field::getJSON() + ", " +
			"\"value\" : \"" + mValue + "\" ," +
			"\"pattern\" : \"" + mPattern + "\" ," +
			"\"length\" : " + len + " ," +
			"\"range\" : [" + range_l + ", "
				+ range_h + "] }");
	}
	
	bool base_string::setJSON(const JSON& aJSON)
	{
		base_string backup(*this);
		bool result = true, found = false;
		if (aJSON.exists("base.title"))
		{
			found = true;
			base_field::setTitle(aJSON.get("base.title"));
		}
		if (aJSON.exists("base.description"))
		{
			found = true;
			base_field::setDescription(aJSON.get("base.description"));
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
			std::stringstream ss;

			ss << aJSON.get("length");
			ss >> num;

			if (!ss || !result || !this->setLength(num))
			{
				result = false;
			}
		}

		if (result && aJSON.exists("range[0]") && aJSON.exists("range[1]"))
		{
			found = true;
			std::size_t min, max;
			std::stringstream ss;

			ss << aJSON.get("range[0]");
			ss >> min;

			if (!!ss)
			{
				ss.clear();
				ss.str("");
				ss << aJSON.get("range[1]");
				ss >> max;
			}

			if (!ss || !result || !this->setMinLength(min) || !this->setMaxLength(max))
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
}
