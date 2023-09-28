#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

void CountingTilings(int i, int j, int k, int l, int n,
                     std::vector<std::vector<int>> &dp) {
  static const int kMod = 1e9 + 7;

  if (j == n) {
    dp[i][k] += dp[i - 1][l];
    dp[i][k] %= kMod;
    return;
  }

  if (k >> j & 1) {
    CountingTilings(i, j + 1, k, l, n, dp);
    return;
  }

  if (j + 1 < n && !(k >> (j + 1) & 1)) {
    CountingTilings(i, j + 2, k, l, n, dp);
  }

  CountingTilings(i, j + 1, k, l ^ (1 << j), n, dp);
}

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;

  // dp[i][k] - number of ways to fully cover first i−1 columns and have a
  // mask k on the ith column where every set bit in k corresponds to an already
  // occupied cell and unset bit to unoccupied cells.
  std::vector dp(m + 1, std::vector<int>(1 << n));
  dp[0][0] = 1;

  for (int i = 1; i <= m; ++i) {
    for (int k = 0; k < 1 << n; ++k) {
      CountingTilings(i, 0, k, 0, n, dp);
    }
  }

  std::cout << dp[m][0] << "\n";

  return 0;
}
