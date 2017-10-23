#include "solver.h"

void Solver::solve(Simplex PL) {
  if(PL.isDual()) {
    PL.solveDual();
    return;
  }
  if(PL.isPrimal()) {
    PL.solvePrimal();
    return;
  }
  cerr << "PL auxiliar acionada" << endl;
  Simplex PLAuxiliar = PL;
  PLAuxiliar.becomeAuxiliar();
  PLAuxiliar.solvePrimal();
  if(PLAuxiliar.answer < 0) {
    cout << "PL inviavel, aqui esta um certificado ";
    PLAuxiliar.optimality();
  }
  else {
    PL.started = true;
    vector<bool> b = PLAuxiliar.base;
    vector<int> p = PLAuxiliar.pos;
    for(int i = 0; i < b.size(); i++) {
      if(b[i]) {
        PL.base[i] = true;
        PL.pos[i] = p[i];
        PL.pivot(p[i], i);
      }
    }
    PL.solvePrimal();
  }
}
