#include <iostream>
#include <vector>

int main() {
  int n, a;
  std::cin >> n;

  int prev = 0;
  long long ops = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> a;

    if (a < prev) {
      ops += prev - a;
    } else {
      prev = a;
    }
  }

  std::cout << ops << "\n";

  return 0;
}
