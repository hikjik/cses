#include <algorithm>
#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, x;
  std::cin >> n >> x;

  std::vector<int> weights(n);
  for (auto &w : weights) {
    std::cin >> w;
  }

  std::vector<std::pair<int, int>> dp(1 << n);
  dp[0] = {1, 0};

  for (int s = 1; s < 1 << n; ++s) {
    dp[s] = {n + 1, 0};
    for (int p = 0; p < n; ++p) {
      if (s & (1 << p)) {
        auto option = dp[s ^ (1 << p)];
        if (option.second + weights[p] <= x) {
          option.second += weights[p];
        } else {
          ++option.first;
          option.second = weights[p];
        }
        dp[s] = std::min(dp[s], option);
      }
    }
  }

  std::cout << dp.back().first << "\n";

  return 0;
}
