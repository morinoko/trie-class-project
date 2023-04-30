#include <iostream>
#include <fstream>
#include "../code/Trie.h"

using namespace std;

int main(int argc, char* argv[])
{   
    cout << endl;
    cout << "@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@" << endl;
    cout << endl;
    cout << "Hello! Welcome to the Trie Class demo!" << endl;
    cout << "This mini program will demonstrate some of the things that Trie can do." << endl;
    cout << endl;
    cout << "@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@" << endl;

    Trie trie;

    cout << endl;
    cout << "Inserting apple, cat, bark, applesauce, catepillar, catacomb, catch, and zebra..." << endl;
    cout << endl;

    trie.Insert("apple");
    trie.Insert("cat");
    trie.Insert("bark");
    trie.Insert("applesauce");
    trie.Insert("catepillar");
    trie.Insert("catacomb");
    trie.Insert("catch");
    trie.Insert("zebra");

    cout << "Total words in trie: " << trie.Size() << endl;
    cout << endl;
    cout << "List of all words in Trie:" << endl;
    trie.Print();

    cout << endl;
    cout << "-----------------------------" << endl;
    cout << "Suggestions for prefix 'cat':" << endl;

    vector<string> suggestions;
    suggestions = trie.SuggestionsForPrefix("cat");

    for (auto suggestion : suggestions) {
        cout << "- " << suggestion << endl;
    }

    cout << endl;
    cout << "----------------------" << endl;
    cout << "Removing 'catacomb'..." << endl;
    cout << endl;

    trie.Remove("catacomb");

    cout << "Total words in trie is now: " << trie.Size() << endl;
    cout << endl;
    cout << "List of all words in Trie:" << endl;
    trie.Print();


    cout << endl;
    cout << "--------------------------" << endl;
    cout << "Loading dictionary file with 9000+ words..." << endl;
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
    cout << "Total words in trie: " << trie.Size() << endl;
    cout << endl;

    suggestions = trie.SuggestionsForPrefix("commi");

    cout << "------------------------------" << endl;
    cout << "Suggestions for prefix 'comm':" << endl;

    for (auto suggestion : suggestions) {
        cout << "- " << suggestion << endl;
    }

    cout << endl;

    suggestions = trie.SuggestionsForPrefix("ze");

    cout << "------------------------------" << endl;
    cout << "Suggestions for prefix 'ze':" << endl;

    for (auto suggestion : suggestions) {
        cout << "- " << suggestion << endl;
    }

    cout << endl;

    suggestions = trie.SuggestionsForPrefix("prog");

    cout << "------------------------------" << endl;
    cout << "Suggestions for prefix 'prog':" << endl;

    for (auto suggestion : suggestions) {
        cout << "- " << suggestion << endl;
    }

    cout << endl;
    cout << "@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@" << endl;
    cout << endl;
    
    return 0;
}