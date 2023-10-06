#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n;
  std::cin >> n;

  std::vector<int> dp(n + 1, INT_MAX);
  dp[0] = 0;

  for (int i = 1; i <= n; ++i) {
    for (int m = i; m; m /= 10) {
      const auto r = m % 10;
      if (i - r >= 0 && dp[i - r] != INT_MAX) {
        dp[i] = std::min(dp[i], dp[i - r] + 1);
      }
    }
  }

  std::cout << dp[n] << "\n";

  return 0;
}
