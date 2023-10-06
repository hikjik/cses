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

  int sum = (n + 1) * n / 2;
  if (sum % 2 == 1) {
    std::cout << 0 << "\n";
    return 0;
  }

  int half = sum / 2;
  std::vector<int> dp(half + 1);
  dp[half] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= half; ++j) {
      dp[j - i] = (dp[j - i] + dp[j]) % kMod;
    }
  }

  std::cout << dp[0] * 500000004L % kMod << "\n";

  return 0;
}
