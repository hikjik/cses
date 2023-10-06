#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  const int kMaxX = 1e6;

  int n;
  std::cin >> n;

  std::vector<int> dp(kMaxX + 1);
  while (n--) {
    int a;
    std::cin >> a;

    ++dp[a];
  }

  for (int gcd = kMaxX; gcd > 0; --gcd) {
    int cnt = 0;
    for (int d = gcd; d <= kMaxX; d += gcd) {
      cnt += dp[d];
    }
    if (cnt >= 2) {
      std::cout << gcd << "\n";
      break;
    }
  }

  return 0;
}
