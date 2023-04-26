#include <iostream>
#include <fstream>
#include "../code/Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
    Trie trie;

    trie.Insert("apple");
    trie.Insert("cat");
    trie.Insert("bark");
    trie.Insert("applesauce");
    trie.Insert("catepillar");
    trie.Insert("catacomb");
    trie.Insert("catch");
    trie.Insert("zebra");

    cout << "All words in Trie:" << endl;
    trie.Print();

    cout << endl;
    cout << "Suggestions for prefix 'cat':" << endl;

    vector<string> suggestions = trie.SuggestionsForPrefix("cat");

    for (auto suggestion : suggestions) {
        cout << suggestion << endl;
    }
    
    return 0;
}