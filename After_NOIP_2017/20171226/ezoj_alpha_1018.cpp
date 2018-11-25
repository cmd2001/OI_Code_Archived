#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int in[maxn<<1],nums[maxn<<1];
int n,dep;

inline int findcon(int pos,int tar) {
    //debug<<"pos = "<<pos<<"tar = "<<tar<<endl;
    int l = pos , r = pos;
    while( l > 1 && ( nums[l]!=tar || nums[l-1]!=tar) )
        --l;
    while( r < ( n * 2 - 1 ) && ( nums[r]!=tar || nums[r+1]!=tar ) )
        ++r;
    //debug<<"l = "<<l<<"r = "<<r<<endl;
    return min( pos - l , r - pos );
}
inline void cov(int x) {
    for(int i=1;i<n<<1;i++)
        nums[i] = ( in[i] >= x );
}
inline bool judge(int x) {
    cov(x);
    /*debug<<"x = "<<x<<endl;
    for(int i=1;i<n<<1;i++)
        debug<<nums[i]<<" ";debug<<endl;*/
    int dze = findcon(n,0) , don = findcon(n,1);
    //debug<<"dze = "<<dze<<"don = "<<don<<endl;
    if( dze != don )
        return dze > don;
    return ! ( (dep + nums[n] ) & 1 );
}
inline int getans() {
    int ll = 1 , rr = ( n << 1 ) - 1 , mid;
    while( rr != ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( !judge(mid) )
            rr = mid;
        else ll = mid;
    }
    return ll;
}

int main() {
    scanf("%d",&n);
    dep = ( n + 1 ) >> 1;
    for(int i=1;i<n<<1;i++)
        scanf("%d",in+i);
    
    printf("%d\n",getans());
    
    return 0;
}