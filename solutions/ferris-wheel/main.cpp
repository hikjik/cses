#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, x;
  std::cin >> n >> x;

  std::vector<int> weights(n);
  for (auto &weight : weights) {
    std::cin >> weight;
  }

  std::sort(weights.begin(), weights.end());

  int ans = 0;
  for (int i = 0, j = n - 1; i <= j; --j) {
    ++ans;
    if (weights[i] + weights[j] <= x) {
      ++i;
    }
  }

  std::cout << ans << "\n";

  return 0;
}
