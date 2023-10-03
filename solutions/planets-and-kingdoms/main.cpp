#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

using Graph = std::vector<std::vector<int>>;

class DepthFirstSearchVisitor {
public:
  virtual ~DepthFirstSearchVisitor() = default;
  virtual void StartVertex(int u) {}
  virtual void DiscoverVertex(int u) {}
  virtual void FinishVertex(int u) {}
};

class VertexInPostOrderBuilder : public DepthFirstSearchVisitor {
public:
  explicit VertexInPostOrderBuilder(std::vector<int> *order) : order_(*order) {}

  void FinishVertex(int u) override { order_.push_back(u); }

private:
  std::vector<int> &order_;
};

class ComponentBuilder : public DepthFirstSearchVisitor {
public:
  explicit ComponentBuilder(std::vector<int> *components, int *component_id)
      : components_(*components), current_component_id_(*component_id) {}

  void StartVertex(int u) override { ++current_component_id_; }

  void DiscoverVertex(int u) override {
    components_[u] = current_component_id_;
  }

private:
  std::vector<int> &components_;
  int &current_component_id_;
};

template <typename Visitor>
void ExploreVertex(int u, const Graph &graph, Visitor visitor,
                   std::vector<bool> *visited) {
  (*visited)[u] = true;
  visitor.DiscoverVertex(u);

  for (auto v : graph[u]) {
    if (!(*visited)[v]) {
      ExploreVertex(v, graph, visitor, visited);
    }
  }

  visitor.FinishVertex(u);
}

template <typename Visitor>
void TraverseGraphInDfsOrder(const Graph &graph, Visitor visitor,
                             const std::vector<int> &vertices_order) {
  std::vector<bool> visited(graph.size());
  for (auto u : vertices_order) {
    if (!visited[u]) {
      visitor.StartVertex(u);
      ExploreVertex(u, graph, visitor, &visited);
    }
  }
}

template <typename Visitor>
void TraverseGraphInDfsOrder(const Graph &graph, Visitor visitor) {
  std::vector<int> vertices_order(graph.size());
  std::iota(vertices_order.begin(), vertices_order.end(), 0);
  TraverseGraphInDfsOrder(graph, visitor, vertices_order);
}

Graph BuildTransposeGraph(const Graph &graph) {
  const int n = graph.size();

  Graph reverse_graph(n);
  for (int u = 0; u < n; ++u) {
    for (auto v : graph[u]) {
      reverse_graph[v].push_back(u);
    }
  }
  return reverse_graph;
}

std::vector<int> GetVerticesInReversedPostOrder(const Graph &graph) {
  std::vector<int> order;
  VertexInPostOrderBuilder post_order_builder(&order);
  TraverseGraphInDfsOrder(graph, post_order_builder);
  std::reverse(order.begin(), order.end());
  return order;
}

std::pair<int, std::vector<int>>
FindStronglyConnectedComponent(const Graph &graph) {
  const auto vertices_order = GetVerticesInReversedPostOrder(graph);
  const auto transpose_graph = BuildTransposeGraph(graph);
  std::vector<int> components(graph.size());
  int components_count = 0;
  ComponentBuilder component_builder(&components, &components_count);
  TraverseGraphInDfsOrder(transpose_graph, component_builder, vertices_order);
  return {components_count, components};
}

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(n);
  while (m--) {
    int a, b;
    std::cin >> a >> b;

    graph[a - 1].push_back(b - 1);
  }

  const auto [count, components] = FindStronglyConnectedComponent(graph);

  std::cout << count << "\n";
  for (auto a : components) {
    std::cout << a << " ";
  }
  std::cout << "\n";

  return 0;
}
