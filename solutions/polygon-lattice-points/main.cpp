#include <cmath>
#include <iostream>
#include <numeric>
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

std::istream &operator>>(std::istream &in, Point &p) {
  in >> p.x >> p.y;
  return in;
}

long long CrossProduct(const Point &a, const Point &b) {
  return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

long long DoubledAreaOfPolygon(const std::vector<Point> &polygon) {
  const int n = polygon.size();

  long long area = 0;
  for (int i = 0; i < n; ++i) {
    area += CrossProduct(polygon[i], polygon[(i + 1) % n]);
  }
  return std::abs(area);
}

int CountLineLatticePoints(const Point &a, const Point &b) {
  return std::gcd(std::abs(a.x - b.x), std::abs(a.y - b.y)) + 1;
}

long long CountLatticePointsOnBoundary(const std::vector<Point> &polygon) {
  const int n = polygon.size();

  long long count = 0;
  for (int i = 0; i < n; ++i) {
    count += CountLineLatticePoints(polygon[i], polygon[(i + 1) % n]);
  }
  return count - polygon.size();
}

int main() {
  fast_io();

  int n;
  std::cin >> n;

  std::vector<Point> polygon(n);
  for (auto &point : polygon) {
    std::cin >> point;
  }

  const auto on_boundary = CountLatticePointsOnBoundary(polygon);
  const auto inside = (DoubledAreaOfPolygon(polygon) + 2 - on_boundary) / 2;

  std::cout << inside << " " << on_boundary << "\n";

  return 0;
}
