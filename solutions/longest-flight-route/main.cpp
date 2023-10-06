#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using Graph = std::vector<std::vector<int>>;

std::vector<int> ComputeLongestFlightRoute(int source, int target,
                                           const Graph &graph) {
  const int n = graph.size();

  std::vector<int> in_degree(n);
  for (int u = 0; u < n; ++u) {
    for (auto v : graph[u]) {
      ++in_degree[v];
    }
  }

  std::queue<int> queue;
  for (int u = 0; u < n; ++u) {
    if (!in_degree[u]) {
      queue.push(u);
    }
  }

  std::vector<int> predecessors(n, -1);

  std::vector<int> distances(n, -1);
  distances[source] = 0;

  while (!queue.empty()) {
    auto u = queue.front();
    queue.pop();

    for (auto v : graph[u]) {
      if (distances[u] != -1 && distances[v] < distances[u] + 1) {
        distances[v] = distances[u] + 1;
        predecessors[v] = u;
      }

      if (!--in_degree[v]) {
        queue.push(v);
      }
    }
  }

  if (distances[target] == -1) {
    return {};
  }

  std::vector<int> route(distances[target] - distances[source] + 1);
  for (int i = route.size() - 1, v = target; i >= 0; --i) {
    route[i] = v;
    v = predecessors[v];
  }
  return route;
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

    graph[a - 1].push_back(b - 1);
  }

  const auto route = ComputeLongestFlightRoute(0, n - 1, graph);

  if (route.empty()) {
    std::cout << "IMPOSSIBLE\n";
  } else {
    std::cout << route.size() << "\n";
    for (auto u : route) {
      std::cout << u + 1 << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
