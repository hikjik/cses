#include <bit>
#include <iostream>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

unsigned long long CountBits(unsigned long long n) {
  if (n == 0) {
    return 0;
  }
  const auto m = std::bit_floor(n);
  if (std::has_single_bit(n + 1)) {
    return n - m + 1 + 2 * CountBits(m - 1);
  }
  return n - m + 1 + CountBits(n - m) + CountBits(m - 1);
}

int main() {
  FastIO();

  unsigned long long n;
  std::cin >> n;
  std::cout << CountBits(n) << "\n";

  return 0;
}
