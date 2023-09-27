#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<long long> nums(n);
  for (auto &a : nums) {
    std::cin >> a;
  }

  auto max_sum = std::numeric_limits<long long>::min();
  auto sum = 0LL;
  for (auto a : nums) {
    sum = std::max(a, a + sum);
    max_sum = std::max(max_sum, sum);
  }

  std::cout << max_sum << "\n";

  return 0;
}
