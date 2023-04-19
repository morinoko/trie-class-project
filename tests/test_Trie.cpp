// Checkout TEST_F functions below to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/Trie.h"

#include <fstream>
#include <iostream>

using namespace std;

class test_Trie : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
	}
};

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////


/////////////////////////////////////////
// Tests start here

TEST_F(test_Trie, TestInitialization){
	Trie trie;
	shared_ptr<trie_node> root = trie.GetRoot();

	// Test that the root is properly created
	ASSERT_TRUE(root);
	ASSERT_FALSE(root->is_end_of_word);
	ASSERT_FALSE(root->letter);
	ASSERT_EQ(root->children.size(), 26);

	// All children should be null at first
	for (auto child : root->children) {
		ASSERT_FALSE(child);
	}
}

