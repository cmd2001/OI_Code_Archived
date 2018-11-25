#include<cstdio>
#include<set>
using namespace std;

struct Node {
    int l,r;
    friend bool operator < (const Node &a,const Node &b) {
        return a.l != b.l ? a.l < b.l : a.r < b.r;
    }
}now;
set<Node> st;

int main() {
    static char o[10];
    static int n;
    scanf("%d",&n);
    for(int i=1,l,r,t;i<=n;i++) {
        scanf("%s",o) , t = 0;
        if( *o == 'B' ) printf("%u\n",(unsigned)st.size());
        else if( *o == 'A' ) {
            scanf("%d%d",&l,&r) , now = (Node){l,r};
            while( st.size() ) {
                set<Node>::iterator it = st.lower_bound(now);
                if( it != st.end() ) {
                    if( ! ( it->r < l || r < it->l ) ) {
                        st.erase(it) , ++t;
                        continue;
                    }
                }
                if( it != st.begin() ) {
                    --it;
                    if( ! ( it->r < l || r < it->l ) ) {
                        st.erase(it) , ++t;
                        continue;
                    }
                }
                break;
            }
            st.insert(now) , printf("%d\n",t);
        }
    }
    return 0;
}
