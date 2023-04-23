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
    // If the work is not in the trie, don't do anything
    if (!Search(word)) { return; }

    // traverse tree and create map of letter nodes for each character in word.
    vector<shared_ptr<trie_node>> letter_node_list = BuildLetterNodeList(word);

    // Iterate the list starting at the last letter of the word
    for (int i = word.length() - 1; i >= 0; i--) {
        shared_ptr<trie_node> current_node = letter_node_list.at(i);

        // If there are branches off of that letter, then nothing can be deleted from this point
        vector<shared_ptr<trie_node>> child_letters = GetChildLetters(current_node);
        
        // If there are children, the current node can't be deleted, but we need to remove the is_end_of_word marker
        if (child_letters.size() > 0) {
            // If it's the node for the last letter, make sure that it is no longer considered 
            // the end of a word
            if (i == word.length() - 1) {
                current_node->is_end_of_word = false;
            }

            break;
        }
        // If no children, we can remove the node if its not part of another word
        else {
            // If it's not the end of the word itself, but we encounter a different word's end,
            // then there is a sub-word within the word we're removing, and it shouldn't be deleted
            if (i != word.length() - 1 && current_node->is_end_of_word) {
                break;
            }

            int letter_index = LetterIndex(current_node->letter);

            // If we're at the first letter in the world, the parent is the root
            if (i == 0) {
                shared_ptr<trie_node> parent_node = GetRoot();
                parent_node->children.at(letter_index) = shared_ptr<trie_node>(NULL);
            }
            else {
                shared_ptr<trie_node> parent_node = letter_node_list.at(i - 1);
                parent_node->children.at(letter_index) = shared_ptr<trie_node>(NULL);
            }
        }
    }
}

// Assumes the word is in the trie
vector<shared_ptr<trie_node>> Trie::BuildLetterNodeList(string word) {
    vector<shared_ptr<trie_node>> letter_node_list;
    shared_ptr<trie_node> cursor = GetRoot();
    
    // For each letter in the word, traverse the trie tree.
    for (int i = 0; i < word.length(); i++) {
        char letter = word.at(i);
        int letter_index = LetterIndex(letter);
        cursor = cursor->children.at(letter_index);

        // Insert the node corresponding to the character
        letter_node_list.push_back(cursor);
    }

    return letter_node_list;
}

vector<shared_ptr<trie_node>> Trie::GetChildLetters(shared_ptr<trie_node> node) {
    vector<shared_ptr<trie_node>> children;

    for (auto child : node->children) {
        if (child) {
            children.push_back(child);
        }
    }

    return children;
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