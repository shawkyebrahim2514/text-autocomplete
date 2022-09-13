#include "trie.h"

Trie::Trie()
{
    for (int i = 0; i < ALPHABET_SIZE; i++) child[i] = NULL;
    isEndOfWord = false;
}

void insert(Trie* root, string& str)
{
    Trie* node = root;
    for (int i = 0; i < str.size(); i++) {
        if(str[i] < 97 || str[i] > 122){
            node->isEndOfWord = true;
            string tmp = str.substr(i+1);
            insert(root, tmp);
            return;
        }
        char ind = str[i] - 'a';
        if (!node->child[ind]) node->child[ind] = new Trie();
        node = node->child[ind];
    }
    node->isEndOfWord = true;
}

bool isLastNode(Trie* node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->child[i]) return 0;
    return 1;
}

void completeRec(Trie* node, string text, vector<string>& container)
{
    if(node->isEndOfWord) container.push_back(text);
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->child[i]) completeRec(node->child[i], text + char('a' + i), container);
}

int printAutoComplete(Trie* node, string query, vector<string>& container)
{
    Trie* curNode = node;
    for (char c : query) {
        int ind = c-'a';
        if (!curNode->child[ind]) return 0;
        curNode = curNode->child[ind];
    }
    if (isLastNode(curNode)) {
        container.push_back(query);
        return -1;
    }
    completeRec(curNode, query, container);
    return 1;
}
