#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  int n, k;
  std::cin >> n >> k;

  std::vector<std::pair<int, int>> arr;
  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;

    arr.push_back({a, b});
  }

  std::sort(arr.begin(), arr.end());

  std::multiset<int> set;
  for (const auto &[a, b] : arr) {
    while (!set.empty() && *set.begin() <= a) {
      set.erase(set.begin());
    }

    set.insert(b);
    if (set.size() > k * 1ULL) {
      --n;
      set.erase(std::prev(set.end()));
    }
  }

  std::cout << n << "\n";

  return 0;
}
