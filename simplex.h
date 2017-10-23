#ifndef simplex_h
#define simplex_h
#include<bits/stdc++.h>
#include "tools.h"
class Simplex {
  public:
  int n_constraints;
  int n_variables;
  int b_col;
  bool unbounded;
  bool infeasible;
  bool aux;
  bool started;
  vector< vector<Frac> > A;
  vector<Frac> c;
  vector<bool> base;
  vector<int> pos;
  Frac answer;
  void read();

  bool isDual();

  bool isPrimal();

  void pivot(int i, int j);

  bool isOptimal();

  pair<int, int> getPosPrimal();

  pair<int, int> getPosDual();

  void optimality();

  void solveDual();

  void solvePrimal();

  void print();

  void becomeAuxiliar();

};

#endif
