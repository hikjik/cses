#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

enum class Color {
  kWhite = 0,
  kGrey,
  kBlack,
};

class Visitor {
public:
  Visitor(std::vector<int> *travel_time)
      : travel_time_(*travel_time), discover_time_(travel_time->size()) {}

  void StartVertex(int u) { clock_ = 0; }

  void DiscoverVertex(int u) { discover_time_[u] = clock_++; }

  void FinishVertex(int u) {
    cycle_ ? --cycle_ : ++time_;
    travel_time_[u] = time_;
  }

  void BackEdge(int u, int v) {
    time_ = clock_ - discover_time_[v];
    cycle_ = time_;
  }

  void ForwardEdge(int u, int v) {
    time_ = travel_time_[v] + 1;
    cycle_ = 1;
  }

private:
  std::vector<int> &travel_time_;
  std::vector<int> discover_time_;
  int time_, cycle_;
  int clock_;
};

void DepthFirstSearch(int u, const std::vector<int> &successors,
                      std::vector<Color> *colors, Visitor *visitor) {
  visitor->DiscoverVertex(u);
  (*colors)[u] = Color::kGrey;

  const auto v = successors[u];
  if (Color::kWhite == (*colors)[v]) {
    DepthFirstSearch(v, successors, colors, visitor);
  } else if (Color::kGrey == (*colors)[v]) {
    visitor->BackEdge(u, v);
  } else if (Color::kBlack == (*colors)[v]) {
    visitor->ForwardEdge(u, v);
  } else {
    throw;
  }

  visitor->FinishVertex(u);
  (*colors)[u] = Color::kBlack;
}

std::vector<int> CalculateNumberOfJumps(int n,
                                        const std::vector<int> &successors) {
  std::vector<Color> colors(n, Color::kWhite);

  std::vector<int> travel_time(n);
  Visitor visitor(&travel_time);

  for (int u = 0; u < n; ++u) {
    if (colors[u] == Color::kWhite) {
      visitor.StartVertex(u);
      DepthFirstSearch(u, successors, &colors, &visitor);
    }
  }

  return travel_time;
}

int main() {
  fast_io();

  int n;
  std::cin >> n;

  std::vector<int> successors(n);
  for (auto &a : successors) {
    std::cin >> a;
    --a;
  }

  for (auto a : CalculateNumberOfJumps(n, successors)) {
    std::cout << a << " ";
  }
  std::cout << "\n";

  return 0;
}
