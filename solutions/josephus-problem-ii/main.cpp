#include <iostream>

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

  ordered_set<int> children;
  for (int i = 1; i <= n; ++i) {
    children.insert(i);
  }

  int start = 0;
  while (!children.empty()) {
    start %= children.size();

    int pos = (start + k) % children.size();
    start = pos;

    auto it = children.find_by_order(pos);
    std::cout << *it << " ";
    children.erase(it);
  }

  return 0;
}
