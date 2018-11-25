#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cerr
using namespace std;
const int maxn = 11000100;

char in[maxn],s[maxn<<1];
int f[maxn<<1];

int main() {
    static int n,li;
    fread(in+1,1,maxn-1,stdin), li = strlen(in+1);
    while(in[li] == '\n' || in[li] == '\r') --li;
    s[++n] = '#';
    for(int i=1;i<=li;i++) s[++n] = in[i], s[++n] = '#';
    int mxr = 0, pos = 0, ans = 0;
    for(int i=1;i<=n;i++) {
        if(i <= mxr) f[i] = max(1, min(f[pos*2-i], mxr - i));
        while(i + f[i] <= n && s[i+f[i]] == s[i-f[i]]) ++f[i];
        if(i + f[i] > mxr) mxr = i + f[i], pos = i;
        ans = max(ans, f[i] - 1);
    }
    printf("%d\n",ans);
    return 0;
}

//qwertyuioppoiuytasdfggfdsazxcvbbvcxz
