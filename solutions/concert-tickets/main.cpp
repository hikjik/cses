#include <iostream>
#include <set>

int main() {
  int n, m;
  std::cin >> n >> m;

  std::multiset<int> prices;
  while (n--) {
    int a;
    std::cin >> a;

    prices.insert(a);
  }

  while (m--) {
    int a;
    std::cin >> a;

    if (auto it = prices.upper_bound(a); it != prices.begin()) {
      std::cout << *--it << "\n";
      prices.erase(it);
    } else {
      std::cout << -1 << "\n";
    }
  }

  return 0;
}
