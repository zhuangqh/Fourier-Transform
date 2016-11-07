#include "./FFT_2D.hpp"
#include <iostream>

using std::cin;
using std::cout;

int main() {
  int type = 0;
  int lenX = 0;
  int lenY = 0;

  while (cin >> lenX >> lenY && lenX > 0 && lenY > 0) {
    vector<vector<double> > input;
    input.resize(lenX);

    for (int i = 0; i < lenX; ++i) {
      input[i].resize(lenY);
      for (int j = 0; j < lenY; ++j) {
        cin >> input[i][j];
      }
    }

    cin >> type;
    if (type != 1) type = -1;
    FFT_2D fft;

    FFT_2D::print(fft.solve(input, type));
  }
}
