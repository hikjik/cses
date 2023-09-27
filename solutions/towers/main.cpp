#include <iostream>
#include <set>

int main() {
  int n;
  std::cin >> n;

  std::multiset<int> set;
  while (n--) {
    int a;
    std::cin >> a;

    if (auto it = set.upper_bound(a); it != set.end()) {
      set.erase(it);
    }
    set.insert(a);
  }

  std::cout << set.size() << "\n";

  return 0;
}
