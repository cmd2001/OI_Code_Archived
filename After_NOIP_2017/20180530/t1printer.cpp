#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;

char a[maxn],b[maxn];

inline void print(char* dst,int x,int base) {
    while(x) *dst++ = x % base + '0' , x /= base;
    *dst = 0;
}
inline bool judge(int x) {
    static int la;
    print(a,x,10) , print(b,x,2) , la = strlen(a);
    for(int i=0;i<la;i++) if( a[i] != b[i] ) return 0;
    return 1;
}

int main() {
    int cnt = 0;
    for(int i=1;i<=100000000;i++) if( judge(i) ) printf("%d,",i) , ++cnt;
    printf("cnt = %d\n",cnt);
    return 0;
}
