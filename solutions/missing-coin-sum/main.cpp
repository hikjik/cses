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

  long long sum = 0;
  for (auto a : nums) {
    if (sum + 1 < a) {
      break;
    }
    sum += a;
  }

  std::cout << sum + 1 << "\n";

  return 0;
}
