#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=1e3+1e2;

vector<int> poss;
int in[maxn],srt[maxn];
int n,m,cnt,ans;

struct BinaryIndexTree {
    int dat[maxn];
    
    #define lowbit(x) (x&-x)
    
    inline void update(int pos,int x) {
        while( pos <= n )
            dat[pos] += x,
            pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos )
            ret += dat[pos],
            pos -= lowbit(pos);
        return ret;
    }
    inline void reset() {
        memset(dat,0,sizeof(dat));
    }
}bit;

inline void getposs(int fst) {
    poss.clear();
    poss.push_back(fst);
    for(int i=fst+1;i<=n;i++)
        if( in[i] < in[fst] )
            poss.push_back(i);
}
inline void replac() {
    static vector<int> nums;
    nums.clear();
    for(unsigned i=0;i<poss.size();i++)
        nums.push_back(in[poss[i]]);
    sort(nums.begin(),nums.end());
    for(unsigned i=0;i<poss.size();i++)
        in[poss[i]] = nums[i];
}
inline int calc() {
    int ret = 0;
    for(int i=1;i<=n;i++) {
        ret += bit.query(n) - bit.query(in[i]);
        bit.update(in[i],1);
    }
    return ret;
}
inline void work(int pos) {
    getposs(pos);
    replac();
    bit.reset();
    ans = calc();
}

inline void init() {
    memcpy(srt,in,sizeof(in));
    cnt = n;
    sort(srt+1,srt+1+cnt);
    cnt = unique(srt+1,srt+1+cnt) - srt - 1;
    for(int i=1;i<=n;i++)
        in[i] = lower_bound(srt+1,srt+1+cnt,in[i]) - srt;
    
    for(int i=1;i<=n;i++)
        poss.push_back(i);
    ans = calc();
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    init();
    
    printf("%d\n",ans);
    for(int j=1,p;j<=m;j++) {
        scanf("%d",&p);
        work(p);
        printf("%d\n",ans);
    }
    
    return 0;
}