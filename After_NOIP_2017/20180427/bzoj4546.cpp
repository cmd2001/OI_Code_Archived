#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=5e5+1e2,maxe=1e7+1e2;

int root[maxn],remcnt[maxn],len;

struct PersistentTrie {
    int ch[maxe][2],sum[maxe],cnt;
    inline void insert(int &pos,int pre,int bit,const int &x) { // bit from 18 to 0;
        sum[pos=++cnt] = sum[pre] + 1;
        if( !~bit ) return;
        int ths = ( x >> bit ) & 1;
        insert(ch[pos][ths],ch[pre][ths],bit-1,x) , ch[pos][ths^1] = ch[pre][ths^1];
    }
    inline int mxxor(int pos,int pre,int bit,const int &ref) {
        if( !~bit ) return 0;
        int ths = ( ( ref >> bit ) & 1 ) ^ 1;
        if( sum[ch[pos][ths]] != sum[ch[pre][ths]] ) return mxxor(ch[pos][ths],ch[pre][ths],bit-1,ref) | ( 1 << bit );
        else return mxxor(ch[pos][ths^1],ch[pre][ths^1],bit-1,ref);
    }
    inline int getrnk(int pos,int pre,int bit,const int &ref) {
        if( !~bit ) return sum[pos] - sum[pre];
        int ths = ( ref >> bit ) & 1;
        if( ths ) return sum[ch[pos][0]] - sum[ch[pre][0]] + getrnk(ch[pos][1],ch[pre][1],bit-1,ref);
        else return getrnk(ch[pos][0],ch[pre][0],bit-1,ref);
    }
    inline int kth(int pos,int pre,int bit,int k) {
        if( !~bit ) return 0;
        if( k <= sum[ch[pos][0]] - sum[ch[pre][0]] ) return kth(ch[pos][0],ch[pre][0],bit-1,k);
        else return kth(ch[pos][1],ch[pre][1],bit-1,k-sum[ch[pos][0]]+sum[ch[pre][0]]) | ( 1 << bit );
    }
    inline void replace(int lastcnt) {
        memset(ch+lastcnt+1,0,sizeof(ch[0])*(cnt-lastcnt)) , memset(sum+lastcnt+1,0,sizeof(int)*(cnt-lastcnt)) , cnt = lastcnt;
    }
}pt;

int main() {
    static int q;
    scanf("%d",&q);
    for(int i=1,o,l,r,x,k;i<=q;i++) {
        scanf("%d",&o);
        if( o == 1 ) scanf("%d",&x) , ++len , pt.insert(root[len],root[len-1],18,x) , remcnt[len] = pt.cnt;
        else if( o == 2 ) scanf("%d%d%d",&l,&r,&x) , printf("%d\n",x^pt.mxxor(root[r],root[l-1],18,x));
        else if( o == 3 ) scanf("%d",&k) , len -= k , pt.replace(remcnt[len]);
        else if( o == 4 ) scanf("%d%d%d",&l,&r,&x) , printf("%d\n",pt.getrnk(root[r],root[l-1],18,x));
        else if( o == 5 ) scanf("%d%d%d",&l,&r,&k) , printf("%d\n",pt.kth(root[r],root[l-1],18,k));
    }
    return 0;
}

