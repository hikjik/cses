#include <iostream>
#include <string>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, q;
  std::cin >> n >> q;
  std::vector<std::string> grid(n);
  for (auto &row : grid) {
    std::cin >> row;
  }

  std::vector dp(n + 1, std::vector<int>(n + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] +
                 (grid[i - 1][j - 1] == '*');
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;

    std::cout << dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] +
                     dp[x1 - 1][y1 - 1]
              << "\n";
  }

  return 0;
}
