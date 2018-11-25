		for(int j=1;j<=m;j++)
		{
			if(j+down[i]<=m)
			{
				if(dp[i][j]>dp[i-1][j+down[i]]) dp[i][j]=dp[i-1][j+down[i]],vis[i][j]=1;
			}
			if(j-up[i]>0)
			{
				if(dp[i][j]>=dp[i-1][j-up[i]]+1) dp[i][j]=dp[i-1][j-up[i]]+1,vis[i][j]=0;
				if(dp[i][j]>=dp[i][j-up[i]]+1&&!dp[i][j-up[i]]) dp[i][j]=dp[i][j-up[i]]+1,vis[i][j]=0;
			}
		}
		
		if(tb[at+1].pos==i)
		{
			at++;
			for(int j=1;j<=tb[at].l;j++) dp[i][j]=inf,vis[i][j]=0;
			for(int j=tb[at].h;j<=m;j++) dp[i][j]=inf,vis[i][j]=0;
		}
		for(int j=1;j<=m;j++) printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
		
		
		
		
		for(int j=1;j<=m;j++) dp[(i+1)%2][j]=inf;
		for(int j=1;j<=m;j++)
		{
			if(j-down[i+1]>0&&dp[(i+1)%2][j-down[i+1]]>dp[i%2][j]) dp[(i+1)%2][j-down[i+1]]=dp[i%2][j],vis[(i+1)%2][j-down[i+1]]=1;
			if(dp[i%2][j+up[i]]>=dp[i%2][j]+1&&dp[i%2][j+up[i]]!=uaf&&!vis[i%2][j]) dp[i%2][j+up[i]]=dp[i%2][j]+1,vis[i%2][j+up[i]]=0;
			if(dp[(i+1)%2][min(j+up[i+1],m)]>=dp[i%2][j]+1) dp[(i+1)%2][min(j+up[i+1],m)]=dp[i%2][j]+1,vis[(i+1)%2][min(j+up[i+1],m)]=0;
		}
		if(tb[at+1].pos==i+1)
		{
			at++;
			for(int j=1;j<=tb[at].l;j++) dp[(i+1)%2][j]=uaf,vis[(i+1)%2][j]=0;
			for(int j=tb[at].h;j<=m;j++) dp[(i+1)%2][j]=uaf,vis[(i+1)%2][j]=0;
		}
		for(int j=1;j<=m;j++) if(dp[i%2][j]<inf) {lastdis=at-1;break;}
		for(int j=1;j<=m;j++) vis[i%2][j]=0;
		
			/*for(int i=0;i<n;i++)
	{
		const int now=i&1,next=(i+1)&1;
		for(int j=1;j<=m;j++) dp[next][j]=low[next][j]=inf;
		for(int j=1;j<=m;j++)
		{
			if(j+up[i]<=m) dp[now][j+up[i]]=min(dp[now],)
	}*/
