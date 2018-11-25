#include<cstdio>
#include<cctype>

int fib[20]={1,1,2,3,0,3,3,1,4,0,4,4,3,2,0,2,2,4,1,0};

int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) ) ;
    return ret;
}

int main() {
    static int T;
    T = getint();
    while(T--) printf("%d\n",fib[(getint()-1)%20]);
}

