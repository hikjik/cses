#include <iostream>
#include <set>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  int x, n;
  std::cin >> x >> n;

  std::set<int> positions{0, x};
  std::multiset<int> lengths{x};
  while (n--) {
    int p;
    std::cin >> p;

    auto end = positions.upper_bound(p);
    auto begin = std::prev(end);

    const auto length = *end - *begin;
    lengths.erase(lengths.lower_bound(length));
    lengths.insert(*end - p);
    lengths.insert(p - *begin);

    positions.insert(p);

    std::cout << *lengths.rbegin() << " ";
  }
  std::cout << "\n";

  return 0;
}
