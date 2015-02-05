#include "base_integer.h"
#include <limits>

namespace ouroboros
{
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
	
	std::string base_integer::getJSON() const
	{
		return std::string(
			"{ \"base\" : " + var_field::getJSON() + ", \"value\" : " + std::to_string(mValue) + " }");
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