# CSPB 2270 Data Structures - Final Project - Trie

## Description

For the final project, I implemented the trie data structure. A trie, or “prefix tree,” is a type of tree data structure that is useful for storing text data when you need autocomplete/predictive text or spell check functionality. The structure is a set of strings in which each string is composed of a node for each character. If two or more strings share the same prefix, these strings would share the same nodes for their common prefix characters. For example, the strings “cat,” “catacomb,” “catch,” and “caterpillar” would share nodes for the characters “c,” “a,” and “t.” This allows you to quickly search for words within the set and figure out which words share the same prefix.

![Trie data structure](/images/trie.png)

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

