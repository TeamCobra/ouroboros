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
		base_field() = default;
		virtual ~base_field() = 0;
	private:
		std::string mTitle;
		std::string mDesc;
	};

	class group : base_field
	{
	public:
		group() = default;
		virtual ~group() = default;
		void add(std::unique_ptr<base_field>& aField);
		base_field *get(std::size_t aIndex) const;
		std::size_t getSize() const;
		base_field *find() const;
		std::unique_ptr<base_field>& remove();
	};

	class base_string
	{
	public:
		std::string getValue() const;
		std::string getPattern() const;
		std::size_t getLength() const;
		std::size_t getMinLength() const;
		std::size_t getMaxLength() const;
		bool getConstant() const;

		void setValue() const;
		void setPattern() const;
		void setLength() const;
		void setMinLength() const;
		void setMaxLength() const;
		void setConstant() const;

	private:
		std::string mValue;
		std::string mPattern;
		std::size_t mLength;
		std::size_t mMinLength;
		std::size_t mMaxLength;
		bool mConstant;
	};

	class base_integer
	{
	public:

	private:
		std::size_t mMaxInclusive;
		std::size_t mMinInclusive;
		std::size_t mValue;
		bool mConstant;
	};
}

#endif//_OUROBOROS_BASE_HPP_
