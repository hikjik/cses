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
