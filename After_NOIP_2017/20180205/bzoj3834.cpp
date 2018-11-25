#include<cstdio>

inline void _swap(int &x,int &y) {
    int t = x;
    x = y , y = t;
}
inline int _min(int a,int b) {
    return a < b ? a : b;
}
inline int _max(int a,int b) {
    return a < b ? b : a;
}

int a,b,c,d,ans;

inline void getans() {
    ans = 1 , --a , --c;
    #define judge(l,r,x) ( r / x > l / x )
    if( d < b ) _swap( a , c ) , _swap( b , d );
    for(int i=1,j;i<=b;i=j+1) {
        j = _min( b / ( b / i ) , d / ( d / i ) );
        //if( i <= a ) j = _min( j , a / ( a / i ) );
        //if( i <= c ) j = _min( j , c / ( c / i ) );
        if( judge(a,b,j) && judge(c,d,j) ) ans = _max( ans , j );
    }
}
int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d%d%d",&a,&b,&c,&d);
        getans();
        printf("%d\n",ans);
    }
    return 0;
}
