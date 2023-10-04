#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
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

  Graph transpose_graph(n);
  for (int u = 0; u < n; ++u) {
    for (auto v : graph[u]) {
      transpose_graph[v].push_back(u);
    }
  }
  return transpose_graph;
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

Graph BuildCondensationGraph(const Graph &graph,
                             const Partition<int> &partition) {
  Graph condensation_graph(partition.GroupsNumber());
  for (int group_id = 0; group_id < partition.GroupsNumber(); ++group_id) {
    for (auto u : partition.ElementsFromGroup(group_id)) {
      for (auto v : graph[u]) {
        if (group_id != partition.GroupId(v)) {
          condensation_graph[group_id].push_back(partition.GroupId(v));
        }
      }
    }
  }
  return condensation_graph;
}

std::vector<int> GetVerticesInTopologicalOrder(const Graph &graph) {
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

  std::vector<int> order;
  while (!queue.empty()) {
    const auto u = queue.front();
    queue.pop();

    order.push_back(u);
    for (auto v : graph[u]) {
      if (!--in_degree[v]) {
        queue.push(v);
      }
    }
  }

  std::reverse(order.begin(), order.end());
  return order;
}

std::vector<char>
CalculateSelectionOfToppings(int m, const Graph &graph,
                             const Partition<int> &partition) {
  const auto condensation_graph = BuildCondensationGraph(graph, partition);
  const auto groups_order = GetVerticesInTopologicalOrder(condensation_graph);

  std::vector<char> toppings(m);
  std::vector<bool> visited(m);
  for (auto group_id : groups_order) {
    for (auto u : partition.ElementsFromGroup(group_id)) {
      const auto i = u / 2;
      if (!visited[i]) {
        visited[i] = true;
        toppings[i] = u & 1 ? '-' : '+';
      }
    }
  }

  return toppings;
}

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(2 * m);
  for (int i = 0; i < n; ++i) {
    int a, b;
    char s, t;
    std::cin >> s >> a >> t >> b;
    --a, --b;

    graph[2 * a + (s == '+')].push_back(2 * b + (t == '-'));
    graph[2 * b + (t == '+')].push_back(2 * a + (s == '-'));
  }

  const auto partition = FindStronglyConnectedComponent(graph);

  for (int i = 0; i < m; ++i) {
    if (partition.GroupId(2 * i) == partition.GroupId(2 * i + 1)) {
      std::cout << "IMPOSSIBLE\n";
      return 0;
    }
  }

  for (auto a : CalculateSelectionOfToppings(m, graph, partition)) {
    std::cout << a << " ";
  }
  std::cout << "\n";

  return 0;
}
