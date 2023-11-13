#include <algorithm>
#include <iostream>
#include <limits>
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
  virtual void DiscoverVertex(const Vertex &) {}
  virtual void ExamineEdge(const Edge &) {}
  virtual void TreeEdge(const Edge &) {}
  virtual void ExamineVertex(const Vertex &) {}
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

  IteratorRange<Graph::EdgeIterator> OutgoingEdges(int vertex,
                                                   int offset) const {
    auto range = graph_.OutgoingEdges(vertex);
    return {range.begin() + offset, range.end()};
  }

  int Flow(int edge_id) const { return edges_properties_[edge_id].flow; }

  int Capacity(int edge_id) const {
    return edges_properties_[edge_id].capacity;
  }

  int ResidualCapacity(int edge_id) const {
    return Capacity(edge_id) - Flow(edge_id);
  }

  FilteredGraph ResidualNetworkView() const {
    return FilteredGraph(graph_, [this](const Graph::Edge &edge) {
      return ResidualCapacity(edge.id) > 0;
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

class LevelGraphBuilder
    : public traversal::BreadthFirstSearchVisitor<int, Graph::Edge> {
public:
  explicit LevelGraphBuilder(std::vector<int> *levels) : levels_(*levels) {}

  void TreeEdge(const Graph::Edge &edge) override {
    levels_[edge.to] = levels_[edge.from] + 1;
  }

private:
  std::vector<int> &levels_;
};

class MaxFlowCalculator {
public:
  MaxFlowCalculator(const MaxFlowCalculator &) = delete;
  MaxFlowCalculator(MaxFlowCalculator &&) = delete;
  MaxFlowCalculator &operator=(const MaxFlowCalculator &) = delete;
  MaxFlowCalculator &operator=(MaxFlowCalculator &&) = delete;

  static MaxFlowCalculator &GetInstance() {
    static MaxFlowCalculator instance;
    return instance;
  }

  long long ComputeMaxFlow(FlowNetwork *network) {
    network_ = network;
    long long max_flow = 0;
    while (BuildLevelGraph()) {
      max_flow += FindBlockingFlow();
    };
    return max_flow;
  }

private:
  static constexpr int kInfFlow = std::numeric_limits<int>::max();

  MaxFlowCalculator() : network_(nullptr) {}

  bool BuildLevelGraph() {
    levels_.assign(network_->VertexCount(), -1);
    levels_[network_->Source()] = 0;
    LevelGraphBuilder visitor(&levels_);
    traversal::BreadthFirstSearch(network_->Source(),
                                  network_->ResidualNetworkView(), visitor);
    return levels_[network_->Sink()] != -1;
  }

  long long FindBlockingFlow() {
    long long total = 0;
    offsets_.assign(network_->VertexCount(), 0);
    while (auto flow = PushFlow(kInfFlow, network_->Source())) {
      total += flow;
    }
    return total;
  }

  int PushFlow(int flow, int vertex) {
    if (vertex == network_->Sink()) {
      return flow;
    }
    for (const auto &edge : network_->OutgoingEdges(vertex, offsets_[vertex])) {
      if (levels_[edge.from] + 1 == levels_[edge.to] &&
          network_->ResidualCapacity(edge.id) > 0) {
        const auto path_flow = PushFlow(
            std::min(flow, network_->ResidualCapacity(edge.id)), edge.to);
        if (path_flow) {
          network_->AddFlow(edge.id, path_flow);
          return path_flow;
        }
      }
      ++offsets_[vertex];
    }
    return 0;
  }

  FlowNetwork *network_;
  std::vector<int> levels_;
  std::vector<int> offsets_;
};

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
  auto &calculator = MaxFlowCalculator::GetInstance();

  std::cout << calculator.ComputeMaxFlow(&network) << "\n";

  return 0;
}
