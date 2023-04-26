#ifndef TRIE_H__
#define TRIE_H__

#include <vector>
#include <memory>
#include <string>
#include <iostream>

using namespace std;

const int ALPHABET_SIZE = 26;

struct trie_node {
    bool is_end_of_word;
    vector<shared_ptr<trie_node>> children;
    char letter;
};

class Trie {
    public:
        Trie(); // Constructor
        ~Trie(); // Destructor

        // Returns the root node
        shared_ptr<trie_node> GetRoot();

        // Insert a word into the trie
        void Insert(const string& word);

        // Remove a word from the trie
        void Remove(const string& word);

        // Search for a word in the trie. Returns true if found, false if not
        bool Search(const string& word);

        // Retuns a list of all words in the trie in alphabetical order
        vector<string> GetAllWords();

        // Prints all words in the trie in alphabetical order
        void Print();

        // Returns a list of possible words for a given prefix.
        // If there are no possible words, an empty vector is returned.
        vector<string> SuggestionsForPrefix(string prefix);
        
    private:
        shared_ptr<trie_node> root;
        shared_ptr<trie_node> InitTrieNode(char letter);

        // Sets the root of the trie
        void SetRoot(shared_ptr<trie_node> new_root);

        // Checks if a character is in the given trie_node
        bool IsLetterInNode(char letter, shared_ptr<trie_node> node);

        // Returns the index of the given character
        int LetterIndex(char letter);

        // Validates the word only contains lowercase letters and no special characters
        bool ValidateWord(const string& word);

        // Recursive helper for insert
        void RecursiveInsert(shared_ptr<trie_node>& node, const string& word, int current_letter_index);
        
        // Recursive helper for getting all words in trie
        void RecursiveGetAllWords(vector<string>& words, shared_ptr<trie_node> cursor, string word);

        // Builds a vector of trie nodes corresponding to each character in a word in order
        vector<shared_ptr<trie_node>> BuildLetterNodeList(string word);
        
        // Get all the direct child letters of a node
        vector<shared_ptr<trie_node>> GetChildLetters(shared_ptr<trie_node> node);

        // Returns a pointer to the last letter node of a prefix
        shared_ptr<trie_node> FindEndOfPrefix(string prefix);

        // Recursive helper for finding suggestions
        void RecursiveSuggestionsForPrefix(vector<string>& suggestions, shared_ptr<trie_node> prefix_last_letter, string prefix);
};

#endif  // TRIE_H__