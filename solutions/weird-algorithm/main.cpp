#include <iostream>

int main() {
  long long n;
  std::cin >> n;

  std::cout << n;
  while (n > 1) {
    n = n & 1 ? 3 * n + 1 : n >> 1;
    std::cout << " " << n;
  }
  std::cout << "\n";

  return 0;
}
