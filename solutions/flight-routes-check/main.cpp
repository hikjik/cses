#include <iostream>
#include <vector>

void DepthFirstSearch(int u, std::vector<std::vector<int>> &graph,
                      std::vector<bool> *visited) {
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

  std::vector<std::vector<int>> graph(n), reversed_graph(n);
  while (m--) {
    int a, b;
    std::cin >> a >> b;

    graph[a - 1].push_back(b - 1);
    reversed_graph[b - 1].push_back(a - 1);
  }

  {
    std::vector<bool> visited(n);
    DepthFirstSearch(0, graph, &visited);
    for (int u = 1; u < n; ++u) {
      if (!visited[u]) {
        std::cout << "NO\n" << 1 << " " << u + 1 << "\n";
        return 0;
      }
    }
  }
  {
    std::vector<bool> visited(n);
    DepthFirstSearch(0, reversed_graph, &visited);
    for (int u = 1; u < n; ++u) {
      if (!visited[u]) {
        std::cout << "NO\n" << u + 1 << " " << 1 << "\n";
        return 0;
      }
    }
  }

  std::cout << "YES\n";
  return 0;
}
