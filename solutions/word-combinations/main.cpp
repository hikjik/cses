#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

struct TrieNode {
  std::array<std::unique_ptr<TrieNode>, 26> children;
  bool terminal = false;
};

class Trie : private TrieNode {
public:
  void Insert(const std::string &word) {
    auto *node = Root();
    for (auto c : word) {
      const auto i = c - 'a';
      if (!node->children[i]) {
        node->children[i] = std::make_unique<TrieNode>();
      }
      node = node->children[i].get();
    }
    node->terminal = true;
  }

  const TrieNode *Next(const TrieNode *node, char c) {
    if (!node) {
      return nullptr;
    }
    return node->children[c - 'a'].get();
  }

  const TrieNode *Root() const { return this; }

  TrieNode *Root() { return this; }
};

int main() {
  FastIO();

  std::string s;
  std::cin >> s;

  Trie trie;
  int k;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    std::string word;
    std::cin >> word;

    trie.Insert(word);
  }

  const int mod = 1e9 + 7;

  std::vector<int> dp(s.size() + 1);
  dp.back() = 1;
  for (int i = s.size() - 1; i >= 0; --i) {
    const auto *node = trie.Root();
    for (int j = i; j < std::ssize(s); ++j) {
      node = trie.Next(node, s[j]);
      if (!node) {
        break;
      }
      if (node->terminal) {
        dp[i] = (dp[i] + dp[j + 1]) % mod;
      }
    }
  }

  std::cout << dp[0] << "\n";

  return 0;
}
