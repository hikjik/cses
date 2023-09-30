#include <iostream>
#include <tuple>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

// Bellman–Ford algorithm
std::vector<int> FindCycle(int n, int source,
                           std::vector<std::tuple<int, int, int>> &edges) {
  static const long long kInf = 0x3f3f3f3f3f3f3f3f;

  std::vector<long long> distances(n, kInf);
  distances[source] = 0;

  std::vector<int> predecessors(n);

  for (int i = 0; i < n - 1; ++i) {
    for (const auto &[u, v, w] : edges) {
      if (distances[v] > distances[u] + w) {
        distances[v] = distances[u] + w;
        predecessors[v] = u;
      }
    }
  }

  for (const auto &[u, v, w] : edges) {
    if (distances[v] > distances[u] + w) {
      predecessors[v] = u;

      // v is reachable from negative cycle, go backward to find cycle
      auto a = v;
      for (int i = 0; i < n; ++i) {
        a = predecessors[a];
      }

      std::vector<int> cycle{a};
      for (auto b = predecessors[a]; b != a; b = predecessors[b]) {
        cycle.push_back(b);
      }
      cycle.push_back(a);
      std::reverse(cycle.begin(), cycle.end());
      return cycle;
    }
  }

  return {};
}

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;
  std::vector<std::tuple<int, int, int>> edges;
  while (m--) {
    int a, b, w;
    std::cin >> a >> b >> w;

    edges.emplace_back(a - 1, b - 1, w);
  }

  const auto cycle = FindCycle(n, 0, edges);

  if (cycle.empty()) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    for (auto c : cycle) {
      std::cout << c + 1 << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
