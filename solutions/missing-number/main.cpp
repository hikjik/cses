#include <iostream>

int main() {
  int n;
  std::cin >> n;

  auto sum = n * (n + 1LL) / 2;
  for (int i = 1; i < n; ++i) {
    int b;
    std::cin >> b;

    sum -= b;
  }

  std::cout << sum << "\n";

  return 0;
}
