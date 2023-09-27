#include <iostream>
#include <map>

int main() {
  int n, x;
  std::cin >> n >> x;

  std::map<int, int> nums;
  for (int i = 1; i <= n; ++i) {
    int a;
    std::cin >> a;

    if (auto it = nums.find(a); it != nums.end()) {
      std::cout << it->second << " " << i << "\n";
      return 0;
    } else {
      nums[x - a] = i;
    }
  }

  std::cout << "IMPOSSIBLE\n";
  return 0;
}
