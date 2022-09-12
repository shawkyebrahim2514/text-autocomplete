#ifndef TRIE_H
#define TRIE_H

#include <bits/stdc++.h>
using namespace std;
const int ALPHABET_SIZE = 26;
class Trie
{
public:
    bool isEndOfWord;
    Trie* child[ALPHABET_SIZE];
    Trie();
};

void insert(Trie* root, string& str);

bool isLastNode(Trie* node);

void completeRec(Trie* node, string text, vector<string>& container);

int printAutoComplete(Trie* node, string query, vector<string>& container);
#endif // TRIE_H
