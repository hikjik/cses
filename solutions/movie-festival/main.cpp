#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> movies;
  while (n--) {
    int a, b;
    std::cin >> a >> b;

    movies.push_back({b, a});
  }

  std::sort(movies.begin(), movies.end());

  int ans = 0, cur = 0;
  for (const auto &[end, start] : movies) {
    if (cur <= start) {
      ++ans;
      cur = end;
    }
  }

  std::cout << ans << "\n";

  return 0;
}
