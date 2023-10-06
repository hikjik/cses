#include <iostream>
#include <vector>

enum class Color {
  kWhite = 0,
  kGrey,
  kBlack,
};

struct Vertex {
  int cycle_id;
  int distance_to_cycle;
  int index_on_cycle;
};

struct Cycle {
  int id;
  int size;
};

class Visitor {
public:
  Visitor(int n, std::vector<Vertex> *vertexes, std::vector<Cycle> *cycles)
      : vertexes_(*vertexes), cycles_(*cycles), discover_time_(n) {}

  void StartVertex(int u) { clock_ = 0; }

  void DiscoverVertex(int u) { discover_time_[u] = clock_++; }

  void FinishVertex(int u) {
    vertexes_[u].cycle_id = cycle_id_;

    if (on_cycle_) {
      vertexes_[u].distance_to_cycle = 0;
      vertexes_[u].index_on_cycle = --on_cycle_;
    } else {
      vertexes_[u].distance_to_cycle = ++distance_;
      vertexes_[u].index_on_cycle = -1;
    }
  }

  void BackEdge(int u, int v) {
    const auto cycle = Cycle{
        .id = static_cast<int>(cycles_.size()),
        .size = clock_ - discover_time_[v],
    };
    cycles_.push_back(cycle);

    on_cycle_ = cycle.size;
    cycle_id_ = cycle.id;
    distance_ = 0;
  }

  void ForwardEdge(int u, int v) {
    on_cycle_ = 0;
    cycle_id_ = vertexes_[v].cycle_id;
    distance_ = vertexes_[v].distance_to_cycle;
  }

private:
  std::vector<Vertex> &vertexes_;
  std::vector<Cycle> &cycles_;

  std::vector<int> discover_time_;
  int cycle_id_;
  int distance_;
  int on_cycle_;
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

class SuccessorGraph {
public:
  SuccessorGraph(int n, const std::vector<int> &destinations) : vertexes_(n) {
    ExploreGraph(n, destinations);
  }

  int CycleId(int u) const { return vertexes_[u].cycle_id; }
  int DistanceToCycle(int u) const { return vertexes_[u].distance_to_cycle; }
  int CycleSize(int u) const { return cycles_[CycleId(u)].size; }

private:
  void ExploreGraph(int n, const std::vector<int> &destinations) {
    std::vector<Color> colors(n, Color::kWhite);
    Visitor visitor(n, &vertexes_, &cycles_);
    for (int u = 0; u < n; ++u) {
      if (colors[u] == Color::kWhite) {
        visitor.StartVertex(u);
        DepthFirstSearch(u, destinations, &colors, &visitor);
      }
    }
  }

  std::vector<Vertex> vertexes_;
  std::vector<Cycle> cycles_;
};

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n;
  std::cin >> n;

  std::vector<int> destinations(n);
  for (auto &a : destinations) {
    std::cin >> a;
    --a;
  }

  const auto graph = SuccessorGraph(n, destinations);

  for (int u = 0; u < n; ++u) {
    std::cout << graph.DistanceToCycle(u) + graph.CycleSize(u) << " ";
  }
  std::cout << "\n";

  return 0;
}
