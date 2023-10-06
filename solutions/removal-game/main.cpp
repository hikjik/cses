#include <algorithm>
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

  std::vector<int> scores(n);
  long long sum = 0;
  for (auto &s : scores) {
    std::cin >> s;
    sum += s;
  }

  std::vector dp(n, std::vector<long long>(n));
  for (int l = n - 1; l >= 0; --l) {
    for (int r = l; r < n; ++r) {
      if (l == r) {
        dp[l][r] = scores[l];
      } else {
        dp[l][r] = std::max(scores[l] - dp[l + 1][r], scores[r] - dp[l][r - 1]);
      }
    }
  }

  std::cout << (sum + dp[0][n - 1]) / 2 << "\n";

  return 0;
}
