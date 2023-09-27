#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

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
