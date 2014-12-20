#include <gtest/gtest.h>
#include <data/data_store.hpp>
#include <base.hpp>

using namespace ouroboros;

namespace {

// The fixture for testing class Foo.
class DataStoreTest : public ::testing::Test {
 protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	DataStoreTest() {
		// You can do set-up work for each test here.
	}

	virtual ~DataStoreTest() {
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
TEST_F(DataStoreTest, Test_Group) {
	// Exercises the Xyz feature of Foo.
	
	group<var_field> root("g1", "");
	//data_store<int> store;
	ASSERT_TRUE(root.findItem("") == nullptr);
	ASSERT_TRUE(root.findGroup("") == nullptr);
	ASSERT_TRUE(root.findGroup("g1") == nullptr);
	base_integer integer("number", "", 1, std::pair<int,int>(0,10));
	root.add(&integer);
	ASSERT_TRUE(root.findItem("number") == &integer);
	root.add(&root);
	ASSERT_EQ(&root, root.findGroup("g1"));
	ASSERT_FALSE(root.findGroup("g1-g1") == &root);
}

TEST_F(DataStoreTest, Test_DataStore) {
	// Exercises the Xyz feature of Foo.
	
	group<var_field> root("g1", "");
	base_integer integer("number", "", 1, std::pair<int,int>(0,10));
	root.add(&integer);
	root.add(&root);
	data_store<var_field> store(std::move(root));
	
	ASSERT_TRUE(nullptr != store.get("g1", "number"));
	ASSERT_TRUE(nullptr != store.get("g1"));
	ASSERT_TRUE(nullptr != store.get("g1-g1"));
}

}	// namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
