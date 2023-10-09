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

  int n;
  std::cin >> n;

  std::vector<int> nums(n);
  for (auto &x : nums) {
    std::cin >> x;
  }

  ordered_set<int> set;
  for (int i = 0; i < n; ++i) {
    set.insert(i);
  }

  for (int i = 0; i < n; ++i) {
    int p;
    std::cin >> p;

    const auto it = set.find_by_order(p - 1);
    std::cout << nums[*it] << (i < n - 1 ? ' ' : '\n');
    set.erase(it);
  }

  return 0;
}
