#include <iostream>
#include <unordered_map>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

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
