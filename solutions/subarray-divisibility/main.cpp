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

  std::vector<long long> freq(n);
  freq[0] = 1;

  long long sum = 0, ans = 0;
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;

    sum += a;
    ans += freq[(sum % n + n) % n]++;
  }

  std::cout << ans << "\n";

  return 0;
}
