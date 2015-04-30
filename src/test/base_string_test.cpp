#include <data/base.hpp>

#include <data/base_string.h>
#include <gtest/gtest.h>


using namespace ouroboros;

namespace {

// The fixture for testing class Foo.
class base_string_test : public ::testing::Test {
 protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	base_string_test()
	:str("title", "desc", "value", ".*", std::pair<std::size_t, std::size_t>(0,10))
	{
		// You can do set-up work for each test here.
	}

	virtual ~base_string_test() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		str = base_string("title", "desc", "value", ".*", std::pair<std::size_t, std::size_t>(0,10));
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Foo.

	base_string str;
};


TEST_F(base_string_test, test_constructor) {
	ASSERT_EQ("title", str.getTitle());
	ASSERT_NE("title2", str.getTitle());
	
	ASSERT_EQ("desc", str.getDescription());
	ASSERT_NE("desc2", str.getDescription());
	
	ASSERT_EQ(0, str.getMinLength());
	ASSERT_EQ(10, str.getMaxLength());
	ASSERT_NE(4, str.getMinLength());
	ASSERT_NE(6, str.getMaxLength());

	ASSERT_EQ("value", str.getString());
}

TEST_F(base_string_test, test_set_pattern)
{
	ASSERT_TRUE(str.setPattern("value"));
	ASSERT_TRUE(str.setPattern("valu."));
	ASSERT_FALSE(str.setPattern("1"));
}

TEST_F(base_string_test, test_set_min_length)
{
	ASSERT_TRUE(str.setMinLength(0));
	ASSERT_FALSE(str.setMinLength(100));
	ASSERT_EQ(0, str.getMinLength());
	
	ASSERT_TRUE(str.setMaxLength(100));
	ASSERT_TRUE(str.setMinLength(9, "12345678901"));

	ASSERT_TRUE(str.setMaxLength(15));
	ASSERT_FALSE(str.setMinLength(14, "12345678901"));
}

TEST_F(base_string_test, test_set_max_length)
{
	ASSERT_TRUE(str.setMaxLength(100));
	ASSERT_FALSE(str.setMaxLength(0));
	ASSERT_EQ(100, str.getMaxLength());
	
	ASSERT_TRUE(str.setMinLength(0));
	ASSERT_TRUE(str.setMaxLength(9, "123456789"));
	ASSERT_FALSE(str.setMaxLength(9, "12345678910"));

}

TEST_F(base_string_test, test_get_JSON)
{
	std::string response = "{ \"type\" : \"base_string\",  \"title\" : \"title\", \"description\" : \"desc\" , \"value\" : \"value\" ,\"pattern\" : \".*\" ,\"length\" : 0 ,\"range\" : [0, 10] }";
	ASSERT_EQ(response, str.getJSON());
}

TEST_F(base_string_test, test_set_JSON)
{
	ASSERT_TRUE(str.setJSON(JSON("{\"value\" : \"value2\"}")));
	ASSERT_FALSE(str.setJSON(JSON("{\"value\" : \"123456789012345\" }")));
	ASSERT_TRUE(str.setJSON(JSON("{\"description\" : \"value2\"}")));
	ASSERT_TRUE(str.setJSON(JSON("{\"title\" : \"value2\"}")));
}

}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

