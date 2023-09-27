#include <iostream>
#include <unordered_map>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  int n, k;
  std::cin >> n >> k;

  std::vector<int> arr(n);
  for (auto &a : arr) {
    std::cin >> a;
  }

  std::unordered_map<int, int> uniq;

  long long ans = 0;
  int i = 0, j = 0;
  while (j < n) {
    ++uniq[arr[j]];
    while (uniq.size() > k) {
      ans += j - i;
      if (!--uniq[arr[i]]) {
        uniq.erase(arr[i]);
      }
      ++i;
    }
    ++j;
  }
  ans += (j - i + 1LL) * (j - i) / 2;

  std::cout << ans << "\n";

  return 0;
}
