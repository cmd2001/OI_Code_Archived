#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e4+1e2;

struct LCT {
	int ch[maxn][2],fa[maxn],rev[maxn],stk[maxn],top;
	
	inline void push(int pos) {
		if( rev[pos] ) {
			swap(ch[pos][0],ch[pos][1]);
			if( ch[pos][0] ) rev[ch[pos][0]] ^= 1;
			if( ch[pos][1] ) rev[ch[pos][1]] ^= 1;
			rev[pos] = 0;
		}
	}
	inline bool isrt(int pos) {
		return pos != ch[fa[pos]][0] && pos != ch[fa[pos]][1];
	}
	inline int getid(int pos) {
		return pos == ch[fa[pos]][1];
	}
	inline void rotate(int pos) {
		const int id = getid(pos) , f = fa[pos];
		fa[pos] = fa[f];
		if( !isrt(f) ) ch[fa[f]][getid(f)] = pos;
		ch[f][id] = ch[pos][id^1];
		if( ch[pos][id^1] ) fa[ch[pos][id^1]] = f;
		ch[pos][id^1] = f , fa[f] = pos;
	}
	inline void splay(int pos) {
		int i = pos;
		while( !isrt(i) )
			stk[++top] = i , i = fa[i];
		stk[++top] = i;
		while( top ) push(stk[top--]);
		while( !isrt(pos) ) {
			if( !isrt(fa[pos]) ) rotate(fa[pos]);
			rotate(pos);
		}
	}
	inline void access(int pos) {
		int t = 0;
		while( pos ) {
			splay(pos);
			ch[pos][1] = t , 
			t = pos ,
			pos = fa[pos];
		}
	}
	inline void makert(int pos) {
		access(pos) , splay(pos);
		rev[pos] ^= 1;
	}
	inline void link(int pos,int f) {
		makert(pos);
		fa[pos] = f;
		splay(pos);
	}
	inline void cut(int pos,int f) {
		makert(f);
		access(pos) , splay(pos);
		fa[f] = 0 , ch[pos][0] = 0;
	}
	inline int find(int x) {
		access(x) , splay(x);
		while( ch[x][0] ) x = ch[x][0];
		return x;
	}
	inline bool query(int x,int y) {
		return find(x) == find(y);
	}
}lct;

int main() {
	static int n,m;
	static char s[20];
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++) {
		scanf("%s%d%d",s,&x,&y);
		if( *s == 'Q' ) puts( lct.query(x,y) ? "Yes" : "No" );
		else if( *s == 'C' ) lct.link(x,y);
		else if( *s == 'D' ) lct.cut(x,y);
	}
	return 0;
}
