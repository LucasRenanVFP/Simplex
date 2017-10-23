#include "simplex.h"
void Simplex::read() {
  started = false;
  aux = false;
  infeasible = false;
  unbounded = false;
  collect();
  answer = Frac(0ll);
  cin >> n_constraints >> n_variables;
  A.resize(n_constraints + 1);
  for(int i = 0; i < A.size(); i++) A[i].resize(n_variables + 2 * n_constraints + 1);
  base.resize(n_variables + n_constraints, false);
  pos.resize(n_variables + n_constraints);
  c.resize(n_variables + n_constraints);
  collect();
  for(int i = 0; i <= n_constraints; i++) {
    collect();
    for(int j = 0; j <= n_variables; j++) {
      double value;
      collect();
      cin >> value;
      A[i][j] = Frac(value);
    }
  }

  for(int i = 0; i < n_variables; i++) c[i] = A[0][i];

  b_col = n_constraints + n_variables;

  for(int i = 0; i <= n_constraints; i++) {
    A[i][b_col] = A[i][n_variables];
  }


  for(int i = 0; i <= n_constraints; i++) {
    for(int j = 0; j < n_constraints; j++) {
      A[i][j + n_variables] = A[i][j + b_col + 1] = Frac(0ll);
    }
  }
  for(int i = 0; i < n_constraints; i++) {
    A[i + 1][i + n_variables] = A[i + 1][i + b_col + 1] = Frac(1ll);
  }

  n_variables += n_constraints;
  base.resize(n_variables, false);
}

bool Simplex::isDual() {
  for(int i = 0; i < n_variables; i++) {
    if(A[0][i] > 0) return false;
  }
  return true;
}

bool Simplex::isPrimal() {
  for(int i = 1; i <= n_constraints; i++) {
    if(A[i][b_col] < 0) return false;
  }
  return true;
}

void Simplex::pivot(int i, int j) {
  if(A[i][j] == 0) {
    cerr << "Tentando pivotear posicao com valor 0." << endl;
    return;
  }
  Frac multiplier = Frac(1ll) / A[i][j];
  for(int k = 0; k < A[i].size(); k++) {
    A[i][k] = A[i][k] * multiplier;
  }

  for(int x = 0; x < A.size(); x++) {
    if(x == i) continue;
    multiplier = A[x][j] * Frac(-1ll);
    for(int k = 0; k < A[x].size(); k++) {
      A[x][k] = A[x][k] + multiplier * A[i][k];
    }
  }
}

bool Simplex::isOptimal() {
  for(int i = 0; i < n_variables; i++) {
    if(A[0][i] > 0) return false;
  }
  for(int i = 1; i < A.size(); i++) {
    if(A[i][b_col] < 0) return false;
  }
  return true;
}

pair<int, int> Simplex::getPosPrimal() {
  int row = -1, col;
  
  for(int i = 0; i < n_variables; i++) {
    if(A[0][i] > 0) {
      col = i;
      break;
    }
  }
  
  for(int i = 1; i < A.size(); i++) {
    if(!(A[i][col] > 0)) continue;
    if(row == -1) row = i;
    else {
      if(A[i][b_col] / A[i][col] < A[row][b_col] / A[row][col]) {
        row = i;
      }
    }
  }
  
  if(row == -1) {
    unbounded = true;
    cout << "PL ilimitada, aqui esta um certificado ";
    vector<Frac> d(n_variables, Frac(0ll));
    d[col] = Frac(1ll);
    for(int i = 0; i < base.size(); i++) {
      if(base[i]) {
        d[i] = Frac(-1ll) * A[pos[i]][col];
      }
    }
    printVector(d);
    cout << endl;
    return make_pair(-1, -1);
  }
  
  for(int i = 0; i < base.size(); i++) {
    if(base[i] and pos[i] == row) {
      base[i] = false;
      pos[i] = 0;
      break;
    }
  }
  
  base[col] = true;
  pos[col] = row;
  return make_pair(row, col);
}

pair<int, int> Simplex::getPosDual() {
  int row, col = -1;

  for(int i = 1; i < A.size(); i++) {
    if(A[i][b_col] < 0) {
      row = i;
      break;
    }
  }
  
  for(int i = 0; i < n_variables; i++) {
    if(!(A[row][i] < 0)) continue;
    if(col == -1) {
      col = i;
    }
    else {
      if(A[0][i] / A[row][i] < A[0][col] / A[row][col]) {
        col = i;
      }
    }
  }
  
  if(col == -1) {
    cout << "PL inviavel, aqui esta um certificado ";
    vector<Frac> d;
    infeasible = true;
    for(int i = 0; i < n_constraints; i++) {
      d.push_back(A[row][b_col + 1 + i]);
    }
    printVector(d);
    cout << endl;
    return make_pair(-1, -1);
  }
  
  for(int i = 0; i < base.size(); i++) {
    if(base[i] and pos[i] == row) {
      base[i] = false;
      pos[i] = 0;
    }
  }
  base[col] = true;
  pos[col] = row;
  return make_pair(row, col);
}

