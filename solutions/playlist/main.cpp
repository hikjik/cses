#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<int> nums(n);
  for (auto &a : nums) {
    std::cin >> a;
  }

  int start = 0, length = 0;
  std::map<int, int> positions;
  for (int i = 0; i < n; ++i) {
    if (auto it = positions.find(nums[i]); it != positions.end()) {
      length = std::max(length, i - start);
      for (int j = start; j < it->second + 1; ++j) {
        positions.erase(nums[j]);
      }
      start = it->second + 1;
    }
    positions.insert({nums[i], i});
  }

  std::cout << std::max(length, n - start) << "\n";

  return 0;
}
