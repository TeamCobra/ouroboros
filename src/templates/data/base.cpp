#include <string>
#include <memory>
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


	var_field::var_field(const std::string& aTitle, const std::string& aDescription, const std::string& aValue)
	:base_field(aTitle, aDescription), mValue(aValue)
	{}

	var_field::~var_field() {}

	std::string var_field::getValue() const
	{
			return mValue;
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
	:var_field(aTitle, aDescription, aValue), mPattern(aPattern), mLength(aLength), mMinLength(aMinLength), mMaxLength(aMaxLength)
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

	base_integer::base_integer(const std::string& aTitle, const std::string& aDescription, const std::string& aValue, std::size_t aMinInclusive, std::size_t aMaxInclusive, std::size_t aMinExclusive, std::size_t aMaxExclusive)
	:var_field(aTitle, aDescription, aValue), mMaxInclusive(aMaxInclusive), mMinInclusive(aMinInclusive)
	{}
	
	std::size_t base_integer::getMaxInclusive() const
	{
		return mMaxInclusive;
	}

	std::size_t base_integer::getMinInclusive() const
	{
		return mMinInclusive;
	}

	std::size_t base_integer::getMaxExclusive() const
	{
		//return mMaxExclusive;
		return 0;
	}

	std::size_t base_integer::getMinExclusive() const
	{
		//return mMinExclusive;
		return 0;
	}

	void base_integer::setMaxInclusive(const std::size_t& aMaxInclusive)
	{
		mMaxInclusive = aMaxInclusive;
	}
	
	void base_integer::setMinInclusive(const std::size_t& aMinInclusive)
	{
		mMinInclusive = aMinInclusive;
	}
	
	void base_integer::setMaxExclusive(const std::size_t& aMaxExclusive)
	{
	
	}

	void base_integer::setMinExclusive(const std::size_t& aMinExclusive)
	{
	
	}
}
