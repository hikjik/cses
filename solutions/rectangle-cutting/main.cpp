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

  int a, b;
  std::cin >> a >> b;

  std::vector dp(a, std::vector<int>(b));
  for (int i = 0; i < a; ++i) {
    dp[i][0] = i;
  }
  for (int j = 0; j < b; ++j) {
    dp[0][j] = j;
  }

  for (int i = 1; i < a; ++i) {
    for (int j = 1; j < b; ++j) {
      if (i == j) {
        dp[i][j] = 0;
      } else {
        dp[i][j] = INT_MAX;
        for (int k = 0; k < i - 1; ++k) {
          dp[i][j] = std::min(dp[i][j], dp[k][j] + dp[i - k - 1][j]);
        }
        for (int k = 0; k < j - 1; ++k) {
          dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[i][j - k - 1]);
        }
        ++dp[i][j];
      }
    }
  }

  std::cout << dp[a - 1][b - 1] << "\n";

  return 0;
}
