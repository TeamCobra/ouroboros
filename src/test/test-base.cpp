#include <data/base.hpp>

#include <data/base_string.h>
#include <gtest/gtest.h>


using namespace ouroboros;

namespace {

// The fixture for testing class Foo.
class BaseTest : public ::testing::Test {
 protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	BaseTest() {
		// You can do set-up work for each test here.
	}

	virtual ~BaseTest() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Foo.
};


TEST_F(BaseTest, Test_BaseString) {
	base_string str("title", "desc", "value", "pattern", 0, std::pair<std::size_t, std::size_t>{0,10});
	ASSERT_EQ("title", str.getTitle());
	str.setTitle("title2");
	ASSERT_EQ("title2", str.getTitle());
	ASSERT_NE("title", str.getTitle());
	
	ASSERT_EQ("desc", str.getDescription());
	str.setDescription("desc2");
	ASSERT_EQ("desc2", str.getDescription());
	
	ASSERT_EQ(0, str.getMinLength());
	ASSERT_EQ(10, str.getMaxLength());
	ASSERT_TRUE(str.setMinLength(4));
	ASSERT_TRUE(str.setMaxLength(6));
	
	ASSERT_EQ(4, str.getMinLength());
	ASSERT_EQ(6, str.getMaxLength());
	
	ASSERT_FALSE(str.setMaxLength(1));
	ASSERT_FALSE(str.setMinLength(10));
	
	ASSERT_TRUE(str.setMinLength(1, "1"));
	ASSERT_TRUE(str.setMaxLength(1));
	
}

TEST_F(BaseTest, Test_BaseInteger) {
	
}

}	// namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
