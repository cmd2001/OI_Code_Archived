#include<bits/stdc++.h>
#define debug cout
using namespace std;

inline bool judge(string x) {
    int len = x.length();
    for(int i=0;i<=len/2;i++)
        if( x[i] != x[len-1-i] ) return 0;
    return 1;
}

int main() {
    string in;
    cin>>in;
    int len = in.length() , ans = 0;
    for(int sx=0;sx<len;++sx)
        for(int tx=sx;tx<len;++tx)
            for(int sy=0;sy<len;++sy)
                for(int ty=sy;ty<len;++ty) {
                    ans += judge( in.substr(sx,tx-sx+1) + in.substr(sy,ty-sy+1) ) * ( tx - sx + 1 + ty - sy + 1 ) ;
                }
    cout<<ans<<endl;
    return 0;
}