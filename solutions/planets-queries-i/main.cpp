#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  int n, q;
  std::cin >> n >> q;

  const int kLogMaxK = 30;

  std::vector successors(kLogMaxK, std::vector<int>(n + 1));
  for (int u = 1; u <= n; ++u) {
    std::cin >> successors[0][u];
  }

  for (int i = 1; i < kLogMaxK; ++i) {
    for (int u = 1; u <= n; ++u) {
      successors[i][u] = successors[i - 1][successors[i - 1][u]];
    }
  }

  while (q--) {
    int x, k;
    std::cin >> x >> k;

    for (int i = 0; i < kLogMaxK; ++i) {
      if ((k >> i) & 1) {
        x = successors[i][x];
      }
    }

    std::cout << x << "\n";
  }

  return 0;
}
