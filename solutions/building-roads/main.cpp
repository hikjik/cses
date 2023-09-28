#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

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

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;

  DisjointSets sets(n + 1);
  while (m--) {
    int a, b;
    std::cin >> a >> b;

    sets.Merge(a, b);
  }

  std::vector<std::pair<int, int>> required_roads;
  for (int i = 2; i <= n; ++i) {
    if (sets.Merge(i - 1, i)) {
      required_roads.push_back({i - 1, i});
    }
  }

  std::cout << required_roads.size() << "\n";
  for (const auto &[a, b] : required_roads) {
    std::cout << a << " " << b << "\n";
  }

  return 0;
}
