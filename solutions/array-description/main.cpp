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

  int n, m;
  std::cin >> n >> m;

  std::vector<int> arr(n);
  for (auto &a : arr) {
    std::cin >> a;
  }

  std::vector dp(n, std::vector<long long>(m + 2));
  if (!arr[0]) {
    for (int j = 1; j <= m; ++j) {
      dp[0][j] = 1;
    }
  } else {
    dp[0][arr[0]] = 1;
  }

  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= m; ++j) {
      dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1]) % kMod;
      if (arr[i] != 0 && arr[i] != j) {
        dp[i][j] = 0;
      }
    }
  }

  long long ans = 0;
  for (int j = 0; j <= m; ++j) {
    ans = (ans + dp[n - 1][j]) % kMod;
  }

  std::cout << ans << "\n";

  return 0;
}
