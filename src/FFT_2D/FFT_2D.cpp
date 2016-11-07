#include "./FFT_2D.hpp"
#define _DEBUG_

using std::vector;
using std::string;
using std::complex;
using std::cout;
using std::endl;
using std::cin;

const double PI = 2 * asin(1);

void FFT_2D::print(const vector<vector<complex<double> > > &C) {
  for (size_t i = 0; i < C.size(); ++i) {
    for (size_t j = 0; j < C[0].size(); ++j) {
      cout << C[i][j] << " ";
    }
    cout << endl;
  }
  cout << "\n\n";
}

void FFT_2D::padding() {
  int lenX = input.size();
  int lenY = input[0].size();

  padLenX = 1;
  while (padLenX < lenX) {
    padLenX <<= 1;
  }

  padLenY = 1;
  while (padLenY < lenY) {
    padLenY <<= 1;
  }

  // initialization
  A.resize(padLenX);
  for (int i = 0; i < padLenX; ++i) {
    for (int j = 0; j < padLenY; ++j) {
      A[i].resize(padLenY);
      if (i < lenX && j < lenY) {
        A[i][j] = complex<double>(input[i][j], 0);
      } else {
        A[i][j] = complex<double>(0, 0);
      }
    }
  }
}

// 位逆序置换 雷德算法
// 倒位序是在最高位加1，然后向低位进位
void FFT_2D::rader(int idx, bool isRow) {
  // i 顺序
  // j 逆序
  int len = isRow ? A[0].size() : A.size();

  int k, j = len >> 1, i = 1;
  for (; i < len - 1; ++i) {
    if (i < j) {
      if (isRow) {
        std::swap(A[idx][i], A[idx][j]);
      } else {
        std::swap(A[i][idx], A[j][idx]);
      }
    }

    k = len >> 1;

    while (j >= k) { // 当前最高位为 1
      j -= k; // 将当前最高位置 0
      k >>= 1; // 看下一位
    }

    j += k; // 当前最高位为 0，进位结束
  }
}

void FFT_2D::helper(int idx, bool isRow) {
  rader(idx, isRow);

  int padLen = isRow ? padLenY : padLenX;

  for (int T = 2; T <= padLen; T <<= 1) {
    complex<double> Wn(cos(op * 2 * PI / T), sin(op * 2 * PI / T));

    for (int i = 0; i < padLen; i += T) {
      complex<double> W(1, 0);

      for (int j = i; j < i + T / 2; ++j) {
        if (isRow) {
          complex<double> u = A[idx][j];
          complex<double> v = W * A[idx][j + T / 2];

          A[idx][j] = u + v;
          A[idx][j + T / 2] = u - v;
        } else {
          complex<double> u = A[j][idx];
          complex<double> v = W * A[j + T / 2][idx];

          A[j][idx] = u + v;
          A[j + T / 2][idx] = u - v;
        }
        W *= Wn;
      }
    }
  }

  if (op == 1) {
    for (int i = 0; i < padLen; ++i) {
      if (isRow) {
        A[idx][i] /= padLen;
      } else {
        A[i][idx] /= padLen;
      }
    }
  }
}

// -1 DFT
// 1 IDFT
vector<vector<complex<double> > > FFT_2D::solve(vector<vector<double> > input, int op) {
  this->input = input;
  this->op = op;
  padding();

#ifdef _DEBUG_
  cout << "padding size " << padLenX << " " << padLenY << endl;
#endif

  for (int i = 0; i < padLenX; ++i) {
    helper(i, true);
    print(A);
  }

#ifdef _DEBUG_
  cout << "column....\n";
#endif

  for (int j = 0; j < padLenY; ++j) {
    helper(j, false);
    print(A);
  }
  return A;
}
