#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

void FindMinDifference(long long left, long long right, size_t i,
                       const std::vector<int> weights, long long *difference) {
  if (i == weights.size()) {
    *difference = std::min(*difference, std::abs(left - right));
    return;
  }

  FindMinDifference(left + weights[i], right, i + 1, weights, difference);
  FindMinDifference(left, right + weights[i], i + 1, weights, difference);
}

int main() {
  int n;
  std::cin >> n;

  std::vector<int> weights(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> weights[i];
  }

  auto difference = std::numeric_limits<long long>::max();
  FindMinDifference(0, 0, 0, weights, &difference);

  std::cout << difference << "\n";

  return 0;
}
