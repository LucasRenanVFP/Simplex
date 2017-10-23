#include<bits/stdc++.h>
#include "tools.h"


long long gcd(long long a, long long b) { return (b == 0) ? a : gcd(b, a % b);}
long long lcm(long long a, long long b) { return (a / gcd(a, b)) * b;}

void div0() {
  cerr<<"Fracao invalida! Divisao por zero"<<endl;
  exit(0);
}

Frac::Frac() : a(0), b(1) {}

Frac::Frac(long long a_, long long b_) : a(a_), b(b_){
  long long g = gcd(a, b);
  a = a / g;
  b = b / g;
  if(b < 0) {
    a = -a;
    b = -b;
  }
}

Frac::Frac(double a_) {
  b = 100000000;
  a = (long long) round(a_ * (double)b);
  long long g = gcd(a, b);
  a = a / g;
  b = b / g;
  if(b < 0) {
    a = -a;
    b = -b;
  }

}

Frac::Frac(long long a_) : a(a_), b(1) {}

Frac Frac::treat() {
  long long g = gcd(a, b);
  if(g == 0) div0();
  if(b / g < 0) return Frac(-a / g, - b / g);
  return Frac(a / g, b / g);
}

Frac Frac::operator+(const struct Frac &o) const {
  long long den = lcm(b, o.b);
  if(den == 0) div0();
  return Frac(a * (den / b) + o.a * (den / o.b), den).treat();
}

Frac Frac::operator-(const struct Frac &o) const {
  long long den = lcm(b, o.b);
  if(den == 0) div0();
  return Frac(a * (den / b) - o.a * (den / o.b), den).treat();
}

Frac Frac::operator*(const struct Frac &o) const {
  return Frac(a * o.a, b * o.b).treat();
}

Frac Frac::operator/(const struct Frac &o) const {
  return Frac(a * o.b, b * o.a).treat();
}

bool Frac::operator<(const struct Frac &o) const { 
  return (a * o.b < o.a * b);
}

bool Frac::operator==(const struct Frac &o) const {
  return (a * o.b == o.a * b);
}

bool Frac::operator>(const struct Frac &o) const {
  return (a * o.b > o.a * b);
}

bool Frac::operator<(const long long &o) const {
  return *this < Frac(o);
}

bool Frac::operator>(const long long &o) const {
  return *this > Frac(o);
}

bool Frac::operator==(const long long &o) const {
  return *this == Frac(o);
}

ostream &operator<<(ostream &os, const Frac &p) {
  if(p.b == 1) os << p.a;  
  else os << p.a << "/" << p.b; 
}

void collect() {
  char c;
  c = cin.peek();
  if(cin.eof()) exit(0);
  while(c == ' ' or c == '[' or c == ']' or c == ',' or c == '\n') {
    getchar();
    c = cin.peek();
    if(cin.eof()) exit(0);
  }
}

void printVector(vector<Frac> &v) {
  cout << "[";
  for(int i = 0; i < v.size(); i++) {
    if(i != 0) cout << ", ";
    cout << v[i];
  }
  cout << "]";

}


