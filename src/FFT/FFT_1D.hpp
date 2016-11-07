#ifndef _FFT_1D_H
#define _FFT_1D_H

#include <vector>
#include <complex>
#include <iostream>

using std::vector;
using std::complex;

class FFT {
private:
  int padLen;
  int op;
  vector<complex<double> > A;
  vector<double> input;

  void padding();
  void rader();
public:
  FFT() {};
  vector<complex<double> > solve(vector<double> input, int op);
  static void print(const vector<complex<double> > &C);
};

#endif
