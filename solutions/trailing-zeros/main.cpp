#include <iostream>

int main() {
  int n;
  std::cin >> n;

  int cnt = 0;
  while (n >= 5) {
    cnt += n / 5;
    n /= 5;
  }

  std::cout << cnt << "\n";

  return 0;
}
