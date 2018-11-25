#include <cstdio>  
#include <cstring>  
#include <cmath>  
#include <algorithm>  
#include <iostream>  
#include <cstdlib>  
#include <queue>  
typedef __int64 LL;  
using namespace std;  
const int maxn = 100005;  
int n,m;  
int T[maxn],a[maxn],b[maxn];  
int lson[maxn * 20],rson[maxn * 20],c[maxn*20];  
int tot,num;  
void hase(int k)  
{  
    sort(b,b+k);  
    num = unique(b,b+k) - b;  
}  
int get_hase(int now)  
{  
    return (lower_bound(b,b+num,now) - b);  
}  
int build(int l,int r)  
{  
    int newroot = tot++;  
    c[newroot] = 0;  
    if(l != r)  
    {  
        int mid = (l + r) >> 1;  
        lson[newroot] = build(l,mid);  
        rson[newroot] = build(mid + 1,r);  
    }  
    return newroot;  
}  
int ans;  
int insert1(int root,int pos,int val)  
{  
    int newroot = tot++;  
    int tmp = newroot;  
    c[newroot] = c[root] + val;  
    int l = 0,r = num - 1;  
    while(l < r)  
    {  
        int mid = (l + r) >> 1;  
        if(pos <= mid)  
        {  
            lson[newroot] = tot++;  
            rson[newroot] = rson[root];  
            root = lson[root];  
            newroot = lson[newroot];  
            r = mid;  
        }  
        else  
        {  
            lson[newroot] = lson[root];  
            rson[newroot] = tot++;  
            root = rson[root];  
            newroot = rson[newroot];  
            l = mid + 1;  
  
        }  
        c[newroot] = c[root] + val;  
    }  
    return tmp;  
}  
int qurry(int ll,int rr,int pos)  
{  
    int rootl = T[ll];  
    int rootr = T[rr];  
    int l = 0,r = num - 1;  
    ans = 0;  
    while(l < r)  
    {  
        int mid = (l + r) >> 1;  
        int cou = c[lson[rootr]] - c[lson[rootl]];  
        if(cou < pos)  
        {  
            pos -= cou;  
            rootr = rson[rootr];  
            rootl = rson[rootl];  
            l = mid + 1;  
            ans += cou;  
        }  
        else  
        {  
            rootr = lson[rootr];  
            rootl = lson[rootl];  
            r = mid;  
        }  
    }  
    ans += c[rootr] - c[rootl];  
    return l;  
}  
int main()  
{  
    int t;  
    scanf("%d",&t);  
    int ca = 1;  
    while(t--)  
    {  
        scanf("%d %d",&n,&m);  
        int i,j;  
        num = tot = 0;  
        for(i = 1; i <= n; i++)  
        {  
            scanf("%d",&a[i]);  
            b[num++] = a[i];  
        }  
        hase(num);  
        T[0] = build(0,num-1);  
        for(i = 1; i <= n; i++)  
        {  
            T[i] = insert1(T[i-1],get_hase(a[i]),1);  
        }  
        printf("Case %d:\n",ca++);  
        while(m--)  
        {  
            int q,w,h;  
            scanf("%d %d %d",&q,&w,&h);  
            q++,w++;  
            int l = 1,r = w - q + 2;  
            while(r - l > 1)  
            {  
                int mid = (l + r) >> 1;  
                int vv = qurry(q-1,w,mid);  
                int now = b[vv];  
                if(b[vv] <= h)  
                    l = mid;  
                else  
                    r = mid;  
            }  
            int vv = qurry(q-1,w,l);  
            if(b[vv] > h)  
            {  
                printf("0\n");  
                continue;  
            }  
            printf("%d\n",ans);  
        }  
    }  
    return 0;  
}
