#include <iostream>

int main() {
  int n;
  std::cin >> n;

  const int kMod = 1e9 + 7;

  long long res = 1;
  long long x = 2;
  while (n) {
    if (n & 1) {
      res = (res * x) % kMod;
    }
    n >>= 1;
    x = (x * x) % kMod;
  }

  std::cout << res << "\n";

  return 0;
}
