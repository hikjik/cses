#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, t;
  std::cin >> n >> t;

  std::vector<int> arr(n);
  for (auto &a : arr) {
    std::cin >> a;
  }

  long long left = 1, right = 1e18;
  while (left < right) {
    const auto middle = left + (right - left) / 2;

    auto sum = 0LL;
    for (auto a : arr) {
      sum += middle / a;
      if (sum >= t) {
        break;
      }
    }

    sum < t ? left = middle + 1 : right = middle;
  }

  std::cout << left << "\n";

  return 0;
}
