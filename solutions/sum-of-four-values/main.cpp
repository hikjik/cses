#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, x;
  std::cin >> n >> x;

  if (n < 4) {
    std::cout << "IMPOSSIBLE\n";
    return 0;
  }

  std::vector<int> arr(n);
  for (auto &a : arr) {
    std::cin >> a;
  }

  std::vector<std::tuple<long long, int, int>> pairs_sum;
  pairs_sum.reserve(n * (n - 1) / 2);
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      pairs_sum.push_back({arr[i] + arr[j], i + 1, j + 1});
    }
  }

  std::sort(pairs_sum.begin(), pairs_sum.end());

  size_t l = 0, r = pairs_sum.size() - 1;
  while (l < r) {
    const auto &[a, i, j] = pairs_sum[l];
    const auto &[b, s, t] = pairs_sum[r];
    const auto sum = a + b;

    if (sum == x && std::set<int>({i, j, s, t}).size() == 4) {
      std::cout << i << " " << j << " " << s << " " << t << "\n";
      return 0;
    }

    sum < x ? ++l : --r;
  }

  std::cout << "IMPOSSIBLE\n";

  return 0;
}
