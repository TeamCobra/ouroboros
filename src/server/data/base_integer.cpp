#include "base_integer.h"
#include <sstream>
#include <limits>

namespace ouroboros
{
	base_integer::base_integer()
	:var_field("", ""), mValue(0), mRange(
		std::numeric_limits<int>::min(), std::numeric_limits<int>::max())
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
		std::pair<int,int> orig_range = mRange;
		
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
	
	std::string base_integer::getJSON() const
	{
		std::stringstream ss;
		ss << mValue;
		return std::string(
			"{ \"base\" : " + var_field::getJSON() + ", \"value\" : " + ss.str() + " }");
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
			this->setDescription(aJSON.get("base.description"));
		}

		std::stringstream ss;
		if (aJSON.exists("value"))
		{
			int num;
			found = true;

			ss << aJSON.get("value");
			ss >> num;

			if (!ss || !result || !this->setNumber(num))
			{
				result = false;
			}

			ss.clear();
			ss.str("");
		}

		if (result && aJSON.exists("range[0]") && aJSON.exists("range[1]"))
		{
			found = true;
			int min, max;
			
			ss << aJSON.get("range[0]");
			ss >> min;
			if (!ss)
			{
				result = false;
			}
			else
			{
				ss.clear();
				ss.str("");

				ss << aJSON.get("range[1]");
				ss >> max;
				if (!ss)
				{
					result = false;
				}
			}

			if (!ss || !result || !this->setInclusiveRange(std::pair<int,int>(min, max)))
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
