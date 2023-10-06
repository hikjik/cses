#include <algorithm>
#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, k;
  std::cin >> n >> k;

  std::vector<int> arr(n);
  for (auto &a : arr) {
    std::cin >> a;
  }

  long long left = *std::max_element(arr.begin(), arr.end());
  long long right = 2e14;
  while (left < right) {
    const auto middle = left + (right - left) / 2;

    int count = 1;
    long long sum = 0;
    for (auto a : arr) {
      sum += a;
      if (sum > middle) {
        sum = a;
        ++count;
      }
    }

    k < count ? left = middle + 1 : right = middle;
  }

  std::cout << left << "\n";

  return 0;
}
