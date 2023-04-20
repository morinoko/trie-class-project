#include "Trie.h"

Trie::Trie() {
    shared_ptr<trie_node> root = InitTrieNode('\0');
    SetRoot(root);
}

Trie::~Trie() {}

void Trie::Insert(const string& word) {
    // Starting at the root, traverse down the trie's nodes, one step for each character in the word
    shared_ptr<trie_node> root = GetRoot();
    
    RecursiveInsert(root, word, 0);
}

void Trie::RecursiveInsert(shared_ptr<trie_node> node, const string& word, int current_letter_index) {
    // Base case: The index of the letter has surpassed end of word
    if (current_letter_index >= word.length()) {
        return;
    }

    char letter = word.at(current_letter_index);

    // If letter is already in node, move to that node and check the next letter
    if (IsLetterInNode(letter, node)) {
        // move letter index to next letter
        current_letter_index++;
        RecursiveInsert(node->children.at(current_letter_index), word, current_letter_index);
    }
    // Letter is not in node, insert it 
    else {
        // Create a new node for the letter
        shared_ptr<trie_node> new_node = InitTrieNode(letter);

        // If its the last letter in the word, mark the node as being end of the word
        if (current_letter_index == word.length() - 1) {
            new_node->is_end_of_word = true;
        }
        
        // Insert it at the correct position in the current node's children
        node->children.at(LetterIndex(letter)) = new_node;

        // Recursively insert any remaining letters
        current_letter_index++;
        RecursiveInsert(new_node, word, current_letter_index);
    }

    
}

void Trie::Remove(string word) {

}

bool Trie::Search(string word) {
    return false;
}

vector<string> Trie::SuggestionsForPrefix(string prefix) {
    return vector<string>(0);
}

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

shared_ptr<trie_node> Trie::GetRoot() {
    return root;
}

void Trie::SetRoot(shared_ptr<trie_node> new_root) {
    root = new_root;
}

bool Trie::IsLetterInNode(char letter, shared_ptr<trie_node> node) {
    int letter_index = LetterIndex(letter);
    
    if (node->children.at(letter_index)) {
        return true;
    } else {
        return false;
    }
}

int Trie::LetterIndex(char letter) {
    // Characters are represented as integers in the background.
    // The character 'a' is represented by 97 and 'z' by 122.
    // Subtract 'a' from the letter to get its index in a node's children vector,
    // so 'a' will be at 0 and z will be at 25
    return letter - 'a';
}