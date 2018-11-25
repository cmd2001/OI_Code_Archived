#include<cstdio>
int main() {
    static double x;
    scanf("%lf",&x);
    x = x * ( x + 1 ) / ( 2 * ( 2 * x - 1 ) );
    printf("%0.9lf\n",x);
    return 0;
}
