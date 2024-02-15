#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

std::vector<int> manacher(const std::string &s) {
  std::string t = "^";
  for (auto c : s) {
    t += '#', t += c;
  }
  t += '#', t += '$';

  std::vector<int> p(t.size());
  for (int i = 1, l = 1, r = 1; i < std::ssize(t) - 1; ++i) {
    const int j = l + r - i;
    p[i] = std::max(0, std::min(r - i, p[j]));

    while (t[i - p[i]] == t[i + p[i]]) {
      ++p[i];
    }

    if (i + p[i] > r) {
      l = i - p[i], r = i + p[i];
    }
  }
  return p;
}

int main() {
  FastIO();

  std::string s;
  std::cin >> s;

  const auto p = manacher(s);

  const auto c = std::max_element(p.begin(), p.end()) - p.begin();
  const auto l = (c - p[c]) / 2, r = (c + p[c]) / 2;
  std::cout << s.substr(l, r - l - 1) << "\n";

  return 0;
}
