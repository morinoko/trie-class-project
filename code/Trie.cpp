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

void Trie::RecursiveInsert(shared_ptr<trie_node>& node, const string& word, int current_letter_index) {
    // Base case: The index of the letter has surpassed end of word
    if (current_letter_index >= word.length()) {
        return;
    }

    char letter = word.at(current_letter_index);

    // If letter is already in node, move to that node and check the next letter
    if (IsLetterInNode(letter, node)) {
        // Grab the next node
        int next_node_index = LetterIndex(letter);
        shared_ptr<trie_node> next_node = node->children.at(next_node_index);

        // If the new word is a subset of an existing word, and the next node is the end,
        // mark the node to an end of a word
        if (current_letter_index == word.length() - 1) {
            next_node->is_end_of_word = true;
        }

        RecursiveInsert(next_node, word, current_letter_index + 1);
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
    // Start at root
    shared_ptr<trie_node> cursor = GetRoot();
    bool found = false;

    // For each letter in the word, traverse the trie tree.
    for (int i = 0; i < word.length(); i++) {
        char letter = word.at(i);

        if (IsLetterInNode(letter, cursor)) {
            // If the letter is present in the cursor's children, check that letter's node
            int letter_index = LetterIndex(letter);
            cursor = cursor->children.at(letter_index);

            // If each letter has been found up until now, and the last letter is at a node that is the end of the word, 
            // the word was found.
            if (i == (word.length() - 1) && cursor->is_end_of_word) {
                found = true;
            }
        } 
        // If the next letter isn't present in the sequence at any point, break out of the loop
        else {
            break;
        }
    }

    return found;
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