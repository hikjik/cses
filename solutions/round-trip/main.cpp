#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

using Graph = std::vector<std::vector<int>>;

Graph ReadGraph() {
  int n, m;
  std::cin >> n >> m;

  Graph graph(n + 1);
  while (m--) {
    int a, b;
    std::cin >> a >> b;

    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  return graph;
}

class Visitor {
public:
  explicit Visitor(int n) : predecessors_(n) {}

  void TreeEdge(int from, int to) { predecessors_[to] = from; }

  void BackEdge(int from, int to) {
    if (to == predecessors_[from]) {
      return;
    }
    BuildCycle(to, from);
  }

  const std::vector<int> &Cycle() const { return cycle_; }

private:
  void BuildCycle(int start, int end) {
    if (!cycle_.empty()) {
      return;
    }

    cycle_.push_back(start);
    for (int u = end; u != start; u = predecessors_[u]) {
      cycle_.push_back(u);
    }
    cycle_.push_back(start);
  }

  std::vector<int> predecessors_;
  std::vector<int> cycle_;
};

void DepthFirstSearch(int u, const Graph &graph, std::vector<bool> *visited,
                      Visitor *visitor) {
  (*visited)[u] = true;
  for (auto v : graph[u]) {
    if (!(*visited)[v]) {
      visitor->TreeEdge(u, v);
      DepthFirstSearch(v, graph, visited, visitor);
    } else {
      visitor->BackEdge(u, v);
    }
  }
}

std::vector<int> FindAnyCycle(const Graph &graph) {
  const int n = graph.size();

  std::vector<bool> visited(n);
  Visitor visitor(n);

  for (int u = 0; u < n; ++u) {
    if (!visited[u]) {
      DepthFirstSearch(u, graph, &visited, &visitor);
    }
  }

  return visitor.Cycle();
}

int main() {
  fast_io();

  const auto cycle = FindAnyCycle(ReadGraph());

  if (cycle.empty()) {
    std::cout << "IMPOSSIBLE\n";
    return 0;
  }

  std::cout << cycle.size() << "\n";
  for (auto c : cycle) {
    std::cout << c << " ";
  }
  std::cout << "\n";
  return 0;
}
