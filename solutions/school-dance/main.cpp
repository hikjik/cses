#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_set>
#include <vector>

template <class Vertex, class Graph, class Visitor>
void BreadthFirstSearch(Vertex source, const Graph &graph, Visitor visitor) {
  visitor.DiscoverVertex(source, graph);

  std::unordered_set<Vertex> visited{source};
  std::queue<Vertex> queue;
  queue.push(source);

  while (!queue.empty()) {
    const auto vertex = queue.front();
    queue.pop();

    visitor.ExamineVertex(vertex, graph);

    for (const auto &edge : OutgoingEdges(graph, vertex)) {
      visitor.ExamineEdge(edge, graph);

      const auto target = GetTarget(graph, edge);
      if (!visited.contains(target)) {
        visitor.TreeEdge(edge, graph);
        visitor.DiscoverVertex(target, graph);

        visited.insert(target);
        queue.push(target);
      }
    }
  }
}

template <class Graph, class Vertex, class Edge>
class BreadthFirstSearchVisitor {
public:
  virtual ~BreadthFirstSearchVisitor() = default;
  virtual void DiscoverVertex(Vertex, const Graph &) {}
  virtual void ExamineEdge(Edge, const Graph &) {}
  virtual void TreeEdge(Edge, const Graph &) {}
  virtual void ExamineVertex(Vertex, const Graph &) {}
};

class FlowGraph {
public:
  struct Edge {
    int from, to;
    int capacity, flow;
  };

  explicit FlowGraph(size_t vertex_count) : adjacency_lists_(vertex_count) {}

  void AddEdge(int from, int to, int capacity) {
    adjacency_lists_[from].push_back(edges_.size());
    edges_.push_back({from, to, capacity, 0});
    adjacency_lists_[to].push_back(edges_.size());
    edges_.push_back({to, from, 0, 0});
  }

  size_t GetVertexCount() const { return adjacency_lists_.size(); }

  const std::vector<int> &GetEdgesIds(int from) const {
    return adjacency_lists_[from];
  }

  const Edge &GetEdge(int id) const { return edges_[id]; }

  void AddFlow(int id, int flow) {
    edges_[id].flow += flow;
    edges_[id ^ 1].flow -= flow;
  }

private:
  std::vector<Edge> edges_;
  std::vector<std::vector<int>> adjacency_lists_;
};

std::vector<int> OutgoingEdges(const FlowGraph &graph, int vertex) {
  std::vector<int> edges_ids;
  for (int edge_id : graph.GetEdgesIds(vertex)) {
    if (graph.GetEdge(edge_id).capacity > graph.GetEdge(edge_id).flow) {
      edges_ids.push_back(edge_id);
    }
  }
  return edges_ids;
}

int GetTarget(const FlowGraph &graph, int edge_id) {
  return graph.GetEdge(edge_id).to;
}

struct Path {
  explicit Path(size_t vertex_count, int source, int sink)
      : incoming_edge_id(vertex_count), source(source), sink(sink) {}

  std::vector<int> incoming_edge_id;
  int source, sink;
};

class PathFinder : public BreadthFirstSearchVisitor<FlowGraph, int, int> {
public:
  explicit PathFinder(Path *path, std::vector<int> *capacity,
                      bool *is_sink_reachable)
      : path_(*path), capacity_(*capacity),
        is_sink_reachable_(*is_sink_reachable) {}

  void TreeEdge(int edge_id, const FlowGraph &graph) override {
    const auto &edge = graph.GetEdge(edge_id);
    capacity_[edge.to] =
        std::min(capacity_[edge.from], edge.capacity - edge.flow);
    path_.incoming_edge_id[edge.to] = edge_id;
  }

  void DiscoverVertex(int vertex, const FlowGraph &graph) override {
    if (vertex == path_.sink) {
      is_sink_reachable_ = true;
    }
  }

private:
  Path &path_;
  std::vector<int> &capacity_;
  bool &is_sink_reachable_;
};

void PushFlow(FlowGraph &graph, const Path &path, int flow) {
  auto vertex = path.sink;
  while (vertex != path.source) {
    const auto edge_id = path.incoming_edge_id[vertex];
    graph.AddFlow(edge_id, flow);
    vertex = graph.GetEdge(edge_id).from;
  }
}

void BuildMaxFlow(FlowGraph &graph, int source, int sink) {
  std::vector<int> min_capacity(graph.GetVertexCount(),
                                std::numeric_limits<int>::max());
  Path path(graph.GetVertexCount(), source, sink);
  auto is_sink_reachable = false;
  do {
    is_sink_reachable = false;
    PathFinder finder(&path, &min_capacity, &is_sink_reachable);
    BreadthFirstSearch(source, graph, finder);

    if (is_sink_reachable) {
      const auto flow = min_capacity[sink];
      PushFlow(graph, path, flow);
    }
  } while (is_sink_reachable);
}

long long ComputeMaxFlow(FlowGraph &graph, int source, int sink) {
  BuildMaxFlow(graph, source, sink);

  long long flow = 0;
  for (int edge_id : graph.GetEdgesIds(source)) {
    if (!(edge_id & 1)) {
      flow += graph.GetEdge(edge_id).flow;
    }
  }
  return flow;
}

std::vector<FlowGraph::Edge>
ComputeMaximumMatchings(int n, int m,
                        const std::vector<std::pair<int, int>> &pairs) {
  FlowGraph graph(n + m + 2);
  for (const auto &[u, v] : pairs) {
    graph.AddEdge(u, v + n, 1);
  }
  for (int u = 1; u <= n; ++u) {
    graph.AddEdge(0, u, 1);
  }
  for (int v = 1; v <= m; ++v) {
    graph.AddEdge(v + n, m + n + 1, 1);
  }

  const auto flow = ComputeMaxFlow(graph, 0, n + m + 1);

  std::vector<FlowGraph::Edge> edges;
  edges.reserve(flow);

  for (int i = 1; i <= n; ++i) {
    for (auto edge_id : graph.GetEdgesIds(i)) {
      const auto edge = graph.GetEdge(edge_id);
      if (!(edge_id & 1) && edge.flow) {
        edges.push_back(edge);
      }
    }
  }

  return edges;
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<std::pair<int, int>> pairs(k);
  for (auto &[from, to] : pairs) {
    std::cin >> from >> to;
  }

  const auto edges = ComputeMaximumMatchings(n, m, pairs);

  std::cout << edges.size() << "\n";
  for (const auto &edge : edges) {
    std::cout << edge.from << " " << edge.to - n << "\n";
  }

  return 0;
}
