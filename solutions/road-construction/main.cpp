#include <iostream>
#include <vector>

class DisjointSets {
public:
  explicit DisjointSets(size_t size) : sets_(size), count_(size) {
    for (size_t i = 0; i < sets_.size(); ++i) {
      sets_[i].parent = i;
    }
  }

  size_t CountComponents() { return count_; }

  size_t Parent(size_t i) {
    if (sets_[i].parent != i) {
      sets_[i].parent = Parent(sets_[i].parent);
    }
    return sets_[i].parent;
  }

  size_t ComponentSize(size_t i) { return sets_[Parent(i)].size; }

  bool Merge(size_t u, size_t v) {
    size_t i = Parent(u), j = Parent(v);
    if (i == j) {
      return false;
    }
    --count_;

    if (sets_[i].rank > sets_[j].rank) {
      sets_[j].parent = i;
      sets_[i].size += sets_[j].size;
    } else {
      sets_[i].parent = j;
      sets_[j].size += sets_[i].size;
      if (sets_[i].rank == sets_[j].rank) {
        ++sets_[j].rank;
      }
    }
    return true;
  }

private:
  struct DisjointSetsElement {
    DisjointSetsElement() : parent(0), rank(0), size(1) {}

    size_t parent;
    size_t rank;
    size_t size;
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

  DisjointSets sets(n);

  size_t max_size = 1;
  while (m--) {
    int a, b;
    std::cin >> a >> b;
    --a, --b;

    if (sets.Merge(a, b)) {
      max_size = std::max(max_size, sets.ComponentSize(a));
    }

    std::cout << sets.CountComponents() << " " << max_size << "\n";
  }

  return 0;
}
