#include "Trie.h"

Trie::Trie() {
    // TODO 
}

Trie::~Trie() {}

shared_ptr<trie_node> Trie::InitTrieNode(char letter) {
    shared_ptr<trie_node> new_node (new trie_node);

    new_node->is_end_of_word = false;
    new_node->letter = letter;
    new_node->children = vector<shared_ptr<trie_node>>(ALPHABET_SIZE);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        new_node->children.at(i) = shared_ptr<trie_node>(NULL);
    }

    return new_node;
}