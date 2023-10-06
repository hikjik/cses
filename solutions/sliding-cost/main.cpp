#include <iostream>
#include <set>
#include <vector>

class CostSet {
public:
  long long Cost() {
    const auto median = *left.rbegin();
    return median * left.size() - left_sum + right_sum - right.size() * median;
  }

  void Insert(int value) {
    if (!left.empty() && value > *left.rbegin()) {
      right.insert(value);
      right_sum += value;
    } else {
      left.insert(value);
      left_sum += value;
    }

    Rebalance();
  }

  void Erase(int value) {
    if (auto it = left.find(value); it != left.end()) {
      left_sum -= *it;
      left.erase(it);
    } else if (auto it = right.find(value); it != right.end()) {
      right_sum -= *it;
      right.erase(it);
    } else {
      throw;
    }

    Rebalance();
  }

private:
  void Rebalance() {
    if (right.size() > left.size()) {
      const auto value = *right.begin();
      right_sum -= value;
      left_sum += value;
      right.erase(right.begin());
      left.insert(value);
    } else if (right.size() + 1 < left.size()) {
      const auto value = *left.rbegin();
      right_sum += value;
      left_sum -= value;
      left.erase(std::prev(left.end()));
      right.insert(value);
    }
  }

  std::multiset<int> left;
  std::multiset<int> right;
  long long left_sum = 0;
  long long right_sum = 0;
};

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, k;
  std::cin >> n >> k;

  std::vector<int> arr(n);
  for (auto &a : arr) {
    std::cin >> a;
  }

  CostSet cost_set;
  for (int i = 0; i < k - 1; ++i) {
    cost_set.Insert(arr[i]);
  }

  for (int i = k - 1; i < n; ++i) {
    cost_set.Insert(arr[i]);
    std::cout << cost_set.Cost() << " ";
    cost_set.Erase(arr[i - k + 1]);
  }
  std::cout << "\n";

  return 0;
}
