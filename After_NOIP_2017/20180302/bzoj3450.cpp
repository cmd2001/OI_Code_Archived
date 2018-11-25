#include<cstdio>
const int inf=3e5+1e2;

int n;
char in[inf];
double ans,l;

int main() {
    scanf("%d%s",&n,in+1);
    for(int i=1;i<=n;i++) {
        if( in[i] == 'x' ) l = 0;
        else if( in[i] == 'o' ) ans += l * 2 + 1 , l = l + 1;
        else ans += l + 0.5 , l = ( l + 1 ) / 2;
    }
    printf("%0.4lf\n",ans);
    return 0;
}
