#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  std::string s, t;
  std::cin >> s >> t;

  const int n = s.size(), m = t.size();

  std::vector dp(n + 1, std::vector<int>(m + 1));
  for (int i = 0; i <= n; ++i) {
    dp[i][0] = i;
  }
  for (int j = 0; j <= m; ++j) {
    dp[0][j] = j;
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (s[i - 1] == t[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = 1 + std::min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
      }
    }
  }

  std::cout << dp[n][m] << "\n";

  return 0;
}
