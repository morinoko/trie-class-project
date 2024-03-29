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

TEST_F(test_Trie, TestInsertInvalidWord) {
	Trie trie;
	trie.Insert("UPPER");

	// Make sure all the children in root are still empty
	for (auto child : trie.GetRoot()->children) {
		ASSERT_FALSE(child);
	}
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

	// Test search of invalid word
	ASSERT_FALSE(trie.Search("CAT"));
}

TEST_F(test_Trie, TestBasicRemove) {
	Trie trie;
	trie.Insert("cats");

	// Basic removal
	trie.Remove("cats");
	ASSERT_FALSE(trie.Search("cats"));

	// Removing word that isn't in trie
	trie.Insert("cats");
	trie.Remove("cat");
	ASSERT_FALSE(trie.Search("cat"));
	ASSERT_TRUE(trie.Search("cats")); // make sure other word isn't affected
}

TEST_F(test_Trie, TestRemoveWithBranches) {
	Trie trie;

	// Removal of word when there are two separate branchs in trie
	trie.Insert("geckos");
	trie.Insert("lions");

	trie.Remove("geckos");
	ASSERT_FALSE(trie.Search("geckos"));
	trie.Remove("lions");
	ASSERT_FALSE(trie.Search("lions"));

	// Remove shorter word that is a sub-word of a longer word
	trie.Insert("cats");
	trie.Insert("cat");

	trie.Remove("cat");
	ASSERT_TRUE(trie.Search("cats"));
	ASSERT_FALSE(trie.Search("cat"));

	// Remove longer word when there are also sub-words
	trie.Insert("cats");
	trie.Insert("cat");

	trie.Remove("cats");
	ASSERT_FALSE(trie.Search("cats"));
	ASSERT_TRUE(trie.Search("cat"));
}

TEST_F(test_Trie, TestSuggestionsForPrefixNoResults) {
	vector<string> suggestions;
	Trie trie;
	trie.Insert("cat");
	
	// When prefix is an empty string
	suggestions = trie.SuggestionsForPrefix("");
	ASSERT_EQ(suggestions.size(), 0);

	// When prefix doesn't exist in the trie
	suggestions = trie.SuggestionsForPrefix("ch");
	ASSERT_EQ(suggestions.size(), 0);

	// When prefix is an invalid word
	suggestions = trie.SuggestionsForPrefix("--");
	ASSERT_EQ(suggestions.size(), 0);
}

TEST_F(test_Trie, TestSuggestionsForPrefix) {
	vector<string> suggestions;
	vector<string> expected;
	Trie trie;
	trie.Insert("cat");
	trie.Insert("cats");
	trie.Insert("catsup");
	trie.Insert("catch");
	trie.Insert("catacomb");
	trie.Insert("dogs");
	
	suggestions = trie.SuggestionsForPrefix("ca");
	expected = vector<string> { "cat", "catacomb", "catch", "cats", "catsup", };
	ASSERT_EQ(suggestions.size(), 5);
	EXPECT_EQ(suggestions, expected);


	suggestions = trie.SuggestionsForPrefix("cats");
	expected = vector<string> { "cats", "catsup", };
	ASSERT_EQ(suggestions.size(), 2);
	EXPECT_EQ(suggestions, expected);

	suggestions = trie.SuggestionsForPrefix("catacombs");
	ASSERT_EQ(suggestions.size(), 0);
}

TEST_F(test_Trie, TestGetAllWords) {
	vector<string> expected;
	Trie trie;
	trie.Insert("apple");
	trie.Insert("cat");
	trie.Insert("bark");
	trie.Insert("applesauce");
	trie.Insert("catepillar");
	trie.Insert("zebra");

	vector<string> words = trie.GetAllWords();
	expected = vector<string> { "apple", "applesauce", "bark", "cat", "catepillar", "zebra", };
	ASSERT_EQ(words, expected);
}

TEST_F(test_Trie, TestSize) {
	Trie trie;

	// Should be 0 when empty
	ASSERT_EQ(trie.Size(), 0);

	trie.Insert("apple");
	trie.Insert("cat");
	trie.Insert("bark");
	trie.Insert("applesauce");
	trie.Insert("catepillar");
	trie.Insert("zebra");

	ASSERT_EQ(trie.Size(), 6);

	// After removal
	trie.Remove("bark");

	ASSERT_EQ(trie.Size(), 5);
}
