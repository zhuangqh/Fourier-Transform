#ifndef _FFT_1D_H
#define _FFT_1D_H

#include <vector>
#include <complex>
#include <iostream>

using std::vector;
using std::complex;

class FFT_2D {
private:
  int padLenX;
  int padLenY;
  int op;

  vector<vector<complex<double> > > A;
  vector<vector<double> > input;

  void padding();
  void rader(int idx, bool isRow);
public:
  FFT_2D() {};
  vector<vector<complex<double> > > solve(vector<vector<double> > input, int op);
  void helper(int idx, bool isRow);
  static void print(const vector<vector<complex<double> > > &C);
};

#endif
