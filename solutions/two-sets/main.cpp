#include <iostream>

int main() {
  int n;
  std::cin >> n;

  int r = n % 4;
  if (r == 1 || r == 2) {
    std::cout << "NO\n";
    return 0;
  }

  std::cout << "YES\n";
  if (r == 0) {
    std::cout << n / 2 << "\n";
    for (int i = 2; i <= n / 2; i += 2) {
      std::cout << i << " " << n - i + 1 << " ";
    }
    std::cout << "\n" << n / 2 << "\n";
    for (int i = 1; i <= n / 2; i += 2) {
      std::cout << i << " " << n - i + 1 << " ";
    }
  } else {
    std::cout << n / 2 << "\n";
    for (int i = 2; i <= n / 2; i += 2) {
      std::cout << i << " " << n - i << " ";
    }
    std::cout << n << "\n" << n / 2 + 1 << "\n";
    for (int i = 1; i <= n / 2; i += 2) {
      std::cout << i << " " << n - i << " ";
    }
  }
  std::cout << "\n";

  return 0;
}
