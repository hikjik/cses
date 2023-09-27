#include <iostream>
#include <string>

int GetDigitAtPostion(long long k) {
  int length = 1;
  long long pow10 = 1;
  while (9 * length * pow10 < k) {
    k -= 9 * length * pow10;
    ++length;
    pow10 *= 10;
  }

  const auto q = (k - 1) / length, r = (k - 1) % length;
  return std::to_string(pow10 + q)[r] - '0';
}

int main() {
  int n;
  std::cin >> n;

  while (n--) {
    long long k;
    std::cin >> k;

    std::cout << GetDigitAtPostion(k) << "\n";
  }

  return 0;
}
