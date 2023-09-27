#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  int n, a, b;
  std::cin >> n >> a >> b;

  std::vector<long long> prefix_sum(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> prefix_sum[i];
    prefix_sum[i] += prefix_sum[i - 1];
  }

  std::multiset<long long> set;
  auto ans = std::numeric_limits<long long>::min();
  for (int i = a; i <= n; ++i) {
    if (i > b) {
      set.erase(set.find(prefix_sum[i - b - 1]));
    }

    set.insert(prefix_sum[i - a]);
    ans = std::max(ans, prefix_sum[i] - *set.begin());
  }

  std::cout << ans << "\n";

  return 0;
}
