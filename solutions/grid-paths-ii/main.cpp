#include <iostream>
#include <string>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  const int kMod = 1e9 + 7;

  int n;
  std::cin >> n;

  std::vector<std::string> grid(n);
  for (auto &row : grid) {
    std::cin >> row;
  }

  std::vector dp(n, std::vector<long long>(n));
  dp[0][0] = grid[0][0] != '*';

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == '*') {
        continue;
      }

      if (i) {
        dp[i][j] = (dp[i][j] + dp[i - 1][j]) % kMod;
      }

      if (j) {
        dp[i][j] = (dp[i][j] + dp[i][j - 1]) % kMod;
      }
    }
  }

  std::cout << dp.back().back() << "\n";

  return 0;
}
