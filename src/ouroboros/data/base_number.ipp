#include <sstream>
#include <limits>
#include <typeinfo>

//This header is not in C++03, but it can be found online if the platform does
//not already support C99. Most modern Linux systems have stdint.h in their
//include folders, so it should be picked up automatically.
#include <stdint.h>

namespace ouroboros
{
	template<class Number, Number Min, Number Max>
	base_number<Number, Min, Max>::base_number()
	:var_field("", ""), mRange(
		Min, Max),
		mValue(0)
	{}

	template<class Number, Number Min, Number Max>
	base_number<Number, Min, Max>::base_number(
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

	template<class Number, Number Min, Number Max>
	std::pair<Number,Number> base_number<Number, Min, Max>::getInclusiveRange() const
	{
		return mRange;
	}

	template<class Number, Number Min, Number Max>
	bool base_number<Number, Min, Max>::setInclusiveRange(const std::pair<Number,Number>& aRange)
	{
		bool result = setInclusiveRange(aRange, mValue);
		return result;
	}

	template<class Number, Number Min, Number Max>
	bool base_number<Number, Min, Max>::setInclusiveRange(const std::pair<Number,Number>& aRange, Number aValue)
	{
		std::pair<Number,Number> orig_range = mRange;

		mValue = aValue;
		mRange.first = std::min(aRange.first, aRange.second);
		mRange.second = std::max(aRange.first, aRange.second);

		if (mRange.first >= Min && mRange.second <= Max && checkValidity(aValue))
		{
			mValue = aValue;
			return true;
		}

		mRange = orig_range;
		return false;
	}

	template<class Number, Number Min, Number Max>
	bool base_number<Number, Min, Max>::setNumber(Number aNum)
	{
		if (checkValidity(aNum))
		{
			mValue = aNum;
			return true;
		}
		return false;
	}

	template<class Number, Number Min, Number Max>
	Number base_number<Number, Min, Max>::getNumber() const
	{
		return mValue;
	}

	template<class Number, Number Min, Number Max>
	std::string base_number<Number, Min, Max>::getJSON() const
	{
		std::stringstream ss;
		ss << "{ \"type\" : \"";

		if (typeid(Number) == typeid(uint8_t))
		{
			ss << "unsigned byte";
		}
		else if (typeid(Number) == typeid(int8_t))
		{
			ss << "signed byte";
		}
		else if (typeid(Number) == typeid(uint16_t))
		{
			ss << "unsigned 16-bit number";
		}
		else if (typeid(Number) == typeid(int16_t))
		{
			ss << "signed 16-bit number";
		}
		else if (typeid(Number) == typeid(uint32_t))
		{
			ss << "unsigned 32-bit number";
		}
		else if (typeid(Number) == typeid(int32_t))
		{
			ss << "signed 32-bit number";
		}
		else if (typeid(Number) == typeid(uint64_t))
		{
			ss << "unsigned 64-bit number";
		}
		else if (typeid(Number) == typeid(int64_t))
		{
			ss << "signed 64-bit number";
		}
		else
		{
			ss << "unknown number type";
		}
		ss << "\", ";

		ss << "\"absolute range\" : [ " << Min << ", " << Max << " ], ";

		std::string base = var_field::getJSON();
		base.erase(base.find_first_of('{'), 1);
		base.erase(base.find_last_of('}'), 1);

		ss << base << ", \"value\" : " << mValue << ", ";
		ss << "\"range\" : [ " << mRange.first << ", " << mRange.second << " ]";
		ss << " }";

		return ss.str();;
	}

	template<class Number, Number Min, Number Max>
	bool base_number<Number, Min, Max>::setJSON(const JSON& aJSON)
	{
		base_number backup(*this);
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

	template<class Number, Number Min, Number Max>
	bool base_number<Number, Min, Max>::checkValidity (Number aInt)
	{
		if (mRange.first <= aInt && aInt <= mRange.second)
		{
			return true;
		}
		return false;
	}
}
