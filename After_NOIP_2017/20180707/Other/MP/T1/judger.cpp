#include<bits/stdc++.h>
#define LOG cerr
using namespace std;
const int maxn=2e4+1e2;

int xl[maxn],yl[maxn],xr[maxn],yr[maxn],wr[maxn],n,m,ans,fce;
bool vl[maxn],vr[maxn];

inline int dis(int i,int j) {
    return abs(xl[i]-xr[j]) + abs(yl[i]-yr[j]);
}

int main(int argc,char** argv) { // input std_output force_output
    FILE *input = fopen(argv[1],"r") , *std_output = fopen(argv[2],"r") , *force_output = fopen(argv[3],"r");
    fscanf(input,"%d%d",&n,&m);
    for(int i=1;i<=n;i++) fscanf(input,"%d%d",xl+i,yl+i);
    for(int i=1;i<=m;i++) fscanf(input,"%d%d%d",xr+i,yr+i,wr+i);
    fscanf(std_output,"%d",&ans) , fscanf(force_output,"%d",&fce);
    if( ans != fce ) return LOG << "Wrong Answer number" << endl , 1;
    while( ans-- ) {
        int i,j; fscanf(std_output,"%d%d",&i,&j);
        if( vl[i] || vr[j] ) return LOG << "Point Used Twice!" << endl , 1;
        vl[i] = vr[j] = 1;
        if( dis(i,j) > wr[j] ) return LOG << "Distence Is Too Long" << endl , 1;
    }
    LOG << "Accepted" << endl;
    return 0;
}

