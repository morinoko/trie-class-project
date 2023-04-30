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

    vector<string> suggestions;
    suggestions = trie.SuggestionsForPrefix("cat");

    for (auto suggestion : suggestions) {
        cout << suggestion << endl;
    }

    cout << endl;
    cout << "Loading dictionary..." << endl;
    cout << endl;

    fstream dictfile;
    dictfile.open("../data/words.txt", ios::in);

    if (dictfile.is_open()) {
        string word;

        while(getline(dictfile, word)) {
            trie.Insert(word);
        }

        dictfile.close();
    }

    cout << "Finished loading dictionary!" << endl;
    cout << endl;

    suggestions = trie.SuggestionsForPrefix("comm");

    cout << "Suggestions for prefix 'comm':" << endl;

    for (auto suggestion : suggestions) {
        cout << suggestion << endl;
    }
    
    return 0;
}