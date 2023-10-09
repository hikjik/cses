#include <algorithm>
#include <bit>
#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  unsigned n, q;
  std::cin >> n >> q;

  std::vector sparse_table(std::bit_width(n), std::vector<int>(n));
  for (auto &a : sparse_table[0]) {
    std::cin >> a;
  }

  for (auto i = 1u; i < sparse_table.size(); ++i) {
    for (auto j = 0u; j + std::rotl(1u, i) <= n; ++j) {
      sparse_table[i][j] =
          std::min(sparse_table[i - 1][j],
                   sparse_table[i - 1][j + std::rotl(1u, i - 1)]);
    }
  }

  while (q--) {
    unsigned a, b;
    std::cin >> a >> b;
    --a, --b;

    const auto length = b - a + 1;
    const auto i = std::bit_width(length) - 1;
    const auto k = std::bit_floor(length);
    std::cout << std::min(sparse_table[i][a], sparse_table[i][b - k + 1])
              << "\n";
  }

  return 0;
}
