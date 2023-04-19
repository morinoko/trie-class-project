#ifndef TRIE_H__
#define TRIE_H__

#include <vector>
#include <memory>

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
        shared_ptr<trie_node> GetRoot();
        
    private:
        shared_ptr<trie_node> root;
        shared_ptr<trie_node> InitTrieNode(char letter);
        void SetRoot(shared_ptr<trie_node> new_root);
};

#endif  // TRIE_H__