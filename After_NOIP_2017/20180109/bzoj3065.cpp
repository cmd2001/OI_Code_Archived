#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxs=130,maxb=1220,blk=600;

int sou[maxs][maxb],rt[maxs][maxb],nxt[maxs],siz[maxs],sc;
int n,m,lastp,used,lastans;

inline void cpy(int* dst,int *sou,int len) {
    int ite = ( len + 7 ) >> 3;
    switch( len & 7 ) {
        case 0: do{ *dst++ = *sou++;
        case 1: *dst++ = *sou++;
        case 2: *dst++ = *sou++;
        case 3: *dst++ = *sou++;
        case 4: *dst++ = *sou++;
        case 5: *dst++ = *sou++;
        case 6: *dst++ = *sou++;
        case 7: *dst++ = *sou++; }while(ite--);
    }
}

inline void reb(int id) {
    cpy(rt[id]+1,sou[id]+1,siz[id]);
    sort(rt[id]+1,rt[id]+1+siz[id]);
}

inline void getp(int k,int& rb,int& rk) {
    rb = 1 , rk = k;
    while( rk > siz[rb] && nxt[rb] ) {
        rk -= siz[rb] , 
        rb = nxt[rb];
    }
}

inline int bin(int id,int k) { // returning the number of elements which < k in block id.
    /*int ret = 0;
    for(int i=1;i<=siz[id];i++)
        ret += ( rt[id][i] < k );
    return ret;*/
    return lower_bound(rt[id]+1,rt[id]+1+siz[id],k) - rt[id] - 1;
}
inline int cont(int id,int l,int r,int k) { // returning the number of elements which < k in block id's range[l,r].
    int ret = 0;
    for(int i=l;i<=r;i++)
        ret += ( sou[id][i] < k );
    //debug<<"id = "<<id<<"l = "<<l<<"r = "<<r<<"k = "<<k<<"ret = "<<ret<<endl;
    return ret;
}

inline int kth(int l,int r,int k) {
    int lb,lpp,rb,rpp;
    getp(l,lb,lpp) , getp(r,rb,rpp);
    //debug<<"lb = "<<lb<<"rb = "<<rb<<endl;
    //debug<<"k = "<<k<<endl;
    int ll = -1 , rr = 70001 , mid , lam;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1 , lam = 0;
        if( lb == rb )
            lam = cont(lb,lpp,rpp,mid);
        else {
            lam = cont(lb,lpp,siz[lb],mid) + cont(rb,1,rpp,mid);
            for(int pos=nxt[lb];pos!=rb;pos=nxt[pos])
                lam += bin(pos,mid);
        }
        //debug<<"ll = "<<ll<<"rr = "<<rr<<"mid = "<<mid<<"lam = "<<lam<<endl;
        if( lam < k )
            ll = mid;
        else
            rr = mid;
    }
    //debug<<"ll = "<<ll<<"rr = "<<rr<<endl;
    return ll;
}
inline void upd(int tar,int nv) {
    int b,pp;
    getp(tar,b,pp);
    int i;
    for(i=1;rt[b][i]!=sou[b][pp];i++) ;
    sou[b][pp] = rt[b][i] = nv;
    while( i < siz[b] && rt[b][i] > rt[b][i+1] )
        swap(rt[b][i],rt[b][i+1]) , ++i;
    while( i > 1 && rt[b][i] < rt[b][i-1] )
        swap(rt[b][i],rt[b][i-1]) , --i;
}
inline void ins(int tar,int nv) {
    //debug<<"tar = "<<tar<<"nv = "<<nv<<endl;
    int b,pp;
    getp(tar,b,pp);
    //debug<<"b = "<<b<<"pp = "<<pp<<endl;
    for(int i=siz[b]+1;i>pp;i--)
        sou[b][i] = sou[b][i-1];
    rt[b][++siz[b]] = sou[b][pp] = nv;
    for(int i=siz[b]; i > 1 && rt[b][i] < rt[b][i-1] ;i--)
        swap(rt[b][i],rt[b][i-1]);
    if( siz[b] >= ( blk << 1 ) ) {
        //debug<<"Newing New Block"<<endl;
        nxt[++sc] = nxt[b] ,
        nxt[b] = sc;
        for(int i=1;i<=blk;i++)
            sou[sc][i] = sou[b][i+blk] ,
            sou[b][i+blk] = rt[b][i+blk] = 0;
        siz[b] = siz[sc] = blk;
        reb(b) , reb(sc);
    }
}

inline void print() {
    /*for(int i=1;i<=sc;i++) {
        debug<<"siz = "<<siz[i]<<"next = "<<nxt[i]<<endl;
        debug<<"unsorted :: ";for(int j=1;j<=siz[i];j++) debug<<sou[i][j]<<" ";debug<<endl;
        debug<<"sorted :: ";for(int j=1;j<=siz[i];j++) debug<<rt[i][j]<<" ";debug<<endl;
    }*/
    for(int i=1;i;i=nxt[i]) {
        for(int j=1;j<=siz[i];j++) debug<<sou[i][j]<<" ";
    }
    debug<<endl;
}
inline void printfull() {
    for(int i=1;i<=sc;i++) {
        debug<<"siz = "<<siz[i]<<"next = "<<nxt[i]<<endl;
        debug<<"unsorted :: ";for(int j=1;j<=siz[i];j++) debug<<sou[i][j]<<" ";debug<<endl;
        debug<<"sorted :: ";for(int j=1;j<=siz[i];j++) debug<<rt[i][j]<<" ";debug<<endl;
    }
}
int main() {
    freopen("exp.txt","w",stdout);
    static char com[10];
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        if( used < i ) {
            lastp = used , used = min( used + blk , n );
            siz[++sc] = used - lastp;
            if( sc != 1 )
                nxt[sc-1] = sc;
        }
        scanf("%d",&sou[sc][i-lastp]);
    }
    for(int i=1;i<=sc;i++)
        reb(i);
    scanf("%d",&m);
    for(int i=1,l,r,k,u,p;i<=m;i++) {
        scanf("%s",com);
        if( *com == 'I' ) {
            scanf("%d%d",&p,&u);
            p ^= lastans , u ^= lastans;
            ins(p,u);
        }
        else if( *com == 'M' ) {
            scanf("%d%d",&p,&u);
            p ^= lastans , u ^= lastans;
            upd(p,u);
        }
        else if( *com == 'Q' ) {
            scanf("%d%d%d",&l,&r,&k);
            l ^= lastans , r ^= lastans , k ^= lastans;
            printf("%d\n",lastans=kth(l,r,k));
        }
        /*print();
        if( i == 16 )
            printfull();*/
    }
    
    return 0;
}

