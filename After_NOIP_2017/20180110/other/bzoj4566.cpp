#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=4e5+1e2;

char in[maxn>>1];
int li,cnt;
lli ans;
struct Node {
    Node *fa,*ch[26];
    lli len,sizr,sum;
    int deg;
}ns[maxn],*last,*root;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns+cnt;
}
inline void extend(int x) {
    Node* p = last;
    Node* np = NewNode(p->len+1);
    np->sizr = 1;
    while( p && !p->ch[x] )
        p->ch[x] = np ,
        p = p->fa;
    if( !p )
        np->fa = root;
    else {
        Node* q = p-> ch[x];
        if( q->len == p->len + 1 )
            np->fa = q;
        else {
            Node* nq = NewNode(p->len+1);
            memcpy(nq->ch,q->ch,sizeof(q->ch));
            nq->fa = q->fa;
            q->fa = np->fa = nq;
            while( p && p->ch[x] == q )
                p->ch[x] = nq ,
                p = p->fa;
        }
    }
    last = np;
}
inline void topo() {
    for(int i=1;i<=cnt;i++)
        if( ns[i].fa )
            ++ns[i].fa->deg;
    queue<Node*> q;
    for(int i=1;i<=cnt;i++)
        if( !ns[i].deg )
            q.push(ns+i);
    while( q.size() ) {
        const Node* pos = q.front(); q.pop();
        if( pos == root )
            break;
        pos->fa->sizr += pos->sizr;
        //debug<<"pos = "<<pos-ns<<"sizr = "<<pos->sizr<<endl;
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
}
inline void getans() {
    Node* now = root;
    lli len = 0;
    for(int i=1;i<=li;i++) {
        const int t = in[i] - 'a';
        //debug<<"t = "<<t<<endl;
        if( now->ch[t] ) {
            now = now->ch[t] ,
            len++;
        }
        else {
            while( now && !now->ch[t] )
                now = now->fa;
            if( !now ) {
                now = root , 
                len = 0;
            }
            else {
                len = now->len + 1 , 
                now = now->ch[t];
            }
        }
        //debug<<"i = "<<i<<"len = "<<len<<endl;
        if( now->fa && min( len , now->len ) >= now->fa->len ) {
            ans += now->sizr * ( min( len , now->len ) - now->fa->len );
            ++now->fa->sum;
        }
    }
}
inline void calc() {
    for(int i=1;i<=cnt;i++)
        ns[i].deg = 0;
    for(int i=1;i<=cnt;i++)
        if( ns[i].fa )
            ++ns[i].fa->deg;
    queue<Node*> q;
    for(int i=1;i<=cnt;i++)
        if( !ns[i].deg )
            q.push(ns+i);
    while( q.size() ) {
        const Node* pos = q.front(); q.pop();
        if( pos == root )
            break;
        ans += pos->sizr * pos->sum * ( pos->len - pos->fa->len );
        pos->fa->sum += pos->sum;
        if( !--pos->fa->deg )
            q.push(pos->fa);
    }
}

int main() {
    scanf("%s",in+1);
    li = strlen(in+1);
    
    last = root = NewNode(0);
    for(int i=1;i<=li;i++)
        extend(in[i]-'a');
    //debug<<"cnt = "<<cnt<<endl;
    topo();
    
    scanf("%s",in+1);
    li = strlen(in+1);
    
    getans();
    calc();
    
    printf("%lld\n",ans);
    
    return 0;
}
