#include <iostream>
#include <optional>
#include <queue>
#include <vector>

std::optional<std::vector<int>>
BipartiteGraph(const std::vector<std::vector<int>> &graph) {
  const int n = graph.size();

  std::vector<int> colors(n);
  for (int u = 0; u < n; ++u) {
    if (colors[u]) {
      continue;
    }

    colors[u] = 1;

    std::queue<int> queue{{u}};
    while (!queue.empty()) {
      const auto u = queue.front();
      queue.pop();

      for (auto v : graph[u]) {
        if (colors[v] == colors[u]) {
          return std::nullopt;
        }
        if (!colors[v]) {
          colors[v] = 3 - colors[u];
          queue.push(v);
        }
      }
    }
  }

  return colors;
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(n);
  while (m--) {
    int a, b;
    std::cin >> a >> b;

    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }

  const auto colors = BipartiteGraph(graph);

  if (!colors) {
    std::cout << "IMPOSSIBLE\n";
    return 0;
  }

  for (auto c : *colors) {
    std::cout << c << " ";
  }
  std::cout << "\n";
  return 0;
}
