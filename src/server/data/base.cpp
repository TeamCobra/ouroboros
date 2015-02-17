#include "base.hpp"

#include <string>
#include <memory>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <limits>
#include "JSON.h"

namespace ouroboros
{
	base_field::base_field(
		const std::string& aTitle, const std::string& aDescription)
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
	
	void var_field::setTitle(const std::string& aTitle)
	{
		base_field::setTitle(aTitle);
	}

	void var_field::setDescription(const std::string& aDescription)
	{
		base_field::setDescription(aDescription);
	}

	std::string base_field::getJSON() const
	{
		return std::string(
			"{ \"title\" : \"" + this->getTitle() + "\", "
			"\"description\" : \"" + this->getDescription() + "\" }");
	}
	
	bool var_field::setJSON(const JSON& aJSON)
	{
		bool found = false;
		if (aJSON.exists("title"))
		{
			found = true;
			base_field::setTitle(aJSON.get("title"));
			
		}
		if (aJSON.exists("description"))
		{
			found = true;
			base_field::setDescription(aJSON.get("description"));
		}

		return found;
	}

	var_field::var_field(
		const std::string& aTitle, const std::string& aDescription)
	:base_field(aTitle, aDescription)
	{}
	
}
