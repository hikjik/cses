#include <cmath>
#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

struct Point {
  int x;
  int y;
};

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

int main() {
  fast_io();

  int n;
  std::cin >> n;

  std::vector<Point> polygon(n);
  for (auto &point : polygon) {
    std::cin >> point.x >> point.y;
  }

  std::cout << DoubledAreaOfPolygon(polygon) << "\n";

  return 0;
}
