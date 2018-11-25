#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxq=6e5+1e2;
 
lli srt[maxq];
 
inline lli f(const lli &k,const lli &b,const int &x) {
    return k * srt[x] + b;
}
int l[maxq*7],r[maxq*7],lson[maxq*7],rson[maxq*7];
struct SegmentTree {
    int cnt;
    lli k[maxq<<3],b[maxq<<3];
     
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr )
            return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid);
        build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void update(int pos,int ll,int rr,lli kk,lli bb) {
    	//debug<<"pos = "<<pos<<"ll = "<<ll<<"rr = "<<rr<<endl;
    	//debug<<"kk = "<<kk<<"bb = "<<bb<<endl;
    	//debug<<"f = "<<f(kk,bb,(l[pos]))<<endl;
        if( rr < l[pos] || r[pos] < ll )
            return;
        if( ll <= l[pos] && r[pos] <= rr ) {
        	//debug<<"pos = "<<pos<<endl;
            if( f(kk,bb,l[pos]) <= f(k[pos],b[pos],l[pos]) && f(kk,bb,r[pos]) <= f(k[pos],b[pos],r[pos]) )
                return;
            if( l[pos] == r[pos] ) {
            	/*debug<<"==="<<endl;
            	debug<<"pos = "<<pos<<endl;*/
            	k[pos] = kk , b[pos] = bb;
            	return;
            }
            const int mid = ( l[pos] + r[pos] ) >> 1;
            if( kk > k[pos] ) {
                if( f(kk,bb,mid) > f(k[pos],b[pos],mid) ) {
                    update(lson[pos],l[pos],r[pos],k[pos],b[pos]);
                    k[pos] = kk , b[pos] = bb;
                }
                else
                    update(rson[pos],l[pos],r[pos],kk,bb);
            }
            else {
                if( f(kk,bb,mid) > f(k[pos],b[pos],mid) ) {
                    update(rson[pos],l[pos],r[pos],k[pos],b[pos]);
                    k[pos] = kk , b[pos] = bb;
                }
                else
                    update(lson[pos],l[pos],r[pos],kk,bb);
            }
        }
        update(lson[pos],ll,rr,kk,bb);
        update(rson[pos],ll,rr,kk,bb);
    }
    inline lli query(int pos,int tar) {
        lli ret = f(k[pos],b[pos],tar);
        /*debug<<"pos = "<<pos<<endl;
        debug<<"k = "<<k[pos]<<"b = "<<b[pos]<<"tar = "<<srt[tar]<<endl;
        debug<<"ret = "<<ret<<endl;*/
        if( l[pos] == r[pos] )
            return ret;
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( tar <= mid )
            ret = max( ret , query(lson[pos],tar) );
        else
            ret = max( ret , query(rson[pos],tar) );
        return ret;
    }
}up,down;
 
int s[maxn],st[maxq],ed[maxq];
lli k[maxq],b[maxq];
int ope[maxq][4];
int n,m,len=1,cnt;
int v[maxn];
 
inline lli getb(int pos,int tme,lli newk) {
    lli alpha = f(k[pos],b[pos],tme);
    return alpha - newk * srt[tme];
}
inline void add(int pos,int tt,lli kk,lli bb=0) {
    k[++cnt] = kk;
    if( !bb )
        bb = getb(s[pos],tt,kk);
    b[cnt] = bb;
    st[cnt] = tt , ed[cnt] = len;
    if( s[pos] )
        ed[s[pos]] = tt;
    s[pos] = cnt;
}
 
inline void init() {
    sort(srt+1,srt+1+len);
    //debug<<"len = "<<len<<endl;
    len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=m;i++)
        ope[i][1] = lower_bound(srt+1,srt+1+len,ope[i][1]) - srt;
    for(int i=1;i<=n;i++)
    	add(i,0,0,v[i]);
    for(int i=1;i<=m;i++)
        if( *ope[i] ) {
            add(ope[i][2],ope[i][1],ope[i][3]);
        }
     
    up.build(up.cnt=1,1,len);
    down.build(down.cnt=1,1,len);
     
    for(int i=1;i<=cnt;i++) {
    	//debug<<"st = "<<st[i]<<"ed = "<<ed[i]<<endl;
        up.update(1,st[i],ed[i],k[i],b[i]);
        down.update(1,st[i],ed[i],-k[i],-b[i]);
        //debug<<"this - = "<<-k[i]*10-b[i]<<endl;
    }
}
 
inline void work() {
    static lli ans;
    for(int i=1;i<=m;i++)
        if( ! *ope[i] ) {
            ans = max( up.query(1,ope[i][1]) , down.query(1,ope[i][1]) );
            //debug<<"query down = "<<down.query(1,ope[i][1])<<endl;
            printf("%lld\n",ans);
        }
}
int main() {
	
    static char com[20];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",v+i);
    for(int i=1;i<=m;i++) {
        scanf("%d",&ope[i][1]);
        srt[++len] = ope[i][1];
        scanf("%s",com);
        if( *com == 'c' ) {
            ope[i][0] = 1;
            scanf("%d%d",&ope[i][2],&ope[i][3]);
        }
    }
    //debug<<"inputed"<<endl;
    init();
    work();
     
    return 0;
}
