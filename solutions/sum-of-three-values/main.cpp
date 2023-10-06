#include <algorithm>
#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, x;
  std::cin >> n >> x;

  std::vector<std::pair<int, int>> arr;
  arr.reserve(n);
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;

    arr.emplace_back(a, i);
  }
  std::sort(arr.begin(), arr.end());

  for (int i = 0; i < n; ++i) {
    const auto target = x - arr[i].first;
    int l = 0, r = n - 1;
    while (l < r) {
      int sum = arr[l].first + arr[r].first;
      if (l != i && r != i && sum == target) {
        std::cout << arr[l].second + 1 << " " << arr[r].second + 1 << " "
                  << arr[i].second + 1 << "\n";
        return 0;
      }
      sum < target ? ++l : --r;
    }
  }

  std::cout << "IMPOSSIBLE\n";

  return 0;
}
