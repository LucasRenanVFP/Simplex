#include<bits/stdc++.h>
#include "solver.h"

int main() {
  Solver MasterSolver;
  while(true) {
    Simplex Simp;
    Simp.read();
    MasterSolver.solve(Simp);
  }
}


