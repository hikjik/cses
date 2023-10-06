#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  const int kMaxX = 1e6;

  std::vector<int> dp(kMaxX + 1);
  for (int i = 1; i <= kMaxX; ++i) {
    for (int j = i; j <= kMaxX; j += i) {
      ++dp[j];
    }
  }

  int n;
  std::cin >> n;

  while (n--) {
    int x;
    std::cin >> x;

    std::cout << dp[x] << "\n";
  }

  return 0;
}
