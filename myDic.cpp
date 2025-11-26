#include<bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool wordEnd;
    char data;
    TrieNode(char ch) {
        data=ch;
        wordEnd = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
public: 
  TrieNode* root;

  Trie() {
      root = new TrieNode('\0');
  }

  void insertHandler(TrieNode* node, string word, int i) {      
    if (i == word.size()) {
      node->wordEnd = true;
      return;
    }       
    int index = word[i] - 'a';
    TrieNode* child;
    if (node->children[index] != NULL) {
      child = node->children[index];
    }
    else {
      child = new TrieNode(word[i]);
      node->children[index] = child;
    }
    insertHandler(child, word, i + 1);
  }

  void insert(string word) {
    insertHandler(root, word, 0);
  }

  bool searchUtil(TrieNode* node, string word, int i) {
    if (i == word.size()) {
        return node->wordEnd;
    }
    int index = word[i] - 'a';
    TrieNode* child;
    if (node->children[index] != NULL) {
        child = node->children[index];
    }
    else {
        return false;
    }
    return searchUtil(child, word, i + 1);
  }

  bool search(string word) {
    return searchUtil(root, word,0);
  }

  bool isEmpty(TrieNode* node) {
    for (int i = 0; i < 26; i++)
        if (node->children[i] != nullptr)
            return false;
    return true;
  }

  bool deleteUtil(TrieNode* node, string &word, int i) {
    if (i == word.size()) {
        if (!node->wordEnd) return false;
        node->wordEnd = false;           
        return true;
    }
    int index = word[i] - 'a';
    TrieNode* child = node->children[index];
    if (!child) return false; 
    bool deleted = deleteUtil(child, word, i + 1);
    if (deleted && !child->wordEnd && isEmpty(child)) {
        delete child;
        node->children[index] = nullptr;
    }
    return deleted;
  }

  void deleteWord(string word) {
    if (deleteUtil(root, word, 0))
        cout << "Deleted the entire word!" << endl;
    else
        cout << "Word not found!" << endl;
  }

};

int main(){
  Trie* t = new Trie();
  int running = 1;
  int choice;
  while (running){
    cout <<"Enter your choice"<<endl;
    cout <<"1. Add a word"<<endl;
    cout <<"2. Search a word"<<endl;
    cout <<"3. delete a word"<<endl;
    cout <<"4. Show words starting from a letter"<<endl;
    cout <<"5. Show all words"<<endl;
    cout <<"6. Exit"<<endl;
    cin>> choice;
    switch(choice){
      case 1:
        t->insert("hello");
        break;
      case 2:
        if(t->search("hello")){
          cout <<"Word found"<<endl;
        } else {
          cout <<"Word not found"<<endl;
        }
        break;
      case 3:
        t->deleteWord("hello");
        break;
      case 4:
        cout <<"Showing words starting from a letter";
        break;
      case 5:
        cout <<"Showing all words";
        break;
      case 6:
        running = 0;
        cout <<"Exited"<<endl;
        break;
      default:
        cout <<"Invalid choice"<<endl;
    }
  }
}
