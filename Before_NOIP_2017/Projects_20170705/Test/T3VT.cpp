#include<bits/stdc++.h>
using namespace std;

int main()
{
    __int128 a=1,b=1;
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) a*=i;
    for(int i=1;i<=k;i++) b*=i;
    for(int i=1;i<=n-k;i++) b*=i;
    
    cout<<(long long)(a/b)<<endl; 
    return 0;
}
