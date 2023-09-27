#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<int> desired(n);
  for (auto &a : desired) {
    std::cin >> a;
  }

  std::vector<int> actual(m);
  for (auto &a : actual) {
    std::cin >> a;
  }

  std::sort(desired.begin(), desired.end());
  std::sort(actual.begin(), actual.end());

  int ans = 0;
  for (int i = 0, j = 0; i < n && j < m;) {
    if (std::abs(desired[i] - actual[j]) <= k) {
      ++ans;
      ++i, ++j;
    } else if (desired[i] > actual[j] + k) {
      ++j;
    } else {
      ++i;
    }
  }

  std::cout << ans << "\n";

  return 0;
}
