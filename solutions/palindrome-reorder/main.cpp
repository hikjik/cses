#include <array>
#include <iostream>

int main() {
  static const int kSize = 26;

  std::array<int, kSize> freq{};

  char c;
  while (std::cin.get(c)) {
    ++freq[c - 'A'];
  }

  int odd = -1;
  for (int i = 0; i < kSize; ++i) {
    if (freq[i] & 1) {
      if (odd != -1) {
        std::cout << "NO SOLUTION\n";
        return 0;
      }
      odd = i;
    }
  }

  for (int i = 0; i < kSize; ++i) {
    for (int r = 0; r < freq[i] / 2; ++r) {
      std::cout << char(i + 'A');
    }
  }
  if (odd != -1) {
    std::cout << char(odd + 'A');
  }
  for (int i = kSize - 1; i >= 0; --i) {
    for (int r = 0; r < freq[i] / 2; ++r) {
      std::cout << char(i + 'A');
    }
  }
  std::cout << "\n";

  return 0;
}
