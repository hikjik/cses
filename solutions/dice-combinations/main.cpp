#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  const int kMod = 1e9 + 7;

  int n;
  std::cin >> n;

  std::vector<int> dp(n + 1);
  dp[0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= 6 && i - j >= 0; ++j) {
      dp[i] = (dp[i] + dp[i - j]) % kMod;
    }
  }

  std::cout << dp[n] << "\n";

  return 0;
}
