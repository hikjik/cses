#include <cmath>
#include <iostream>
#include <vector>

struct Point {
  int x;
  int y;
};

std::istream &operator>>(std::istream &in, Point &p) {
  in >> p.x >> p.y;
  return in;
}

long long CrossProduct(const Point &a, const Point &b) {
  return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

long long DoubledAreaOfPolygon(const std::vector<Point> &polygon) {
  long long area = 0;
  for (size_t i = 0; i < polygon.size(); ++i) {
    area += CrossProduct(polygon[i], polygon[(i + 1) % polygon.size()]);
  }
  return std::abs(area);
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n;
  std::cin >> n;

  std::vector<Point> polygon(n);
  for (auto &point : polygon) {
    std::cin >> point;
  }

  std::cout << DoubledAreaOfPolygon(polygon) << "\n";

  return 0;
}
