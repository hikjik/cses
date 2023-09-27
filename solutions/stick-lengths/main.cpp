#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<int> nums(n);
  for (auto &a : nums) {
    std::cin >> a;
  }

  std::sort(nums.begin(), nums.end());

  auto median = nums[n / 2];

  long long cost = 0;
  for (auto a : nums) {
    cost += std::abs(median - a);
  }

  std::cout << cost << "\n";

  return 0;
}
