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
int letter_index(char letter) {
	return letter - 'a';
}


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

TEST_F(test_Trie, TestInsert) {
	Trie trie;
	trie.Insert("dog");

	shared_ptr<trie_node> root = trie.GetRoot();

	int d_index = letter_index('d');
	int o_index = letter_index('o');
	int g_index = letter_index('g');

	shared_ptr<trie_node> d_node = root->children.at(d_index);
	ASSERT_TRUE(d_node);
	ASSERT_EQ(d_node->letter, 'd');
	ASSERT_FALSE(d_node->is_end_of_word);

	shared_ptr<trie_node> o_node = d_node->children.at(o_index);
	ASSERT_TRUE(o_node);
	ASSERT_EQ(o_node->letter, 'o');
	ASSERT_FALSE(o_node->is_end_of_word);

	shared_ptr<trie_node> g_node = o_node->children.at(g_index);
	ASSERT_TRUE(g_node);
	ASSERT_EQ(g_node->letter, 'g');
	ASSERT_TRUE(g_node->is_end_of_word);

	// Test overlapping words
	trie.Insert("dogs");
	int s_index = letter_index('s');

	// Make sure prior nodes are unaffected
	ASSERT_EQ(d_node->letter, 'd');
	ASSERT_FALSE(d_node->is_end_of_word);

	ASSERT_EQ(o_node->letter, 'o');
	ASSERT_FALSE(o_node->is_end_of_word);

	ASSERT_EQ(g_node->letter, 'g');
	ASSERT_TRUE(g_node->is_end_of_word);

	shared_ptr<trie_node> s_node = g_node->children.at(s_index);
	ASSERT_TRUE(s_node);
	ASSERT_EQ(s_node->letter, 's');
	ASSERT_TRUE(s_node->is_end_of_word);

	// Test insert shorter word that is a part of an existing word
	trie.Insert("do");

	ASSERT_TRUE(o_node->is_end_of_word);
}

TEST_F(test_Trie, TestSearch) {
	Trie trie;
	trie.Insert("catnip");
	trie.Insert("cats");

	// Make sure inserted words can be found
	ASSERT_TRUE(trie.Search("cats"));
	ASSERT_TRUE(trie.Search("catnip"));

	// Make sure words simply not present in the trie return false
	ASSERT_FALSE(trie.Search("dog"));

	// Even if a prefix is present, it's not in the trie unless it was inserted and the
	// last letter was marked as being the end of a word.
	ASSERT_FALSE(trie.Search("cat"));
}

