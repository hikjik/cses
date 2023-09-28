#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

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
