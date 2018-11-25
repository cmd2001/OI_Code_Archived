#include<bits/stdc++.h>
typedef long long int lli;
using namespace std;

inline lli calc(lli p) {
    lli fac=1;
    for(int i=1;i<p;i++) fac = fac * i % p;
    fac = fac * 2 % p , fac += 2;
    return fac;
}

int main() {
    for(int i=1;i<=10000;i++) {
        lli t = calc(i);
        if( t != i && t != 2 ) cerr<<"Error at i = "<<i<<endl;
    }
    return 0;
}