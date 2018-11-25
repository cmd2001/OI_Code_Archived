#include<cstdio>
#include<cctype>
#include<queue>
typedef long long int lli;

std::priority_queue<lli> pq[2];

inline void popdual(std::priority_queue<lli> &pq,lli &mx,lli &sec) {
    mx = pq.top() , pq.pop() , sec = pq.top() , pq.push(mx);
}
inline bool work() {
    for(int cur=0;;cur^=1) {
        if( !pq[cur].size() ) return cur^1;
        else if( pq[cur].size() == 1 ) {
            if( pq[cur].top() < pq[cur^1].top() ) return cur ^ 1;
            else if( pq[cur].top() == pq[cur^1].top() && pq[cur^1].size() == 1 ) return 1;
            else pq[cur^1].pop();
        } else {
            lli mx,sec; popdual(pq[cur],mx,sec);
            if( pq[cur^1].size() == 1 ) pq[cur].pop() , pq[cur].pop() , pq[cur].push(mx+sec);
            else {
                lli nmx,nsec; popdual(pq[cur^1],nmx,nsec);
                if( mx <= nmx ) pq[cur].pop() , pq[cur].pop() , pq[cur].push(mx+sec);
                else {
                    if( mx + sec < nmx + nsec ) pq[cur^1].pop();
                    else pq[cur].pop() , pq[cur].pop() , pq[cur].push(mx+sec);
                }
            }
        }
    }
}

inline lli getint() {
    lli ret = 0;
    char ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int cse,n,m;
    while( scanf("%d%d",&n,&m) == 2 ) {
        while( pq[0].size() ) pq[0].pop();
        while( pq[1].size() ) pq[1].pop();
        while(n--) pq[0].push(getint());
        while(m--) pq[1].push(getint());
        printf("Case %d: %s\n",++cse,work()?"Buyout Limited":"Takeover Incorporated");
    }
    return 0;
}
