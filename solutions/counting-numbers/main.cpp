#include <cstring>
#include <iostream>
#include <string>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

long long DP[20][10][2][2];

long long CountNumbers(const std::string &number, size_t n, int previous_digit,
                       int leading_zeros, int tight) {
  if (n == 0) {
    return 1;
  }

  long long &total = DP[n][previous_digit][leading_zeros][tight];

  if (previous_digit != -1 && total != -1) {
    return total;
  }

  int lower = 0;
  int upper = tight ? number[number.size() - n] - '0' : 9;

  total = 0;
  for (int digit = lower; digit <= upper; ++digit) {
    if (digit == previous_digit && !leading_zeros) {
      continue;
    }
    total += CountNumbers(number, n - 1, digit, leading_zeros && !digit,
                          tight && digit == upper);
  }
  return total;
}

long long CountNumbers(long long number) {
  std::memset(DP, -1, sizeof(DP));
  const std::string number_str = std::to_string(number);
  return CountNumbers(number_str, number_str.size(), -1, 1, 1);
}

int main() {
  fast_io();

  long long a, b;
  std::cin >> a >> b;

  std::cout << CountNumbers(b) - CountNumbers(a - 1) << "\n";

  return 0;
}
