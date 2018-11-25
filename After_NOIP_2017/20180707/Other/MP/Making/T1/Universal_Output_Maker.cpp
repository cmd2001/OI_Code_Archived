#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1e2;

char in[maxn],com[maxn];
int siz;

int main() {
    scanf("%d%s",&siz,in);
    for(int i=1;i<=siz;i++) {
        sprintf(com,"./std < %s%d.in > %s%d.out",in,i,in,i);
        cerr<<"Making Case :: "<<i<<endl;
        system(com);
    }
    return 0;
}

