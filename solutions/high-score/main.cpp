#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using Graph = std::vector<std::vector<int>>;
using WeightedEdge = std::tuple<int, int, int>;

void DepthFirstSearch(int u, const Graph &graph, std::vector<bool> *visited) {
  (*visited)[u] = true;
  for (auto v : graph[u]) {
    if (!(*visited)[v]) {
      DepthFirstSearch(v, graph, visited);
    }
  }
}

std::vector<bool> GetReachableVertexes(int source, const Graph &graph) {
  std::vector<bool> visited(graph.size());
  DepthFirstSearch(source, graph, &visited);
  return visited;
}

// Bellman–Ford algorithm
std::vector<long long>
ComputeDistances(int vertex_count, int source,
                 const std::vector<WeightedEdge> &edges) {
  static const long long kInf = 0x3f3f3f3f3f3f3f3f;

  std::vector<long long> distances(vertex_count, kInf);
  distances[source] = 0;

  while (--vertex_count) {
    for (const auto &[u, v, w] : edges) {
      distances[v] = std::min(distances[v], distances[u] + w);
    }
  }

  return distances;
}

long long GetHighScore(int source, int target, int vertex_count,
                       const std::vector<WeightedEdge> &edges) {
  Graph graph(vertex_count), reversed_graph(vertex_count);
  for (const auto &[u, v, _] : edges) {
    graph[u].push_back(v);
    reversed_graph[v].push_back(u);
  }

  const auto source_successors = GetReachableVertexes(source, graph);
  const auto target_predecessors = GetReachableVertexes(target, reversed_graph);

  auto distances = ComputeDistances(vertex_count, source, edges);
  for (const auto &[u, v, w] : edges) {
    if (distances[v] > distances[u] + w) {
      if (source_successors[v] && target_predecessors[v]) {
        return -1;
      }
    }
  }

  return -distances.back();
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m;
  std::cin >> n >> m;

  const int source = 0, target = n - 1;
  std::vector<WeightedEdge> edges;
  while (m--) {
    int a, b, w;
    std::cin >> a >> b >> w;

    edges.emplace_back(a - 1, b - 1, -w);
  }

  std::cout << GetHighScore(source, target, n, edges) << "\n";

  return 0;
}
