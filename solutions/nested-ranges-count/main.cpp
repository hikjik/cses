#include <algorithm>
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

void PrintArray(const std::vector<int> &nums) {
  for (auto a : nums) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}

int main() {
  fast_io();

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

  ordered_set<std::pair<int, int>> ordered_set;
  std::vector<int> contained(n);
  for (int i = 0; i < n; ++i) {
    const auto &[a, b, j] = arr[i];
    const auto key = std::make_pair(-b, -i);
    ordered_set.insert(key);
    contained[j] = i - ordered_set.order_of_key(key);
  }

  ordered_set.clear();
  std::vector<int> contains(n);
  for (int i = n - 1; i >= 0; --i) {
    const auto &[a, b, j] = arr[i];
    const auto key = std::make_pair(-b, -i);
    ordered_set.insert(key);
    contains[j] = ordered_set.order_of_key(key);
  }

  PrintArray(contains);
  PrintArray(contained);

  return 0;
}
