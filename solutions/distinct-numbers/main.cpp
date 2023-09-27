#include <iostream>
#include <set>

int main() {
  int n;
  std::cin >> n;

  std::set<int> set;
  while (n--) {
    int a;
    std::cin >> a;

    set.insert(a);
  }

  std::cout << set.size() << "\n";

  return 0;
}
