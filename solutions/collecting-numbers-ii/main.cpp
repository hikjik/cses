#include <climits>
#include <iostream>
#include <set>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> nums(n + 1), index(n + 2);
  index[n + 1] = INT_MAX;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;

    nums[i + 1] = x;
    index[x] = i;
  }

  int rounds = 1;
  for (int i = 1; i <= n; ++i) {
    if (index[i] < index[i - 1]) {
      rounds += 1;
    }
  }

  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;

    std::set<std::pair<int, int>> pairs{
        {nums[a] - 1, nums[a]},
        {nums[a], nums[a] + 1},
        {nums[b] - 1, nums[b]},
        {nums[b], nums[b] + 1},
    };

    for (auto [x, y] : pairs) {
      if (index[x] > index[y]) {
        --rounds;
      }
    }
    std::swap(index[nums[a]], index[nums[b]]);
    std::swap(nums[a], nums[b]);
    for (auto [x, y] : pairs) {
      if (index[x] > index[y]) {
        ++rounds;
      }
    }

    std::cout << rounds << "\n";
  }

  return 0;
}
