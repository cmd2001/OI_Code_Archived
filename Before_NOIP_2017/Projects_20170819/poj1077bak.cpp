inline int zip(int f[5][5])
{
	static int tmp[15];
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			tmp[(i-1)*3+j]=f[i][j];
	int ret=0;
	for(int i=9;i;i--)
		ret=ret*10+tmp[i];
	return ret;
}
inline void unzip(int f[5][5],int sta)
{
	static int tmp[15];
	for(int i=1;i<=9;i++)
		tmp[i]=sta%10,sta/=10;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			f[i][j]=tmp[(i-1)*3+j];
}

inline int h(int sta)
{
	const int tarx={0,1,1,1,2,2,2,3,3,3},tary={0,1,2,3,1,2,3,1,2,3};
	static int t[5][5];
	unzip(t,sta);
	int ret=0;
	
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			ret+=abs(i-tx[t[i][j]])+abs(j-ty[t[i][j]]);
	
	return ret;
}
