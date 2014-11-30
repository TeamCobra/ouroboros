#include <gtest/gtest.h>
#include <rest.hpp>

using namespace ouroboros;

namespace {

// The fixture for testing class Foo.
class RestTest : public ::testing::Test {
 protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	RestTest() {
		// You can do set-up work for each test here.
	}

	virtual ~RestTest() {
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

// Tests that Foo does Xyz.
TEST_F(RestTest, Test_is_Rest_URI) {
	// Exercises the Xyz feature of Foo.
	ASSERT_FALSE(is_REST_URI(""));
	ASSERT_TRUE(is_REST_URI("/group/1/name/2"));
}

}	// namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
