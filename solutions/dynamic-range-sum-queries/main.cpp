#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

class BinaryIndexedTree {
public:
  explicit BinaryIndexedTree(const std::vector<int> &nums)
      : tree_(nums.size() + 1) {
    for (size_t idx = 1; idx < tree_.size(); ++idx) {
      tree_[idx] += nums[idx - 1];
      const auto p = idx + RSB(idx);
      if (p < tree_.size()) {
        tree_[p] += tree_[idx];
      }
    }
  }

  void Set(size_t idx, int value) {
    const auto delta = value - GetRangeSum(idx, idx);
    Add(idx, delta);
  }

  long long GetRangeSum(size_t left, size_t right) {
    return GetPrefixSum(right) - GetPrefixSum(left - 1);
  }

  void Add(size_t idx, int delta) {
    while (idx < tree_.size()) {
      tree_[idx] += delta;
      idx += RSB(idx);
    }
  }

  long long GetPrefixSum(size_t idx) {
    long long sum = 0;
    while (idx > 0) {
      sum += tree_[idx];
      idx -= RSB(idx);
    }
    return sum;
  }

private:
  size_t RSB(size_t idx) { return -idx & idx; }

  std::vector<long long> tree_;
};

int main() {
  FastIO();

  int n, q;
  std::cin >> n >> q;

  std::vector<int> nums(n);
  for (auto &a : nums) {
    std::cin >> a;
  }

  BinaryIndexedTree tree(nums);

  while (q--) {
    int type;
    std::cin >> type;

    if (type == 1) {
      int idx, value;
      std::cin >> idx >> value;

      tree.Set(idx, value);
    } else if (type == 2) {
      int left, right;
      std::cin >> left >> right;

      std::cout << tree.GetRangeSum(left, right) << "\n";
    } else {
      throw;
    }
  }

  return 0;
}
