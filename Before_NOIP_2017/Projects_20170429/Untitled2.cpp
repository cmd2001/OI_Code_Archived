#include<cstdio>
#define lowbit(x) (x&(-x))
#define debug cout
using namespace std;
const int maxn=32768;
const int N=32766;
int dat[maxn],n,cnt[maxn];
void update(int pos)
{
    while(pos<N)
    {
        dat[pos]++;
        pos+=lowbit(pos);
    }
}
int query(int pos)
{
    int ret=0;
    while(pos)
    {
        ret+=dat[pos];
        pos-=lowbit(pos);
    }
    return ret;
}
int main()
{
    scanf("%d",&n);
    int a;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%*d",&a);
        a++;
        cnt[query(a)]++;
        update(a);
    }
    for(int i=0;i<n;i++) printf("%d\n",cnt[i]);
    return 0;
}
