#include<bits/stdc++.h>
#ifndef tools_h
#define tools_h
using namespace std;

__int128 gcd(__int128 a, __int128 b);
__int128 lcm(__int128 a, __int128 b);

void div0();

struct Frac {
  public:
  __int128 a;
  __int128 b;

  Frac();

  Frac(__int128 a_, __int128 b_);

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

ostream &operator<<(ostream &os, const __int128 &p);

ostream &operator<<(ostream &os, const Frac &p);

void collect();

void printVector(vector<Frac> &v);
#endif
