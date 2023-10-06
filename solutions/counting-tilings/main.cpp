#include <iostream>
#include <vector>

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

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m;
  std::cin >> n >> m;

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
