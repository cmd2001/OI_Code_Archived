#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1e2;

int su[maxn];

FILE *ans,*in;

int main() {
    static char buf[maxn];
    static int n;
    in = fopen("dat.txt","r") , ans = fopen("my.txt","r");
    fscanf(in,"%d",&n) , fscanf(ans,"%s",buf);
    if( *buf == 'N' ) return 0;
    for(int i=1,tar;i<=n;i++) {
        fscanf(in,"%d",&tar) , fscanf(ans,"%s",buf);
        if( strlen(buf) != tar + 2 ) cerr<<"Wrong Answer :: Length Error"<<endl , exit(1);
        for(int i=2;i<tar+2;i++) su[i-1] += buf[i] - '0';
    }
    //for(int i=1;i<=10;i++) cerr<<su[i]<<" "; cerr<<endl;
    for(int i=maxn-1;i;i--) su[i-1] += su[i] / 10 , su[i] %= 10;
    if( !*su )  cerr<<"Wrong Answer :: Sum Less Than 1"<<endl , exit(1);
    for(int i=1;i<maxn;i++) if( su[i] )cerr<<"Wrong Answer :: Sum More Than 1"<<endl , exit(1);
    cerr<<"Accepted"<<endl;
    return 0;
}