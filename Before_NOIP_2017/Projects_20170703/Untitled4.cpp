next_permutation

1 2 3 4 5   dist
1 2 4 3 5
1 3 2 4 5
1 3 4 2 5
1 4 2 3 5
1 4 3 2 5
....

1 5

Hamilton

O(n!)



DFS  O(n!)

current position   [N]
visited   N bits     (x>>i&1)==1
                               0 not visited
        
                       

memset(f, 0x3f, sizeof(f));
f[1][1] = 0;               
for (int x=2; x<(1<<n)-1; x++)  // n bits
	for (int p=1; p <= n; p++)
		if (x>>(p-1)&1) {
			for (int last=1;last<=n;last++)
				if (a[last][p]!=-1 && (x>>(last-1)&1)==1)
					f[x][p]=min(f[x][p],f[x^(1<<(p-1))][last]+a[last][p]);
		}
f[(1<<n)-1][n];

! ~
*/	
+-
<< >>
== < > !=
& &&
|
^

cout << (x>>1) << endl; 


set<pair<int,int> > hs;
for (int i=n;i;i--) {
	hs.insert(make_pair(h[i],i));
	set<int>::iterator p=hs.find(make_pair(h[i],i)), q=p;
	p++;
	q--;
	if (p->first-h[i] < h[i]-q->first) b[i]=p->second; else b[i]=q->second;
	set<int>::iterator u=p,v=q;
	u++,v--;
	// p q u v 
	// a[i]
}


f[i][j][k=0/1]  drive 2^i days from city j (k xian kai che)      arrives at ?
f[0][j][0]=a[j];
f[0][j][1]=b[j];
int t=log(n)/log(2);


for (int i=1;i<=t;i++)
	for(int j=1;j<=n;j++)
		for (int k=0;k<2;k++) { 
			f[i][j][k]=f[i-1][f[i-1][j][k]][i==1?k^1:k];
		}
		
		
da[i][j][k]   drive 2^i days from city j (k drives first)    how long does A drive?
db[i][j][k]                                                                B

da[0][j][0]=abs(h[a[j]]-h[j]),db[0][j][0]=0;
da[0][j][1]=0,db[0][j][1]=abs(h[b[j]]-h[j]);
for (int i=1;i<=t;i++)
	for(int j=1;j<=n;j++)
		for (int k=0;k<2;k++) { 
			da[i][j][k] = da[i-1][j][k] + da[i-1][f[i-1][j][k]][i==1?k^1:k];
			db[i][j][k] = db[i-1][j][k] + db[i-1][f[i-1][j][k]][i==1?k^1:k];
		}

calc(s,x) -> pair<int,int>  <la,lb>
int la=0,lb=0;
for (int i=t;i>=0;i--) {
	if(da[i][s][0]+db[i][s][0]<=x) {
		x-=da[i][s][0]+db[i][s][0];
		s=f[i][s][0];
		la+=da[i][s][0],lb+=db[i][s][0];
	}
}

13
1101
1000
 100
   1
   
   O(NlogN)

