#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define uint unsigned int
#define debug cout
using namespace std;
const int maxn=35;

uint ans,x,y,z,k;

int main()
{
	while(scanf("%u%u%u",&x,&y,&z)==3)
	{
		ans=0;
		k=(y-x)/z;
		
		
