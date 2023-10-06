#include <iostream>
#include <unordered_map>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, x;
  std::cin >> n >> x;

  long long ans = 0, sum = 0;
  std::unordered_map<long long, long long> map{{0, 1}};
  while (n--) {
    int a;
    std::cin >> a;

    sum += a;
    ans += map[sum - x];
    ++map[sum];
  }

  std::cout << ans << "\n";

  return 0;
}
