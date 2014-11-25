#ifndef _OUROBOROS_BASE_HPP_
#define _OUROBOROS_BASE_HPP_

#include <string>
#include <memory>

namespace ouroboros
{
	//Have this verify that our code generator is generating valid structures
	bool validateStructure();

	class base_field
	{
	public:
		base_field(const std::string& aTitle, const std::string& aDescription);
		virtual ~base_field() = 0;

		std::string getTitle() const;
		std::string getDescription() const;

		void setTitle(const std::string& aTitle);
		void setDescription(const std::string& aDescription);
	private:
		std::string mTitle;
		std::string mDescription;
	};

	class var_field : base_field
	{
	public:
		var_field(const std::string& aTitle, const std::string& aDescription, const std::string& aValue);
		virtual ~var_field() = 0;

		std::string getValue() const;
	private:
		std::string mValue;
	};

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

	class base_string : var_field
	{
	public:
		base_string(const std::string& aTitle, const std::string& aDescription, const std::string& aValue, const std::string& aPattern, std::size_t aLength, std::size_t aMinLength, std::size_t aMaxLength);
		std::string getPattern() const;
		std::size_t getLength() const;
		std::size_t getMinLength() const;
		std::size_t getMaxLength() const;

		void setPattern(const std::string& aPattern);
		void setLength(const std::size_t& aLength);
		void setMinLength(const std::size_t& aMinLength);
		void setMaxLength(const std::size_t& aMaxLength);

	private:
		std::string mPattern;
		std::size_t mLength;
		std::size_t mMinLength;
		std::size_t mMaxLength;
	};

	class base_integer : var_field
	{
	public:
		base_integer(const std::string& aTitle, const std::string& aDescription, const std::string& aValue, std::size_t aMinInclusive, std::size_t aMaxInclusive, std::size_t aMinExclusive, std::size_t aMaxExclusive);

		std::size_t getMaxInclusive() const;
		std::size_t getMinInclusive() const;
		std::size_t getMaxExclusive() const;
		std::size_t getMinExclusive() const;

		void setMaxInclusive(const std::size_t& aMaxInclusive);
		void setMinInclusive(const std::size_t& aMinInclusive);
		void setMaxExclusive(const std::size_t& aMaxExclusive);
		void setMinExclusive(const std::size_t& aMinExclusive);

	private:
		std::size_t mMaxInclusive;
		std::size_t mMinInclusive;
	};
}

#endif//_OUROBOROS_BASE_HPP_
