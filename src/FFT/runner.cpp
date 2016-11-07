#include "./FFT_1D.hpp"
#include <iostream>

using std::cin;

int main() {
  int type = 0;
  int len = 0;
  while (cin >> len) {
    double tmp;
    vector<double> input;
    while (len--) {
      cin >> tmp;
      input.push_back(tmp);
    }
    cin >> type;
    if (type != 1) type = -1;

    FFT fft;
    FFT::print(fft.solve(input, type));
  }
}
