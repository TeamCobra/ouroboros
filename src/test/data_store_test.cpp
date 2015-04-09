#include <gtest/gtest.h>
#include <data/data_store.hpp>
#include <data/base_string.h>

using namespace ouroboros;

namespace {

// The fixture for testing class Foo.
class data_store_test : public ::testing::Test {
 protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	data_store_test() {
		// You can do set-up work for each test here.
	}

	virtual ~data_store_test() {
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

TEST_F(data_store_test, test_constructor) {
	// Exercises the Xyz feature of Foo.
	
	group<var_field> root("g1", "");
	base_string str("number", "decs", "1", "1", 0, std::pair<size_t, size_t>(0,10));
	root.add(&str);
	root.add(&root);
	data_store<var_field> store(root);
	
	ASSERT_TRUE(NULL != store.get("g1", "number"));
	ASSERT_TRUE(NULL != store.get("g1"));
	ASSERT_FALSE(NULL != store.get("g1-g1"));
}

}	// namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
