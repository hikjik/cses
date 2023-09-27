#include <iostream>
#include <numeric>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  std::iota(a.begin(), a.end(), 1);

  while (!a.empty()) {
    if (a.size() == 1) {
      std::cout << a[0] << "\n";
      break;
    }

    std::vector<int> b;
    b.reserve(n / 2 + 1);

    if (a.size() % 2) {
      b.push_back(a.back());
      a.pop_back();
    }

    for (size_t i = 0; i + 1 < a.size(); i += 2) {
      b.push_back(a[i]);
      std::cout << a[i + 1] << " ";
    }

    a.swap(b);
  }

  return 0;
}
