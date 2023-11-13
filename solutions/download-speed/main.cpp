#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <queue>
#include <vector>

template <class Iterator> class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {}

  Iterator begin() const { return begin_; }

  Iterator end() const { return end_; }

private:
  Iterator begin_, end_;
};

template <typename Iterator> class FilterIterator : public Iterator {
public:
  using Predicate = std::function<bool(const typename Iterator::value_type &)>;

  FilterIterator() = default;
  FilterIterator(Predicate predicate, Iterator base, Iterator end)
      : Iterator(base), end_(end), predicate_(predicate) {
    SatisfyPredicate();
  }

  FilterIterator &operator++() {
    Iterator::operator++();
    SatisfyPredicate();
    return *this;
  }

private:
  void SatisfyPredicate() {
    while (*this != end_ and !predicate_(**this)) {
      Iterator::operator++();
    }
  }

  Iterator end_;
  Predicate predicate_;
};

namespace traversal {

template <class Vertex, class Graph, class Visitor>
void BreadthFirstSearch(Vertex origin_vertex, const Graph &graph,
                        Visitor visitor) {
  visitor.DiscoverVertex(origin_vertex);

  std::vector<bool> discovered_vertices(graph.VertexCount());
  discovered_vertices[origin_vertex] = true;

  std::queue<Vertex> vertices_to_explore;
  vertices_to_explore.push(origin_vertex);

  while (!vertices_to_explore.empty()) {
    const auto vertex = vertices_to_explore.front();
    vertices_to_explore.pop();

    visitor.ExamineVertex(vertex);

    for (const auto &edge : graph.OutgoingEdges(vertex)) {
      visitor.ExamineEdge(edge);

      const auto adjacent_vertex = graph.EdgeTarget(edge);
      if (!discovered_vertices[adjacent_vertex]) {
        visitor.TreeEdge(edge);
        visitor.DiscoverVertex(adjacent_vertex);

        discovered_vertices[adjacent_vertex] = true;
        vertices_to_explore.push(adjacent_vertex);
      }
    }
  }
}

template <class Vertex, class Edge> class BreadthFirstSearchVisitor {
public:
  virtual ~BreadthFirstSearchVisitor() = default;
  virtual void DiscoverVertex(const Vertex & /*vertex*/) {}
  virtual void ExamineEdge(const Edge & /*edge*/) {}
  virtual void TreeEdge(const Edge & /*edge*/) {}
  virtual void ExamineVertex(const Vertex & /*vertex*/) {}
};

} // namespace traversal

class Graph {
public:
  struct Edge {
    Edge(int from, int to, int id) : from(from), to(to), id(id) {}

    int from, to;
    int id;
  };

  using AdjacencyList = std::vector<Edge>;
  using EdgeIterator = AdjacencyList::const_iterator;

  explicit Graph(size_t vertex_count) : adjacency_lists_(vertex_count) {}

  size_t VertexCount() const { return adjacency_lists_.size(); }

  void AddEdge(int from, int to, int id) {
    adjacency_lists_[from].emplace_back(from, to, id);
  }

  IteratorRange<EdgeIterator> OutgoingEdges(int from) const {
    return {adjacency_lists_[from].begin(), adjacency_lists_[from].end()};
  }

  int EdgeTarget(const Edge &edge) const { return edge.to; }

private:
  std::vector<AdjacencyList> adjacency_lists_;
};

class FilteredGraph {
public:
  using FilteredEdgeIterator = FilterIterator<Graph::EdgeIterator>;
  using Predicate = FilteredEdgeIterator::Predicate;

  FilteredGraph(const Graph &graph, Predicate predicate)
      : graph_(graph), predicate_(predicate) {}

  size_t VertexCount() const { return graph_.VertexCount(); }

  IteratorRange<FilteredEdgeIterator> OutgoingEdges(int from) const {
    auto range = graph_.OutgoingEdges(from);
    return {{predicate_, range.begin(), range.end()},
            {predicate_, range.end(), range.end()}};
  }

  int EdgeTarget(const Graph::Edge &edge) const {
    return graph_.EdgeTarget(edge);
  }

private:
  const Graph &graph_;
  Predicate predicate_;
};

class FlowNetwork {
public:
  friend class FlowNetworkBuilder;

  int Source() const { return source_; }

  int Sink() const { return sink_; }

  int VertexCount() const { return graph_.VertexCount(); }

