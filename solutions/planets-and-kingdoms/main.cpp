#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

using Graph = std::vector<std::vector<int>>;

template <typename T> class Partition {
public:
  template <typename U> friend class PartitionBuilder;

  int GroupsNumber() const { return groups_.size(); }

  int GroupId(const T &element) const { return group_id_.at(element); }

  const std::vector<T> &ElementsFromGroup(int group_id) const {
    return groups_[group_id];
  }

private:
  std::unordered_map<T, int> group_id_;
  std::vector<std::vector<T>> groups_;
};

template <typename T> class PartitionBuilder {
public:
  int CreateNewGroup() {
    partition_.groups_.emplace_back();
    return partition_.GroupsNumber() - 1;
  }

  void AddElementToGroup(int group_id, const T &element) {
    partition_.groups_[group_id].push_back(element);
    partition_.group_id_[element] = group_id;
  }

  Partition<T> Build() { return partition_; }

private:
  Partition<T> partition_;
};

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
  explicit ComponentBuilder(PartitionBuilder<int> *partition_builder)
      : partition_builder_(*partition_builder) {}

  void StartVertex(int u) override {
    current_component_id_ = partition_builder_.CreateNewGroup();
  }

  void DiscoverVertex(int u) override {
    partition_builder_.AddElementToGroup(current_component_id_, u);
  }

private:
  PartitionBuilder<int> &partition_builder_;
  int current_component_id_;
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

Partition<int> FindStronglyConnectedComponent(const Graph &graph) {
  const auto vertices_order = GetVerticesInReversedPostOrder(graph);
  const auto transpose_graph = BuildTransposeGraph(graph);
  PartitionBuilder<int> builder;
  ComponentBuilder component_builder(&builder);
  TraverseGraphInDfsOrder(transpose_graph, component_builder, vertices_order);
  return builder.Build();
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

  const auto partition = FindStronglyConnectedComponent(graph);

  std::cout << partition.GroupsNumber() << "\n";
  for (int u = 0; u < n; ++u) {
    std::cout << partition.GroupId(u) + 1 << " ";
  }
  std::cout << "\n";

  return 0;
}
