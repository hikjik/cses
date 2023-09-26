#include <algorithm>
#include <iostream>

int main() {
  int n;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    long long x, y;
    std::cin >> y >> x;

    const auto m = std::max(x, y);
    std::cout << (m - 1) * (m - 1) + m + (x - y) * (m % 2 * 2 - 1) << "\n";
  }

  return 0;
}
