#include<cstdio>
using namespace std;

int main() {
    static int n;
    freopen("mothergoose.in","r",stdin);
    freopen("mothergoose.out","w",stdout);
    scanf("%d",&n);
    if( n <= 2 ) return printf("%d\n",2-n) , 0;
    fclose(stdout);
    return 0;
}
