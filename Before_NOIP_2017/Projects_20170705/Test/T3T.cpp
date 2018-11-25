#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+1e2;

int c[maxn][maxn];

int main()
{
    static int n;
    cin>>n;
    for(int i=1;i<=n;i++) c[i][0]=c[i][i]=1;

    for(int i=1;i<=n;i++)
    {
        for(int k=1;k<i;k++) c[i][k]=c[i-1][k-1]+c[i-1][k];
    }
    
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=n;j++) cout<<c[i][j]<<" ";
        cout<<endl;
    }

    return 0;
}
