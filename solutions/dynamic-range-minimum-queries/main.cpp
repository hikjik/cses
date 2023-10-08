#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

template <typename Iterator, typename ValueType, typename BinaryOp>
class SegmentTree {
public:
  SegmentTree(Iterator first, Iterator last, ValueType init, BinaryOp op)
      : size_(std::distance(first, last)), data_(2 * size_), op_(op),
        init_(init) {
    std::copy(first, last, data_.begin() + size_);
    for (int i = size_ - 1; i > 0; --i) {
      data_[i] = op_(data_[i << 1], data_[i << 1 | 1]);
    }
  }

  void Modify(size_t idx, ValueType value) {
    for (data_[idx += size_] = value; idx > 1; idx >>= 1) {
      data_[idx >> 1] = op_(data_[idx], data_[idx ^ 1]);
    }
  }

  ValueType RangeQuery(size_t left, size_t right) {
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
  size_t size_;
  std::vector<ValueType> data_;
  BinaryOp op_;
  ValueType init_;
};

struct Min {
  int operator()(int lhs, int rhs) { return std::min(lhs, rhs); }
};

int main() {
  FastIO();

  int n, q;
  std::cin >> n >> q;

  std::vector<int> nums(n);
  for (auto &a : nums) {
    std::cin >> a;
  }

  SegmentTree tree(nums.begin(), nums.end(), INT_MAX, Min());

  while (q--) {
    int type;
    std::cin >> type;

    if (type == 1) {
      int idx, value;
      std::cin >> idx >> value;

      tree.Modify(idx - 1, value);
    } else if (type == 2) {
      int left, right;
      std::cin >> left >> right;

      std::cout << tree.RangeQuery(left - 1, right - 1) << "\n";
    } else {
      throw;
    }
  }

  return 0;
}
