#include <algorithm>
#include <iostream>
#include <map>
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

  std::vector<std::tuple<int, int, int>> projects(n);
  for (auto &[end, start, reward] : projects) {
    std::cin >> start >> end >> reward;
  }

  std::sort(projects.begin(), projects.end());

  long long ans = 0;
  std::map<int, long long> dp{{0, 0}};
  for (const auto &[end, start, reward] : projects) {
    auto it = dp.lower_bound(start);
    ans = std::max(ans, prev(it)->second + reward);
    dp[end] = ans;
  }

  std::cout << ans << "\n";

  return 0;
}
