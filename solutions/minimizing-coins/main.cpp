#include <algorithm>
#include <climits>
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

  std::vector<int> coins(n);
  for (auto &c : coins) {
    std::cin >> c;
  }

  std::vector<int> dp(x + 1, INT_MAX);
  dp[0] = 0;

  for (int c : coins) {
    for (int j = 0; j <= x - c; j++) {
      if (dp[j] != INT_MAX) {
        dp[j + c] = std::min(dp[j + c], dp[j] + 1);
      }
    }
  }

  std::cout << (dp[x] != INT_MAX ? dp[x] : -1) << "\n";

  return 0;
}
