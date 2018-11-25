#include<iostream>
#include<cstdio> 
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1e6+1e2;

int now[maxn];
int ope[maxn],arg1[maxn],arg2[maxn];
int srt[maxn],len;

struct BinaryIndexTree {
    lli dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <= len )
            dat[pos] += x , pos += lowbit(pos);
    }
    inline lli query(int pos) {
        lli ret = 0;
        while( pos )
            ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
}sum,cont;

int main() {
    static char o[10];
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) {
        scanf("%s%d%d",o,arg1+i,arg2+i) , srt[++len] = arg2[i];
        if( *o == 'Z' ) ope[i] = 1 ;
    }
    srt[++len] = 0;
    sort(srt+1,srt+1+len) , len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=m;i++) arg2[i] = lower_bound(srt+1,srt+1+len,arg2[i]) - srt;
    for(int i=1;i<=n;i++) now[i] = lower_bound(srt+1,srt+1+len,0) - srt;
    for(int i=1;i<=m;i++) {
        if( !ope[i] ) {
            if( srt[now[arg1[i]]] > 0 ) {
                sum.update(now[arg1[i]],-srt[now[arg1[i]]]) ,
                cont.update(now[arg1[i]],-1);
            }
            now[arg1[i]] = arg2[i];
            if( srt[arg2[i]] > 0 ) {
                sum.update(arg2[i],srt[arg2[i]]) ,
                cont.update(arg2[i],1);
            }
        } else {
            int full = cont.query(len);
            lli abo = cont.query(len) - cont.query(arg2[i]);
            lli ss = sum.query(arg2[i]) + abo * srt[arg2[i]];
            puts( ( full >= arg1[i] && ss >= (lli) arg1[i] * srt[arg2[i]] ) ? "TAK" : "NIE" );
        }
    }
    return 0;
}
