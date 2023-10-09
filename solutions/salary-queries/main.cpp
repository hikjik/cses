#include <iostream>
#include <vector>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag,
                         tree_order_statistics_node_update>;

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, q;
  std::cin >> n >> q;

  std::vector<int> salaries(n);
  for (auto &a : salaries) {
    std::cin >> a;
  }

  ordered_set<std::pair<int, int>> set;
  for (int i = 0; i < n; ++i) {
    set.insert({salaries[i], i});
  }

  while (q--) {
    char c;
    std::cin >> c;

    if (c == '!') {
      int k, x;
      std::cin >> k >> x;
      --k;

      set.erase({salaries[k], k});
      set.insert({salaries[k] = x, k});
    } else if (c == '?') {
      int a, b;
      std::cin >> a >> b;

      std::cout << set.order_of_key({b, INT_MAX}) -
                       set.order_of_key({a - 1, INT_MAX})
                << "\n";
    } else {
      throw;
    }
  }

  return 0;
}
