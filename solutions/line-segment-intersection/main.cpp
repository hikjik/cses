#include <algorithm>
#include <iostream>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

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

std::istream &operator>>(std::istream &in, Segment &s) {
  in >> s.p >> s.q;
  return in;
}

int PointLocation(const Point &p, const Segment &s) {
  return Sign(CrossProduct(p - s.p, p - s.q));
}

bool IsPointOnSegment(const Point &p, const Segment &s) {
  return std::min(s.p.x, s.q.x) <= p.x && p.x <= std::max(s.p.x, s.q.x) &&
         std::min(s.p.y, s.q.y) <= p.y && p.y <= std::max(s.p.y, s.q.y) &&
         PointLocation(p, s) == 0;
}

bool IsIntersect(const Segment &s1, const Segment &s2) {
  if (PointLocation(s1.p, s2) != PointLocation(s1.q, s2) &&
      PointLocation(s2.p, s1) != PointLocation(s2.q, s1)) {
    return true;
  }
  return IsPointOnSegment(s1.p, s2) || IsPointOnSegment(s1.q, s2) ||
         IsPointOnSegment(s2.p, s1) || IsPointOnSegment(s2.q, s1);
}

int main() {
  fast_io();

  int t;
  std::cin >> t;

  while (t--) {
    Segment s1, s2;
    std::cin >> s1 >> s2;

    std::cout << (IsIntersect(s1, s2) ? "YES" : "NO") << "\n";
  }

  return 0;
}
