#include<cstdio>
#include<cstring>
typedef long long int lli;
const int maxn=1e5+1e2;

struct Node {
    int val,*dst;
    Node() {}
    Node(int &x) { val = x , dst = &x; }
    inline void work() { *dst = val; }
}rs[maxn<<5];
int top;

struct SuffixAutomatic {
    int ch[maxn<<1][26],fa[maxn<<1],len[maxn<<1],cnt,root,last;
    SuffixAutomatic() { last = root = cnt = 1; }
    inline int NewNode(int ll) {
        return len[++cnt] = ll , memset(ch[cnt],0,sizeof(ch[cnt])) , cnt;
    }
    inline int extend(int x) {
        rs[++top] = Node(cnt) , rs[++top] = Node(last);
        int p = last , np = NewNode(len[p]+1);
        while( p && !ch[p][x] ) rs[++top] = Node(ch[p][x]) , ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q])) , fa[nq] = fa[q] ,
                rs[++top] = Node(fa[q]) , fa[q] = fa[np] = nq;
                while( p && ch[p][x] == q ) rs[++top] = Node(ch[p][x]) , ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
        return len[np] - len[fa[np]];
    }
}sam;

char in[maxn];
int li;
lli ans;

struct Stack {
    int top[maxn],ttop;
    lli ans[maxn];
    inline void push() {
        top[++ttop] = ::top , ans[ttop] = ::ans;
    }
    inline void pop() {
        while( ::top > top[ttop] ) rs[::top--].work();
        ::ans = ans[ttop--];
    }
}stk;


int main() {
    scanf("%s",in+1) , li = strlen(in+1);
    for(int i=1;i<=li;i++) {
        if( in[i] == '-' ) stk.pop();
        else stk.push() , ans += sam.extend(in[i]-'a');
        printf("%lld\n",ans);
    }
    return 0;
}
