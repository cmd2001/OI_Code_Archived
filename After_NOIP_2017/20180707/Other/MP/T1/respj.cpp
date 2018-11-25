#include<bits/stdc++.h>
#define LOG cerr
using namespace std;
const int maxn=2e5+1e2;

int x[maxn],y[maxn],xx[maxn],yy[maxn],w[maxn];
bool vl[maxn],vr[maxn];
int n,m,std_ans;

FILE *INP,*OTP;

inline void AC() { exit(0); }
inline void WA() { exit(1); }

inline int readint() {
    static int ret = 0;
    if( !~fscanf(OTP,"%d",&ret) ) WA();
    return ret;
}

inline int dis(int i,int j) {
    return abs(x[i]-xx[j]) + abs(y[i]-yy[j]);
}
int main(int argc,char** argv) {
    static int usr_ans,i,j,hsh=std::hash<string>()("KurenaiKisaragi");
    INP = fopen(argv[1],"r") , OTP = fopen(argv[2],"r");
    fscanf(INP,"%d%d",&n,&m);
    for(int i=1;i<=n;i++) fscanf(INP,"%d%d",x+i,y+i);
    for(int i=1;i<=m;i++) fscanf(INP,"%d%d%d",xx+i,yy+i,w+i);
    fscanf(INP,"%d",&std_ans) , std_ans ^= hsh , usr_ans = readint();
    if( usr_ans != std_ans ) WA();
    while( usr_ans-- ) {
        i = readint() , j = readint();
        if( i < 0 || j < 0 || i > n || j > m ) WA();
        if( vl[i] || vr[j] ) WA();
        if( dis(i,j) > w[j] ) WA();
        vl[i] = vr[j] = 1;
    }
    AC();
}
