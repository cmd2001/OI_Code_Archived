#include<cstdio>
using namespace std;

int main() {
    static int n;
    scanf("%d",&n);
    if( n <= 2 ) return printf("%d\n",2-n) , 0;
    return 0;
}

