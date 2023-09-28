#include <algorithm>
#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  int n, x;
  std::cin >> n >> x;

  std::vector<int> prices(n);
  for (auto &price : prices) {
    std::cin >> price;
  }

  std::vector<int> pages(n);
  for (auto &page : pages) {
    std::cin >> page;
  }

  std::vector dp(n + 1, std::vector<int>(x + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= x; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j - prices[i - 1] >= 0) {
        dp[i][j] =
            std::max(dp[i][j], dp[i - 1][j - prices[i - 1]] + pages[i - 1]);
      }
    }
  }

  std::cout << dp[n][x] << "\n";

  return 0;
}
