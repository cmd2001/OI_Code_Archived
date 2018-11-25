#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1.5e4+1e2;
 
char in[maxn];
int nxt[maxn];
int n,k,ans;
 
inline void calc(int p) {
    for(int i=1;i<=p;i++) nxt[i] = p - 1;
    for(int i=p+1;i<=n;i++) {
        int j = nxt[i-1];
        while( j != p-1 && in[j+1] != in[i] ) j = nxt[j];
        if( in[j+1] == in[i] ) ++j;
        nxt[i] = j;
    }
    int j = p - 1;
    for(int i=p+1;i<=n;i++) {
        while( j != p-1 && in[j+1] != in[i] ) j = nxt[j];
        if( in[j+1] == in[i] ) ++j;
        while( ( j - p + 1 ) * 2 >= ( i - p + 1 ) ) j = nxt[j];
        if( j - p + 1 >= k ) ++ans;
    }
}
 
int main() {
    scanf("%s%d",in+1,&k) , n = strlen(in+1);
    for(int i=1;i<=n;i++) calc(i);
    printf("%d\n",ans);
    return 0;
}