void Simplex::optimality() {
  cout << "[";  
  for(int j = b_col + 1; j < A[0].size(); j++) {
    if(j != b_col + 1) cout << ", ";
    cout << A[0][j];
  }
  cout << "]" << endl;
}

void Simplex::solveDual() {
  int iteration = 1;
  cerr << "Simplex Dual acionado" << endl;
  cout << "Iteracao 0" << endl;
  print();
  
  if(!started) {
    for(int i = 0; i < n_constraints; i++) {
      base[n_variables - n_constraints + i] = true;
      pos[n_variables - n_constraints + i] = i + 1;
    }
  }
  
  while(!isOptimal()) {
    pair<int, int> to_pivot = getPosDual();
    if(infeasible) return;
    pivot(to_pivot.first, to_pivot.second);
    cout << "Iteracao " << iteration++ << endl;
    print();
  }
  
  if(!infeasible) {
    vector<Frac> ans(n_variables, Frac(0ll));
    vector<Frac> printans(n_variables - n_constraints, Frac(0ll));
    for(int i = 0; i < n_variables; i++) {
      if(base[i]) {
        if(i < (n_variables - n_constraints)) printans[i] = A[pos[i]][b_col];
        ans[i] = A[pos[i]][b_col];
        if(i < c.size())
          answer = answer + (c[i] * ans[i]);
      }
    }
    if(!aux) {
      cout << "Solucao otima x = ";
      printVector(printans);
      cout << ", com valor objetivo " << answer << " e certificado y = ";
      optimality();
    }

  }
}


void Simplex::solvePrimal() {
  cerr << "Simplex Primal acionado" << endl;
  int iteration = 1;
  cout << "Iteracao 0" << endl;
  print();
  
  if(!started) {
    for(int i = 0; i < n_constraints; i++) {
      base[n_variables - n_constraints + i] = true;
      pos[n_variables - n_constraints + i] = i + 1;
    }
  }
  
  while(!isOptimal()) {
    pair<int, int> to_pivot = getPosPrimal();
    if(unbounded) return;
    pivot(to_pivot.first, to_pivot.second);
    cout << "Iteracao " << iteration++ << endl;
    print();
  }
  
  if(!unbounded) {
    vector<Frac> ans(n_variables, Frac(0ll));
    vector<Frac> printans(n_variables - n_constraints, Frac(0ll));
    for(int i = 0; i < n_variables; i++) {
      if(base[i]) {
        if(i < (n_variables - n_constraints)) printans[i] = A[pos[i]][b_col];
        ans[i] = A[pos[i]][b_col];
        if(i < c.size()) answer = answer + (c[i] * ans[i]);
      }
    }
    if(!aux) {
      cout << "Solucao otima x = ";
      printVector(printans);
      cout << ", com valor objetivo " << answer << " e certificado y = ";
      optimality();
    }
  }
}

void Simplex::print() {
  for(int i = 0; i < A.size(); i++) {
    for(int j = 0; j < A[i].size(); j++) {
      if(j != 0) cout << " ";
      cout << A[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

void Simplex::becomeAuxiliar() {
  aux = true;
  int shift = n_constraints;
  int new_sz = n_constraints * 2 + n_variables + 1;
  for(int i = 0; i < A.size(); i++) A[i].resize(new_sz, Frac(0ll));
  base.resize(n_variables + n_constraints, false);
  pos.resize(n_variables + n_constraints, 0);
  c.resize(n_variables + n_constraints, Frac(0ll));
  Frac minus = Frac(-1ll);
  
  for(int i = 1; i < A.size(); i++) {
    if(A[i][b_col] < 0) {
      for(int j = 0; j < A[i].size(); j++) A[i][j] = A[i][j] * minus;
    }
  }

  for(int i = 0; i < A.size(); i++) {
    for(int j = n_variables + n_constraints; j >= b_col; j--) {
      assert(j + shift < A[i].size());
      A[i][j + shift] = A[i][j];
      A[i][j] = Frac(0ll);
    }
  }

  for(int i = 1; i < A.size(); i++) {
    assert(b_col + i - 1 < A[i].size());
    A[i][b_col + i - 1] = Frac(1ll);
  }
  
  for(int i = 0; i < A[0].size(); i++) {
    A[0][i] = Frac(0ll);
    if(i < c.size()) c[i] = A[0][i];
  }
  
  for(int i = 0; i < n_constraints; i++) {
    A[0][b_col + i] = Frac(-1ll);
    assert(b_col + i < A[0].size());
    if(b_col + i < c.size()) c[b_col + i] = A[0][b_col + i];
  }
  
  for(int i = 1; i < A.size(); i++) {
    pivot(i, b_col + i - 1); 
  }
  n_variables += n_constraints;
  b_col = b_col + shift;

}

