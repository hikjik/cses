#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> nums;
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;

    while (!nums.empty() && nums.back().first >= a) {
      nums.pop_back();
    }

    if (!nums.empty()) {
      std::cout << nums.back().second << " ";
    } else {
      std::cout << 0 << " ";
    }

    nums.push_back({a, i + 1});
  }
  std::cout << "\n";

  return 0;
}
