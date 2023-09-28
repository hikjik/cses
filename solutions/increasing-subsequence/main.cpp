#include <algorithm>
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

  std::vector<int> dp;
  dp.reserve(n);

  while (n--) {
    int a;
    std::cin >> a;

    if (auto it = std::lower_bound(dp.begin(), dp.end(), a); it == dp.end()) {
      dp.push_back(a);
    } else {
      *it = a;
    }
  }

  std::cout << dp.size() << "\n";

  return 0;
}
