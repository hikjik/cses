#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

class DisjointSets {
public:
  explicit DisjointSets(size_t size) : sets_(size), count_(size) {
    for (size_t i = 0; i < sets_.size(); ++i) {
      sets_[i].parent = i;
    }
  }

  size_t Count() { return count_; }

  size_t Parent(size_t i) {
    if (sets_[i].parent != i) {
      sets_[i].parent = Parent(sets_[i].parent);
    }
    return sets_[i].parent;
  }

  bool Merge(size_t u, size_t v) {
    size_t i = Parent(u), j = Parent(v);
    if (i == j) {
      return false;
    }
    count_--;

    if (sets_[i].rank > sets_[j].rank) {
      sets_[j].parent = i;
    } else {
      sets_[i].parent = j;
      if (sets_[i].rank == sets_[j].rank) {
        ++sets_[j].rank;
      }
    }
    return true;
  }

private:
  struct DisjointSetsElement {
    DisjointSetsElement() : parent(0), rank(0) {}

    size_t parent;
    size_t rank;
  };

  std::vector<DisjointSetsElement> sets_;
  size_t count_;
};

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::tuple<int, int, int>> edges(m);
  for (auto &[c, a, b] : edges) {
    std::cin >> a >> b >> c;
    --a, --b;
  }
  std::sort(edges.begin(), edges.end());

  long long cost = 0;
  DisjointSets sets(n);
  for (const auto &[c, a, b] : edges) {
    if (sets.Merge(a, b)) {
      cost += c;
    }
  }

  if (sets.Count() > 1) {
    std::cout << "IMPOSSIBLE\n";
  } else {
    std::cout << cost << "\n";
  }

  return 0;
}
