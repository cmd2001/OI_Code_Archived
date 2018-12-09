#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define debug cerr
using namespace std;
const int maxn = 1e6 + 1e2;
const double alpha = 0.80;

char in[maxn];

class SuffixBalancedTree { // compare prefix.
private:
    int lson[maxn],rson[maxn],siz[maxn],nv[maxn],rec[maxn],cnt,seq[maxn],root,sql,fail,*failfa;
    double val[maxn],fl,fr;
    int sa[maxn],sal;
    inline bool cmp(const int &x,const int &y) {
        assert(x && y);
        if(in[x] != in[y]) return in[x] < in[y];
        return val[rec[x-1]] < val[rec[y-1]];
    }
    inline void maintain(const int &pos,const double &ll,const double &rr) {
        siz[pos] = siz[lson[pos]] + siz[rson[pos]] + 1;
        if(max(siz[lson[pos]],siz[rson[pos]]) > siz[pos] * alpha) fail = pos, failfa = &root, fl = ll, fr = rr;
        else if(fail == lson[pos] || fail == rson[pos]) failfa = (fail == lson[pos] ? lson : rson) + pos;
    }
    inline void insert(int &pos,const double &ll,const double &rr,const int &id) {
        if(!pos) {
            val[pos=++cnt] = (ll + rr) / 2.0, siz[rec[nv[pos]=id]=pos] = 1;
            return;
        } const double mm = (ll + rr) / 2.0;
        cmp(id,nv[pos]) ? insert(lson[pos],ll,mm,id) : insert(rson[pos],mm,rr,id);
        maintain(pos,ll,rr);
    }
    inline void recycle(const int &pos) {
        if(!pos) return;
        recycle(lson[pos]), seq[++sql] = pos, recycle(rson[pos]);
        lson[pos] = rson[pos] = 0;
    }
    inline int rebuild(const int &l,const int &r,const double &ll,const double &rr) {
        const int mid = (l + r) >> 1, pos = seq[mid];
        const double vmid = (ll + rr) / 2.0; val[pos] = vmid, siz[pos] = r - l + 1;
        if(l < mid) lson[pos] = rebuild(l,mid-1,ll,vmid);
        if(mid < r) rson[pos] = rebuild(mid+1,r,vmid,rr);
        return pos;
    }
    inline void gsa(const int &pos,const int &len) {
        if(!pos) return;
        //debug<<"pos = "<<pos<<"lson = "<<lson[pos]<<"rson = "<<rson[pos]<<endl;
        gsa(lson[pos],len), sa[++sal] = len - nv[pos] + 1, gsa(rson[pos],len);
    }
public:
    inline void insert(const int &id) {
        fail = -1, failfa = NULL;
        insert(root,0.0,1.0,id);
        if(~fail) sql = 0, recycle(fail), *failfa = rebuild(1,sql,fl,fr);
        //debug<<"id = "<<id<<" "<<lson[1]<<" "<<rson[1]<<endl;
    }
    inline void gsa(int n) {
        gsa(root,n);
    }
    const int& operator [] (const int &x) const {
        return sa[x];
    }
}sbt;

int main() {
    static int li;
    scanf("%s",in+1), reverse(in+1,in+1+(li=strlen(in+1)));
    for(int i=1;i<=li;i++) sbt.insert(i);
    sbt.gsa(li);
    for(int i=1;i<=li;i++) printf("%d%c",sbt[i],"\n "[i!=li]);
    return 0;
}

