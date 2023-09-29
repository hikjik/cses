#include <iostream>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

struct Point {
  int x;
  int y;
};

Point operator-(const Point &a, const Point &b) {
  return {a.x - b.x, a.y - b.y};
}

long long CrossProduct(const Point &a, const Point &b) {
  return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

int main() {
  fast_io();

  int t;
  std::cin >> t;

  while (t--) {
    Point s1, s2, p;
    std::cin >> s1.x >> s1.y >> s2.x >> s2.y >> p.x >> p.y;

    const auto cross_product = CrossProduct(p - s1, p - s2);
    if (cross_product > 0) {
      std::cout << "LEFT\n";
    } else if (cross_product < 0) {
      std::cout << "RIGHT\n";
    } else {
      std::cout << "TOUCH\n";
    }
  }

  return 0;
}
