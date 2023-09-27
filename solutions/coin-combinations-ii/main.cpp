#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  const int kMod = 1e9 + 7;

  int n, x;
  std::cin >> n >> x;

  std::vector<int> coins(n);
  for (auto &c : coins) {
    std::cin >> c;
  }

  std::vector<int> dp(x + 1);
  dp[0] = 1;

  for (auto c : coins) {
    for (int i = 1; i <= x; ++i) {
      if (i - c >= 0) {
        dp[i] = (dp[i] + dp[i - c]) % kMod;
      }
    }
  }

  std::cout << dp[x] << "\n";

  return 0;
}