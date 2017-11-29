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
    vector<int> falta;
    for(int i = 1; i < PL.A.size(); i++) {
      for(int j = 0; j < PL.A[i].size(); j++) {
        PL.A[i][j] = PLAuxiliar.A[i][j];
      }
    }
    for(int i = 1; i < PL.A.size(); i++) {
      PL.A[i][PL.b_col] = PLAuxiliar.A[i][PLAuxiliar.b_col];
    }
    for(int i = 0; i < b.size(); i++) {
      if(b[i]) {
        if(i >= PL.A.size()) {
          falta.push_back(p[i]);
          continue;
        }
        PL.base[i] = true;
        PL.pos[i] = p[i];
        cout<<PL.pos[i]<<" "<<i<<" BASE"<<endl;
        PL.pivot(p[i], i);
      }
    }
    for(int i = 0; i < falta.size(); i++) {
      int row = falta[i];
      for(int j = 0; j < PL.n_variables; j++) {
        if(!(PL.A[row][j] == 0)) {
          PL.base[j] = true;
          cout<<"virou base "<<row<<" "<<j<<endl;
          PL.pos[j] = row;
          PL.pivot(row, j);
          break;
        }
      }
    }
    PL.solvePrimal();
  }
}
