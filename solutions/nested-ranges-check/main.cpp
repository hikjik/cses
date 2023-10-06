#include <algorithm>
#include <climits>
#include <iostream>
#include <ranges>
#include <tuple>
#include <vector>

void PrintArray(const std::vector<int> &nums) {
  for (auto a : nums) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n;
  std::cin >> n;

  std::vector<std::tuple<int, int, int>> arr;
  arr.reserve(n);
  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;

    arr.push_back({a, -b, i});
  }

  std::sort(arr.begin(), arr.end());

  std::vector<int> contained(n);
  int max_right = 0;
  for (const auto &[a, b, i] : arr) {
    if (-b <= max_right) {
      contained[i] = 1;
    }
    max_right = std::max(max_right, -b);
  }

  std::vector<int> contains(n);
  int min_right = INT_MAX;
  for (const auto &[a, b, i] : std::ranges::reverse_view(arr)) {
    if (-b >= min_right) {
      contains[i] = 1;
    }
    min_right = std::min(min_right, -b);
  }

  PrintArray(contains);
  PrintArray(contained);

  return 0;
}
