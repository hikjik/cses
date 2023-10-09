#include <algorithm>
#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

template <typename ValueType, typename BinaryOp> class SegmentTree {
public:
  SegmentTree(size_t size, BinaryOp op, ValueType init)
      : size_(size), data_(2 * size_), op_(op), init_(init) {}

  template <typename Iterator>
  SegmentTree(Iterator first, Iterator last, BinaryOp op, ValueType init)
      : SegmentTree(std::distance(first, last), op, init) {
    std::copy(first, last, data_.begin() + size_);
    for (int i = size_ - 1; i > 0; --i) {
      data_[i] = op_(data_[i << 1], data_[i << 1 | 1]);
    }
  }

  size_t Size() const { return size_; }

  void Set(size_t idx, ValueType value) {
    data_[idx += size_] = value;
    Update(idx);
  }

  void Add(size_t idx, ValueType delta) {
    data_[idx += size_] += delta;
    Update(idx);
  }

  // process a range query on interval [left, right]
  ValueType RangeQuery(size_t left, size_t right) const {
    auto res = init_;
    for (left += size_, right += size_ + 1; left < right;
         left >>= 1, right >>= 1) {
      if (left & 1) {
        res = op_(res, data_[left++]);
      }
      if (right & 1) {
        res = op_(res, data_[--right]);
      }
    }
    return res;
  }

private:
  void Update(size_t idx) {
    for (int i = idx; i > 1; i >>= 1) {
      data_[i >> 1] = op_(data_[i], data_[i ^ 1]);
    }
  }

  size_t size_;
  std::vector<ValueType> data_;
  BinaryOp op_;
  ValueType init_;
};

template <typename ValueType> struct Max {
  int operator()(ValueType lhs, ValueType rhs) const {
    return std::max(lhs, rhs);
  }
};

template <typename ValueType, typename BinaryOp>
size_t BinarySearch(const SegmentTree<ValueType, BinaryOp> &tree,
                    ValueType value) {
  int left = 0, right = tree.Size();
  while (left < right) {
    const auto middle = left + (right - left) / 2;
    tree.RangeQuery(0, middle) < value ? left = middle + 1 : right = middle;
  }
  return left;
}

int main() {
  FastIO();

  int n, q;
  std::cin >> n >> q;

  std::vector<int> nums(n);
  for (auto &a : nums) {
    std::cin >> a;
  }

  SegmentTree tree(nums.begin(), nums.end(), Max<int>(), 0);

  while (q--) {
    int r;
    std::cin >> r;

    const auto idx = BinarySearch(tree, r);
    if (idx < tree.Size()) {
      std::cout << idx + 1 << " ";
      tree.Add(idx, -r);
    } else {
      std::cout << 0 << " ";
    }
  }
  std::cout << "\n";

  return 0;
}
