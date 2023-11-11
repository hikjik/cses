#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, x;
  std::cin >> n >> x;

  if (n < 4) {
    std::cout << "IMPOSSIBLE\n";
    return 0;
  }

  std::vector<std::pair<long long, int>> arr(n);
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    arr[i] = {a, i + 1};
  }

  std::sort(arr.begin(), arr.end());
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int l = j + 1, r = n - 1;
      while (l < r) {
        const auto sum =
            arr[i].first + arr[j].first + arr[l].first + arr[r].first;
        if (sum == x) {
          std::cout << arr[i].second << ' ' << arr[j].second << ' '
                    << arr[l].second << ' ' << arr[r].second << '\n';
          return 0;
        }
        sum < x ? ++l : --r;
      }
    }
  }

  std::cout << "IMPOSSIBLE\n";
  return 0;
}
