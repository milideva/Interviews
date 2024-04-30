#include <vector>
#include <cassert>
#include <iostream>
#include <memory>

using namespace std;

struct TrieNode {
  vector <shared_ptr<TrieNode>> children;
  bool isWord = false;
  TrieNode() : children(26) {}
};

class Trie {
 public:
  void insert(const string& word) {
    shared_ptr <TrieNode> node = root;
    for (const char c : word) {
      const int i = c - 'a';
      if (node->children[i] == nullptr)
        node->children[i] = make_shared<TrieNode>();
      node = node->children[i];
    }
    node->isWord = true;
  }

  bool search(const string& word) {
    shared_ptr<TrieNode> node = find(word);
    return node && node->isWord;
  }

  bool startsWith(const string& prefix) {
    return find(prefix) != nullptr;
  }

 private:
  shared_ptr<TrieNode> root = make_shared<TrieNode>();

  shared_ptr<TrieNode> find(const string& prefix) {
    shared_ptr<TrieNode> node = root;
    for (const char c : prefix) {
      const int i = c - 'a';
      if (node->children[i] == nullptr)
        return nullptr;
      node = node->children[i];
    }
    return node;
  }
};

void testTrie() {
    Trie trie;

    // Test insert and search
    trie.insert("apple");
    assert(trie.search("apple") == true); // Expected: Found
    assert(trie.search("app") == false); // Expected: Not Found

    // Test startsWith
    assert(trie.startsWith("app") == true); // Expected: True
    assert(trie.startsWith("bat") == false); // Expected: False

    // Test insert and search again
    trie.insert("app");
    assert(trie.search("app") == true); // Expected: Found

    // Test startsWith again
    assert(trie.startsWith("app") == true); // Expected: True

    // Additional test cases
    trie.insert("dog");
    assert(trie.search("dog") == true); // Expected: Found
    assert(trie.search("cat") == false); // Expected: Not Found
    assert(trie.startsWith("do") == true); // Expected: True
    assert(trie.startsWith("c") == false); // Expected: False

    trie.insert("doge");
    assert(trie.search("doge") == true); // Expected: Found
    assert(trie.search("dogf") == false); // Expected: Not Found
    assert(trie.startsWith("dog") == true); // Expected: True
    assert(trie.startsWith("dogg") == false); // Expected: False

    trie.insert("cat");
    assert(trie.search("cat") == true); // Expected: Found
    assert(trie.search("cath") == false); // Expected: Not Found
    assert(trie.startsWith("ca") == true); // Expected: True
    assert(trie.startsWith("b") == false); // Expected: False

    trie.insert("cathy");
    assert(trie.search("cathy") == true); // Expected: Found
    assert(trie.search("cathya") == false); // Expected: Not Found
    assert(trie.startsWith("cathy") == true); // Expected: True
    assert(trie.startsWith("cathz") == false); // Expected: False
}

int main() {
    testTrie();
    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}