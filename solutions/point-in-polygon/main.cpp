#include <cmath>
#include <iostream>
#include <string>
#include <vector>

template <typename T> int Sign(T value) {
  return (T(0) < value) - (value < T(0));
}

struct Point {
  int x;
  int y;
};

Point operator-(const Point &a, const Point &b) {
  return {a.x - b.x, a.y - b.y};
}

std::istream &operator>>(std::istream &in, Point &p) {
  in >> p.x >> p.y;
  return in;
}

long long CrossProduct(const Point &a, const Point &b) {
  return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

struct Segment {
  Point p;
  Point q;
};

int PointLocation(const Point &p, const Segment &s) {
  return Sign(CrossProduct(p - s.p, p - s.q));
}

bool IsPointOnSegment(const Point &p, const Segment &s) {
  return std::min(s.p.x, s.q.x) <= p.x && p.x <= std::max(s.p.x, s.q.x) &&
         std::min(s.p.y, s.q.y) <= p.y && p.y <= std::max(s.p.y, s.q.y) &&
         PointLocation(p, s) == 0;
}

bool IsVerticalDownRayIntersectSegment(const Point &p, const Segment &s) {
  return (s.p.x <= p.x && p.x < s.q.x && PointLocation(p, s) > 0) ||
         (s.q.x <= p.x && p.x < s.p.x && PointLocation(p, s) < 0);
}

std::string PointLocation(const Point &p, std::vector<Point> &polygon) {
  const int n = polygon.size();

  int intersection_count = 0;
  for (int i = 0; i < n; ++i) {
    Segment s{polygon[i], polygon[(i + 1) % n]};
    if (IsPointOnSegment(p, s)) {
      return "BOUNDARY";
    }
    intersection_count += IsVerticalDownRayIntersectSegment(p, s);
  }

  return intersection_count % 2 == 0 ? "OUTSIDE" : "INSIDE";
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m;
  std::cin >> n >> m;

  std::vector<Point> polygon(n);
  for (auto &point : polygon) {
    std::cin >> point;
  }

  while (m--) {
    Point point;
    std::cin >> point;

    std::cout << PointLocation(point, polygon) << "\n";
  }

  return 0;
}
