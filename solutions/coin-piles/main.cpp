#include <algorithm>
#include <iostream>

int main() {
  int x;
  std::cin >> x;

  while (x--) {
    int a, b;
    std::cin >> a >> b;

    if ((a + b) % 3 == 0 && std::max(a, b) <= 2 * std::min(a, b)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }

  return 0;
}
