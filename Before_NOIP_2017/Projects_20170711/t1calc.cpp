#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+1e2;

int num[maxn];
inline void gen(int pos,int x,int n)
{
    for(int i=pos+1;i<=n;i++)
    {
        num[i]=x;
        x++;
    }
}
inline int add(int pos,int n)
{
    int ret=0;
    for(int i=pos+1;i<=n;i++) ret+=num[i];
    return ret;
}
inline void put(int n)
{
    for(int i=1;i<=n;i++) cout<<num[i]<<" ";
    cout<<endl;
}

int main()
{
    gen(1,0,8);
    cout<<(add(1,8))<<endl;
    put(8);
    return 0;
}


