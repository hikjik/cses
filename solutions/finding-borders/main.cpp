#include <iostream>
#include <string>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
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

  const int n = s.size();
  const auto z = zFunction(s);

  for (int j = n - 1; j > 0; --j) {
    if (j + z[j] == n) {
      std::cout << n - j << " ";
    }
  }
  std::cout << "\n";

  return 0;
}
