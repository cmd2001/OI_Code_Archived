#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cctype>
#define lli long long int
#define mid ( ( ll + rr ) >> 1 )
#define debug cout
using namespace std;
const int maxn=2e4+1e2,maxk=1e2+1e1;
const int inf = 0x3f3f3f3f;

int c[maxn],poss[maxn],st[maxn],ed[maxn],s[maxn];
lli w[maxn],f[maxn];
vector<int> vec[maxn];
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3];
lli dat[maxn<<3],lazy[maxn<<3];
int n,m,k,cnt;
lli ans;

inline void build(int pos,int ll,int rr)
{
    //debug<<"ll = "<<ll<<"rr = "<<rr<<endl;
    l[pos] = ll , r[pos] = rr;
    dat[pos] = f[ll] , lazy[pos] = 0;
    if( ll == rr )
        return;
    build( lson[pos] = ++cnt , ll , mid );
    build( rson[pos] = ++cnt , mid + 1 , rr );
    dat[pos] = min( dat[lson[pos]] , dat[rson[pos]] );
}

inline void push(const int &pos)
{
    if( lazy[pos] )
    {
        if( lson[pos])
            lazy[lson[pos]] += lazy[pos] , dat[lson[pos]] += lazy[pos];
        if( rson[pos] )
            lazy[rson[pos]] += lazy[pos] , dat[rson[pos]] += lazy[pos];
        lazy[pos] = 0 ;
    }
}

inline void update(int pos,const int &ll,const int &rr,const lli &lam)
{
    if( rr < l[pos] || r[pos] < ll )
        return;
    if( ll <= l[pos] && r[pos] <= rr )
    {
        lazy[pos] += lam;
        dat[pos] += lam;
        return;
    }
    push(pos);
    update( lson[pos] , ll , rr , lam );
    update( rson[pos] , ll , rr , lam );
    dat[pos] = min( dat[lson[pos]] , dat[rson[pos]] );
}

inline lli query(int pos,const int &ll,const int &rr)
{
    if( rr < l[pos] || r[pos] < ll )
        return inf;
    if( ll <= l[pos] && r[pos] <= rr )
        return dat[pos];
    push(pos);
    return min( query(lson[pos],ll,rr) , query(rson[pos],ll,rr) );
}

inline void pre()
{
    poss[++n] = inf ,
    w[n] = inf,
    m++;
    for(int i=1;i<=n;i++)
        st[i] = lower_bound(poss+1,poss+1+n,poss[i]-s[i]) - poss,
        ed[i] = lower_bound(poss+1,poss+1+n,poss[i]+s[i]) - poss,
        ed[i] -= poss[ed[i]] > poss[i] + s[i] ;
    for(int i=1;i<=n;i++)
        vec[ed[i]].push_back(i);
}
inline void getans()
{
    //memset(f,0x3f,sizeof(f));
    ans = inf;
    lli ss = 0;
    for(int dep=1;dep<=m;dep++)
    {
        //debug<<"dep = "<<dep<<endl;
        if( dep == 1 )
        {
            //debug<<"dep == 1 "<<endl;
            for(int i=1;i<=n;i++)
            {
                f[i] = c[i] + ss;
                for(unsigned j=0;j<vec[i].size();j++)
                    ss += w[vec[i][j]];
            }
            ans = f[n];
            /*for(int i=1;i<=n;i++)
                debug<<f[i]<<" ";debug<<endl;*/
            continue;
        }
        
        build(cnt=1,1,n);
        
        //debug<<"builded"<<endl;
        
        for(int i=1;i<=n;i++)
        {
            if( i - 1 )
                f[i] = query(1,1,i-1) + c[i];
            for(unsigned j=0;j<vec[i].size();j++)
            {
                const int xx = vec[i][j];
                if( st[xx] - 1 )
                    update(1,1,st[xx]-1,w[xx]);
            }
        }
        
        /*debug<<"dep = "<<dep<<endl;
        
        for(int i=1;i<=n;i++)
            debug<<f[i]<<" ";debug<<endl;*/
        
        ans = min( ans , f[n] );
    }
}

inline int getint()
{
    int ret = 0 , fix = 1;
    char ch = getchar();
    while( ! isdigit(ch) )
        fix = ch == '-' ? -1 : fix ,
        ch = getchar();
    while( isdigit(ch) )
        ret = ret * 10 + ( ch - '0' ) ,
        ch = getchar();
    return ret * fix;
}

int main()
{
    n = getint() , m = getint();
    for(int i=2;i<=n;i++)
        poss[i] = getint();
    for(int i=1;i<=n;i++)
        c[i] = getint();
    for(int i=1;i<=n;i++)
        s[i] = getint();
    for(int i=1;i<=n;i++)
        w[i] = getint();
    
    pre();
    
    /*for(int i=1;i<=n;i++)
    	debug<<st[i]<<" "<<ed[i]<<endl;*/
    	
    getans();
    
    printf("%lld\n",ans);
    
    return 0;
}
