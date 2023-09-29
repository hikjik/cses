#include <algorithm>
#include <iostream>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  long long n;
  std::cin >> n;

  long long low = 1, high = n * n;
  while (low < high) {
    const auto middle = low + (high - low) / 2;

    long long cnt = 0;
    for (int i = 1; i <= n; ++i) {
      cnt += std::min(n, middle / i);
    }

    cnt >= (n * n + 1) / 2 ? high = middle : low = middle + 1;
  }

  std::cout << low << "\n";

  return 0;
}
