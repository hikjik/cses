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

int main() {
  FastIO();

  std::string s, p;
  std::cin >> s >> p;

  const int n = s.size();
  const int m = p.size();
  const auto lps = LPS(p);

  int ans = 0;
  for (int i = 0, j = 0; i < n;) {
    if (s[i] == p[j]) {
      i++, j++;
      if (j == m) {
        ++ans;
        j = lps[j - 1];
      }
    } else {
      if (j) {
        j = lps[j - 1];
      } else {
        ++i;
      }
    }
  }
  std::cout << ans << "\n";

  return 0;
}
