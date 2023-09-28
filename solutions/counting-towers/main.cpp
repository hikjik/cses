#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  const int kMaxN = 1e6;
  const int kMod = 1e9 + 7;

  std::vector dp(3, std::vector<long long>(kMaxN + 1));
  dp[0][1] = dp[1][1] = 1;

  for (int j = 2; j <= kMaxN; ++j) {
    dp[0][j] = (dp[0][j - 1] * 2 + dp[1][j - 1]) % kMod;
    dp[1][j] = (dp[0][j - 1] + dp[1][j - 1] * 4) % kMod;
  }

  for (int j = 0; j <= kMaxN; ++j) {
    dp[2][j] = (dp[0][j] + dp[1][j]) % kMod;
  }

  int t;
  std::cin >> t;
  while (t--) {
    int n;
    std::cin >> n;

    std::cout << dp[2][n] << "\n";
  }

  return 0;
}
