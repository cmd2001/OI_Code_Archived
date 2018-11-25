#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int arr[maxn],mks[maxn];
int n=1e6;

inline int _rand(int l,int r) {
    return rand() % ( r - l + 1 ) + l;
}

int main() {
    int m = 0;
    freopen("dat.txt","w",stdout);
    srand(time(0));
    for(int i=1;i<=n;i++)
        arr[i] = i;
    random_shuffle(arr+1,arr+1+n);
    mks[n] = 1;
    for(int i=1;i<=n;i++) {
        //debug<<mks[n]<<endl;
        if( ( !mks[i-1] ) && ( rand()&1 ) )
            mks[i] = 1;
    }
    for(int i=1;i<=n;i++)
        m = m + mks[i];
    //debug<<endl;
    printf("%d %d\n",n,m);
    for(int i=1,j,siz;i<=n;i=j+1) {
        j = i , siz = 0;
        while( j <= n ) {
            siz++;
            if( mks[j] )
                break;
            j++;
        }
        printf("%d ",siz);
        for(int k=i;k<=j;k++)
            printf("%d ",arr[k]);
        printf("%d\n",_rand(7,100000));
    }
    int t = _rand(2,20);
    printf("%d\n",t);
    for(int i=1;i<=t;i++)
        printf("%d %d\n",arr[i],_rand(100000/2,100000));
    return 0;
}