#include<cstdio>

int main() {
    static int in[55],n,ans;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",in+i);
        for(int j=1;j<i;j++) ans ^= ( in[j] < in[i] );
    }
    puts(ans?"Q":"T");
    return 0;
}
