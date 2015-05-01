#include <sstream>
#include <limits>

namespace ouroboros
{
	template<class Number>
	base_floating<Number>::base_floating()
	:var_field("", ""), mRange(
		-std::numeric_limits<Number>::max(), std::numeric_limits<Number>::max()),
		mValue(0)
	{}
	
	template<class Number>
	base_floating<Number>::base_floating(
		const std::string& aTitle,
		const std::string& aDescription,
		Number aValue,
		const std::pair<Number,Number>& aRange)
	:var_field(aTitle, aDescription), mValue(aValue)
	{
		if (!setInclusiveRange(aRange))
		{
			throw(std::out_of_range("Given value is out of range!"));
		}
	}
	
	template<class Number>
	std::pair<Number,Number> base_floating<Number>::getInclusiveRange() const
	{
		return mRange;
	}

	template<class Number>
	bool base_floating<Number>::setInclusiveRange(const std::pair<Number,Number>& aRange)
	{
		bool result = setInclusiveRange(aRange, mValue);
		return result;
	}
	
	template<class Number>
	bool base_floating<Number>::setInclusiveRange(const std::pair<Number,Number>& aRange, Number aValue)
	{
		std::pair<Number,Number> orig_range = mRange;
		
		mValue = aValue;
		mRange.first = std::min(aRange.first, aRange.second);
		mRange.second = std::max(aRange.first, aRange.second);
		
		if (mRange.first >= -std::numeric_limits<Number>::max() && mRange.second <= std::numeric_limits<Number>::max() && checkValidity(aValue))
		{
			mValue = aValue;
			return true;
		}
		
		mRange = orig_range;
		return false;
	}
	
	template<class Number>
	bool base_floating<Number>::setNumber(Number aNum)
	{
		if (checkValidity(aNum))
		{
			mValue = aNum;
			return true;
		}
		return false;
	}
	
	template<class Number>
	std::string base_floating<Number>::getJSON() const
	{
		std::stringstream ss;
		ss << "{ \"type\" : \"base_floating\", ";
		
		std::string base = var_field::getJSON();
		base.erase(base.find_first_of('{'), 1);
		base.erase(base.find_last_of('}'), 1);
		
		ss << base << ", \"value\" : " << mValue << ", ";
		ss << "\"range\" : [ " << mRange.first << ", " << mRange.second << " ]";
		ss << " }";
		
		return ss.str();;
	}
	
	template<class Number>
	bool base_floating<Number>::setJSON(const JSON& aJSON)
	{
		base_floating backup(*this);
		bool result = true, found = false;
		if (aJSON.exists("title"))
		{
			found = true;
			this->setTitle(aJSON.get("title"));
		}
		if (aJSON.exists("description"))
		{
			found = true;
			this->setDescription(aJSON.get("description"));
		}

		std::stringstream ss;
		if (aJSON.exists("value"))
		{
			Number num;
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
			Number min, max;
			
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

			if (!ss || !result || !this->setInclusiveRange(std::pair<Number,Number>(min, max)))
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

	template<class Number>
	bool base_floating<Number>::checkValidity (Number aInt)
	{
		if (mRange.first <= aInt && aInt <= mRange.second)
		{
			return true;
		}
		return false;
	}
}
