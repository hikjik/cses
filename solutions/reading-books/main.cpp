#include <algorithm>
#include <iostream>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n;
  std::cin >> n;

  long long sum = 0;
  int max = 0;
  while (n--) {
    int a;
    std::cin >> a;

    max = std::max(max, a);
    sum += a;
  }

  std::cout << std::max(2LL * max, sum) << "\n";

  return 0;
}
