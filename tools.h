#include<bits/stdc++.h>
#ifndef tools_h
#define tools_h
using namespace std;

long long gcd(long long a, long long b);
long long lcm(long long a, long long b);

void div0();

struct Frac {
  public:
  long long a;
  long long b;

  Frac();

  Frac(long long a_, long long b_);

  Frac(double a_);
  
  Frac(long long a_);
  
  Frac treat();
  
  Frac operator+(const struct Frac &o) const; 
  
  Frac operator-(const struct Frac &o) const; 
  
  Frac operator*(const struct Frac &o) const;
  
  Frac operator/(const struct Frac &o) const;

  bool operator<(const struct Frac &o) const;
  
  bool operator==(const struct Frac &o) const;

  bool operator>(const struct Frac &o) const;
  
  bool operator<(const long long &o) const;

  bool operator>(const long long &o) const; 
  
  bool operator==(const long long &o) const;
  
};


ostream &operator<<(ostream &os, const Frac &p);

void collect();

void printVector(vector<Frac> &v);
#endif
