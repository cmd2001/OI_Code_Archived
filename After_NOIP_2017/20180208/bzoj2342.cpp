#include<iostream>
#include<cstdio>
const int maxn=1e6+1e2;

char in[maxn],s[maxn];
int f[maxn],n,len,id,mx,ans;

int main() {
    scanf("%d%s",&n,in+1);
    *s = '$';
    for(int i=1;i<=n;i++)
        s[++len] = '#' , s[++len] = in[i];
    for(int i=1;i<=len;i++) {
        f[i] = i < mx ? std::min( f[id*2-i] , mx-i ) : 1;
        while( s[i-f[i]] == s[i+f[i]] ) ++f[i];
        if( i + f[i] > mx ) mx = i + f[i] , id = i;
    }
    for(int i=1;i<=len;i+=2) {
        int l = ( ( i - f[i] + 1 ) + i ) >> 1;
        if( ! ( l & 1 ) ) ++l;
        while( l + f[l] < i ) l += 2;
        ans = std::max( ans , ( i - l ) >> 1 );
    }
    ans <<= 2;
    printf("%d\n",ans);
    return 0;
}
