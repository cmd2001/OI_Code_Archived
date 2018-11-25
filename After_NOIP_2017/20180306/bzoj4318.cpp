#include<cstdio>

int main() {
    static int n;
    static double in,x,x2,x3;
    scanf("%d",&n);
    while(n--) {
        scanf("%lf",&in);
        x3 += in * ( 3 * x2 + 3 * x + 1 ) ,
        x2 = in * ( x2 + 2 * x + 1 ) ,
        x = ( x + 1 ) * in;
    }
    printf("%0.1lf\n",x3);
    return 0;
}
