#include <iostream>
#include <map>
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

  std::vector<std::tuple<int, int, int>> customers;
  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;

    customers.push_back({a, i, b});
  }

  std::sort(customers.begin(), customers.end());

  std::multimap<int, int> settled;
  int rooms_count = 0;
  std::vector<int> rooms(n);
  for (const auto &[a, i, b] : customers) {
    if (settled.empty() || a <= settled.begin()->first) {
      rooms[i] = ++rooms_count;
    } else {
      rooms[i] = settled.begin()->second;
      settled.erase(settled.begin());
    }

    settled.insert({b, rooms[i]});
  }

  std::cout << rooms_count << "\n";
  for (auto a : rooms) {
    std::cout << a << " ";
  }
  std::cout << "\n";

  return 0;
}
