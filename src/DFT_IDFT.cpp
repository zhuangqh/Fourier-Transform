#include <iostream>
#include <string>
#include <complex>
#include <vector>
#include <cmath>

using std::vector;
using std::string;
using std::complex;
using std::cout;
using std::endl;
using std::cin;

const double PI = 2 * asin(1);

void print(const vector<complex<double> > &c) {
  for (size_t i = 0; i < c.size(); ++i) {
    cout << c[i] << endl;
  }
}

void padding(vector<double> &input, int &padLen, vector<complex<double> > &A) {
  int len = input.size();

  padLen = 1;
  while (padLen < len) {
    padLen <<= 1;
  }

  // 零补位
  input.resize(padLen, 0);

  // initialization
  A.reserve(padLen);
  for (int i = 0; i < padLen; ++i) {
    if (i < len) {
      A.push_back(complex<double>(input[i], 0));
    } else {
      A.push_back(complex<double>());
    }
  }
}

// 位逆序置换 雷德算法
// 倒位序是在最高位加1，然后向低位进位
void rader(vector<complex<double> > &C) {
  // i 顺序
  // j 逆序
  int len = C.size();
  int k, j = len >> 1, i = 1;
  for (; i < len - 1; ++i) {
    if (i < j) {
      std::swap(C[i], C[j]);
    }

    k = len >> 1;

    while (j >= k) { // 当前最高位为 1
      j -= k; // 将当前最高位置 0
      k >>= 1; // 看下一位
    }

    j += k; // 当前最高位为 0，进位结束
  }
}

// -1 DFT
// 1 IDFT
vector<complex<double> > FFT(vector<double> &input, int op) {
  vector<complex<double> > C;
  int padLen;
  padding(input, padLen, C);
  rader(C);

  for (int T = 2; T <= padLen; T <<= 1) {
    complex<double> Wn(cos(op * 2 * PI / T), sin(op * 2 * PI / T));

    for (int i = 0; i < padLen; i += T) {
      complex<double> W(1, 0);

      for (int j = i; j < i + T / 2; ++j) {
        complex<double> u = C[j];
        complex<double> v = W * C[j + T / 2];

        C[j] = u + v;
        C[j + T / 2] = u - v;
        W *= Wn;
      }
    }
  }

  if (op == 1) {
    for (int i = 0; i < padLen; ++i)
      C[i] /= padLen;
  }

  return C;
}

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
    print(FFT(input, type));
  }
}
