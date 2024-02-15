#include <iostream>
#include <string>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

std::vector<int> LPS(const std::string &s) {
  std::vector<int> lps(s.size());
  for (int i = 1, j = 0; i < std::ssize(s);) {
    if (s[i] == s[j]) {
      lps[i++] = ++j;
    } else {
      if (j) {
        j = lps[j - 1];
      } else {
        ++i;
      }
    }
  }
  return lps;
}

std::vector<int> zFunction(const std::string &s) {
  const int n = s.size();
  std::vector<int> z(n);
  int l = 0, r = 0;
  for (int i = 1; i < n; ++i) {
    if (i < r) {
      z[i] = std::min(r - i, z[i - l]);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}

int main() {
  FastIO();

  std::string s;
  std::cin >> s;

  for (auto a : zFunction(s)) {
    std::cout << a << " ";
  }
  std::cout << "\n";

  for (auto a : LPS(s)) {
    std::cout << a << " ";
  }
  std::cout << "\n";

  return 0;
}
