#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void DepthFirstSearch(int u, const Graph &graph, std::vector<bool> *visited) {
  (*visited)[u] = true;
  for (auto v : graph[u]) {
    if (!(*visited)[v]) {
      DepthFirstSearch(v, graph, visited);
    }
  }
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m;
  std::cin >> n >> m;

  Graph graph(n);
  while (m--) {
    int a, b;
    std::cin >> a >> b;
    --a, --b;

    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  std::vector<int> roads;
  std::vector<bool> visited(n);
  for (int u = 0; u < n; ++u) {
    if (!visited[u]) {
      roads.push_back(u);
      DepthFirstSearch(u, graph, &visited);
    }
  }

  std::cout << roads.size() - 1 << "\n";
  for (size_t i = 0; i + 1 < roads.size(); ++i) {
    std::cout << roads[i] + 1 << " " << roads[i + 1] + 1 << "\n";
  }

  return 0;
}
