# CSPB 2270 Data Structures - Final Project - Trie

## Description

For the final project, I implemented the trie data structure. A trie, or “prefix tree,” is a type of tree data structure that is useful for storing text data when you need autocomplete/predictive text or spell check functionality. The structure is a set of strings in which each string is composed of a node for each character. If two or more strings share the same prefix, these strings would share the same nodes for their common prefix characters. For example, the strings “cat,” “catacomb,” “catch,” and “caterpillar” would share nodes for the characters “c,” “a,” and “t.” This allows you to quickly search for words within the set and figure out which words share the same prefix.

In my implementation, the trie is made up of trie nodes. Each trie node stores information for the character it represents, its children (subsequent nodes for a sequence of characters), and whether the node represents the end of a word. A node's children are contained in a vector of size 26—one slot for each letter of the alphabet. Words are restricted to only lowercase alphabet characters. 

A trie tree has one root node, which represents the top of the tree but does not itself have a character. The root node's children contain the first letters for all of the words in the set. For an individual word, it starts at the root (the first letter being a child of the root) and each subsequent letter is a child of the current letter node in the sequence. A word's end is marked by the `is_end_of_word` flag on the node representing the last letter.

![Trie data structure](/images/trie.png)

The `Trie` class has a public interface that supports inserting and removing words, and searching for words within the tree. The tree also has funtionality for providing word "suggestions" for a given prefix. Below is a list of each public method with brief description:

- `void Insert(const string& word)`: Inserts a word into the Trie. It will not insert invalid words or duplicates.
- `void Remove(const string& word)`: Removes the given word from the Trie if it exists.
- `bool Search(const string& word)`: Returns true if the given word is in the Trie and false if not.
- `vector<string> GetAllWords()`: Gets a list of all the words (in alphabetical order) in the Trie, returned as a vector of strings.
- `void Print()`: Prints a list of all the words in the trie in alphabetical order.
- `int Size()`: Returns the number of individual words in the Trie.
- `vector<string> SuggestionsForPrefix(string prefix)`: Returns a list of possible words for a given prefix. An empty list is returned if the prefix is not contained in the Trie.

## Setup, Compiling, and Running the Code

After cloning the repository, run `cmake` and `make` from the `build/` directory to set up and compile the code:

```
cd build/
cmake ..
make
```

You can now run the sample app or the tests from within the `build/` directory. Note that if you make any changes to the code, make sure to complile again with `make` before running the app or tests.

To run the app:
```
# Move to the build/ directory if not there already
cd build/
./run_app
```

To run the test suite:
```
./run_tests
```

