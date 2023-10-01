#include <iostream>
#include <queue>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

using WeightedGraph = std::vector<std::vector<std::pair<int, int>>>;

std::vector<long long> KShortestPaths(int source, int target, int k,
                                      const WeightedGraph &graph) {
  const int n = graph.size();

  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>, std::greater<>>
      min_heap;
  min_heap.push({0, source});

  std::vector<int> visited(n);

  std::vector<long long> distances;
  while (!min_heap.empty()) {
    const auto [distance, u] = min_heap.top();
    min_heap.pop();

    if (u == target) {
      distances.push_back(distance);
      if (distances.size() == k * 1LL) {
        break;
      }
    }

    if (++visited[u] > k) {
      continue;
    }

    for (const auto &[v, w] : graph[u]) {
      min_heap.push({distance + w, v});
    }
  }

  return distances;
}

int main() {
  fast_io();

  int n, m, k;
  std::cin >> n >> m >> k;

  WeightedGraph graph(n);
  while (m--) {
    int a, b, w;
    std::cin >> a >> b >> w;
    --a, --b;

    graph[a].push_back({b, w});
  }

  for (auto distance : KShortestPaths(0, n - 1, k, graph)) {
    std::cout << distance << " ";
  }
  std::cout << "\n";

  return 0;
}
