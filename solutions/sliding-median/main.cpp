#include <iostream>
#include <vector>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag,
                         tree_order_statistics_node_update>;

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

  ordered_set<std::pair<int, int>> set;
  for (int i = 0; i < k - 1; ++i) {
    set.insert({arr[i], i});
  }

  for (int i = k - 1; i < n; ++i) {
    set.insert({arr[i], i});
    std::cout << set.find_by_order((k - 1) / 2)->first << " ";
    set.erase({arr[i - k + 1], i - k + 1});
  }

  return 0;
}