  int EdgeFlow(int edge_id) const { return edges_properties_[edge_id].flow; }

  int EdgeCapacity(int edge_id) const {
    return edges_properties_[edge_id].capacity;
  }

  int EdgeResidualCapacity(int edge_id) const {
    return EdgeCapacity(edge_id) - EdgeFlow(edge_id);
  }

  FilteredGraph ResidualNetworkView() const {
    return FilteredGraph(graph_, [this](const Graph::Edge &edge) {
      return EdgeResidualCapacity(edge.id) > 0;
    });
  }

  void AddFlow(int edge_id, int flow) {
    edges_properties_[edge_id].flow += flow;
    edges_properties_[edge_id ^ 1].flow -= flow;
  }

private:
  struct EdgeProperties {
    EdgeProperties(int flow, int capacity) : flow(flow), capacity(capacity) {}

    int flow, capacity;
  };

  explicit FlowNetwork(int vertex_count) : graph_(vertex_count) {}

  Graph graph_;
  std::vector<EdgeProperties> edges_properties_;
  int source_, sink_;
};

class FlowNetworkBuilder {
public:
  explicit FlowNetworkBuilder(size_t vertex_count) : network_(vertex_count) {}

  void AddEdge(int from, int to, int capacity) {
    network_.graph_.AddEdge(from, to, network_.edges_properties_.size());
    network_.edges_properties_.emplace_back(0, capacity);
    network_.graph_.AddEdge(to, from, network_.edges_properties_.size());
    network_.edges_properties_.emplace_back(0, 0);
  }

  void SetSource(int source) { network_.source_ = source; }
  void SetSink(int sink) { network_.sink_ = sink; }

  FlowNetwork Build() const { return network_; }

private:
  FlowNetwork network_;
};

class AugmentingPathFinder
    : public traversal::BreadthFirstSearchVisitor<int, Graph::Edge> {
public:
  explicit AugmentingPathFinder(std::vector<std::optional<Graph::Edge>> *path)
      : path_(*path) {}

  void TreeEdge(const Graph::Edge &edge) override { path_[edge.to] = edge; }

private:
  std::vector<std::optional<Graph::Edge>> &path_;
};

int ComputeAugmentingPathMinCapacity(
    const FlowNetwork &network,
    const std::vector<std::optional<Graph::Edge>> &path) {
  if (!path[network.Sink()]) {
    return 0;
  }
  auto capacity = std::numeric_limits<int>::max();
  for (auto vertex = network.Sink(); vertex != network.Source();
       vertex = path[vertex]->from) {
    const auto edge_id = path[vertex]->id;
    capacity = std::min(capacity, network.EdgeResidualCapacity(edge_id));
  }
  return capacity;
}

int FindAugmentingPath(const FlowNetwork &network,
                       std::vector<std::optional<Graph::Edge>> *path) {
  path->assign(network.VertexCount(), std::nullopt);
  AugmentingPathFinder visitor(path);
  traversal::BreadthFirstSearch(network.Source(), network.ResidualNetworkView(),
                                visitor);
  return ComputeAugmentingPathMinCapacity(network, *path);
}

void PushFlow(FlowNetwork *network, int capacity,
              const std::vector<std::optional<Graph::Edge>> &path) {
  for (auto vertex = network->Sink(); vertex != network->Source();
       vertex = path[vertex]->from) {
    const auto edge_id = path[vertex]->id;
    network->AddFlow(edge_id, capacity);
  }
}

long long ComputeMaxFlow(FlowNetwork *network) {
  std::vector<std::optional<Graph::Edge>> path;
  long long max_flow = 0;
  while (auto capacity = FindAugmentingPath(*network, &path)) {
    PushFlow(network, capacity, path);
    max_flow += capacity;
  };
  return max_flow;
}

FlowNetwork ReadNetwork() {
  int vertex_count, edge_count;
  std::cin >> vertex_count >> edge_count;

  FlowNetworkBuilder builder(vertex_count);
  builder.SetSource(0);
  builder.SetSink(vertex_count - 1);
  while (edge_count--) {
    int from, to, capacity;
    std::cin >> from >> to >> capacity;

    builder.AddEdge(from - 1, to - 1, capacity);
  }

  return builder.Build();
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  auto network = ReadNetwork();

  std::cout << ComputeMaxFlow(&network) << "\n";

  return 0;
}
