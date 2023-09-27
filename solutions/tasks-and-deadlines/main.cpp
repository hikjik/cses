#include <algorithm>
#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  int n;
  std::cin >> n;

  long long reward = 0;
  std::vector<int> durations(n);
  for (auto &d : durations) {
    int r;
    std::cin >> d >> r;
    reward += r;
  }

  std::sort(durations.begin(), durations.end());

  auto sum = 0LL;
  for (auto d : durations) {
    sum += d;
    reward -= sum;
  }

  std::cout << reward << "\n";

  return 0;
}
