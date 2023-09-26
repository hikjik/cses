#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;

  int repetitions = 1, cnt = 1;
  for (size_t i = 1; i < s.size(); ++i) {
    cnt = s[i] == s[i - 1] ? cnt + 1 : 1;
    repetitions = std::max(repetitions, cnt);
  }
  std::cout << repetitions << "\n";

  return 0;
}
