#ifndef TRIE_H__
#define TRIE_H__

#include <vector>
#include <memory>
#include <string>

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
        void Remove(string word);

        // Search for a word in the trie. Returns true if found, false if not
        bool Search(string word);

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

        // Recursive helper for insert
        void RecursiveInsert(shared_ptr<trie_node>& node, const string& word, int current_letter_index);

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