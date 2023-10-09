#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, q;
  std::cin >> n >> q;

  std::vector<long long> prefix_sums(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> prefix_sums[i];
    prefix_sums[i] ^= prefix_sums[i - 1];
  }

  while (q--) {
    int a, b;
    std::cin >> a >> b;

    std::cout << (prefix_sums[b] ^ prefix_sums[a - 1]) << "\n";
  }

  return 0;
}
