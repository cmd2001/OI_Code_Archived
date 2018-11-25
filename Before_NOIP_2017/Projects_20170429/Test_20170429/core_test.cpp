#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
long long int org[maxn];
int n,m,i,j,s,e,tmp,t;
long long int sum;
char cmd;
void update(int pos,int x)
{
    while(pos<=n)
    {
        debug<<"pos="<<pos<<endl;
        org[pos]+=x;
        pos+=lowbit(pos);
    }
}
long long int query(int pos)
{
    long long int ret=0;
    while(pos)
    {
        debug<<"pos="<<pos<<endl;
        ret+=org[pos];
        pos-=lowbit(pos);
    }
    return ret;
}
int main()
{
    int a,b,c,d;
    n=1e3;
    while(1)
    {
        cin>>a;
        if(a==1)
        {
            cin>>b>>c>>d;
            update(b,d);
            update(c,-d);
        }
        else
        {
            cin>>b;
            cout<<query(b)<<endl;
        }
    }
}
