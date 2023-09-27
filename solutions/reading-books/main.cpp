#include <algorithm>
#include <iostream>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

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
