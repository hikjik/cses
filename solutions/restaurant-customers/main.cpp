#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> events;
  events.reserve(2 * n);
  while (n--) {
    int a, b;
    std::cin >> a >> b;

    events.push_back({a, 1});
    events.push_back({b, -1});
  }

  std::sort(events.begin(), events.end());

  int ans = 0, cnt = 0;
  for (const auto &[_, d] : events) {
    cnt += d;
    ans = std::max(ans, cnt);
  }

  std::cout << ans << "\n";

  return 0;
}
