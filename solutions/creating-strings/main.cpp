#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> SolveBySTL(std::string s) {
  std::sort(s.begin(), s.end());

  std::vector<std::string> words;
  do {
    words.push_back(s);
  } while (std::next_permutation(s.begin(), s.end()));

  return words;
}

void SolveByRecursion(size_t n, std::vector<int> *freq, std::string *word,
                      std::vector<std::string> *words) {
  if (word->size() == n) {
    words->push_back(*word);
    return;
  }

  for (size_t i = 0; i < freq->size(); ++i) {
    if (freq->at(i)) {
      --freq->at(i);
      word->push_back(i + 'a');
      SolveByRecursion(n, freq, word, words);
      word->pop_back();
      ++freq->at(i);
    }
  }
}

std::vector<std::string> SolveByRecursion(std::string s) {
  std::vector<int> freq(26);
  for (auto c : s) {
    ++freq[c - 'a'];
  }

  std::string word;
  std::vector<std::string> words;
  SolveByRecursion(s.size(), &freq, &word, &words);

  return words;
}

int main() {
  std::string s;
  std::cin >> s;

  // const auto words = SolveBySTL(s);
  const auto words = SolveByRecursion(s);

  std::cout << words.size() << "\n";
  for (const auto &word : words) {
    std::cout << word << "\n";
  }

  return 0;
}
