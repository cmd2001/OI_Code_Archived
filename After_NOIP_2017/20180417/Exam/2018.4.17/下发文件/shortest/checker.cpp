#include <map>
#include <set>
#include <list>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std ;
#define LS(t) ((t)<<1)
#define RS(t) (((t)<<1)+1)
#define MD(l,r) (((l)+(r))>>1)
#define PI 3.1415926535897932384626433832795
const int maxn = 10000 + 10 ;
const int maxm = 100000 + 10 ;
int N , M , K , T ;
int x[maxm] , y[maxm] , z[maxm] ;
int d[maxn] ;
vector < pair < int , int > > e[maxn] ;
bool b[maxm] ;
char tmp[maxn] ;
priority_queue < pair < int , int > > Heap ;

inline void Return( string s )
{
	cout << s << endl ;
	exit( 0 ) ;
}

int main( int argc, char *argv[] )
{
	if ( argc != 2 ) {
		Return( "Format error." ) ;
	}
	int num = 0 ;
	sscanf( argv[1] , "%d" , &num ) ;
	if ( num < 0 || num > 10 ) {
		Return( "Format error." ) ;
	}
	string inputFile = argv[1] ;
	string outputFile = argv[1] ;
	inputFile = "shortest" + inputFile + ".in" ;
	outputFile = "shortest" + outputFile + ".out" ;
	FILE *Fin = fopen( inputFile.c_str() , "r" ) ;
	FILE *Fout = fopen( outputFile.c_str() , "r" ) ;
	if ( Fin == NULL ) {
		Return( "The input file \"" + inputFile  + "\" does not exist." ) ;
		return 0 ;
	}
	if ( Fout == NULL ) {
		Return( "The output file \"" + outputFile  + "\" does not exist." ) ;
	}
	if ( fscanf( Fin , "%d%d%d" , &N , &M , &K ) == EOF ) {
		Return( "Input file is not correct." ) ;
	}
	for ( int i = 0 ; i < M ; i ++ ) {
		if ( fscanf( Fin , "%d%d%d" , &x[i] , &y[i] , &z[i] ) == EOF ) {
			Return( "Input file is not correct." ) ;
		}
		if ( x[i] < 1 || x[i] > N || y[i] < 1 || y[i] > N ) {
			Return( "Input file is not correct." ) ;
		}
	}
	if ( fscanf( Fout , "%d" , &T ) == EOF ) {
		Return( "Output file is not correct." ) ;
	}
	if ( T > K ) {
		Return( "You delete too many edges." ) ;
	}
	for ( int i = 0 , k ; i < T ; i ++ ) {
		if ( fscanf( Fout , "%d" , &k ) == EOF ) {
			Return( "Output file is not correct." ) ;
		}
		if ( k < 1 || k > M ) {
			sprintf( tmp , "%d" , k ) ;
			string ss = tmp ;
			ss = "Edge " + ss + " does not exist." ;
			Return( ss ) ;
		}
		if ( b[k] ) {
			sprintf( tmp , "%d" , k ) ;
			string ss = tmp ;
			ss = "Edge " + ss + " is deleted twice or more." ;
			Return( ss ) ;
		}
		b[k] = true ;
	}
	for ( int i = 0 ; i < M ; i ++ )
	if ( !b[i+1] ) {
		e[x[i]].push_back( make_pair( y[i] , z[i] ) ) ;
		e[y[i]].push_back( make_pair( x[i] , z[i] ) ) ;
	}
	memset( d , 63 , sizeof( d ) ) ;
	d[1] = 0 ;
	Heap.push( make_pair( 0 , 1 ) ) ;
	while ( !Heap.empty() ) {
		int u = Heap.top().second ;
		int dis = -Heap.top().first ;
		Heap.pop() ;
		if ( dis > d[u] ) {
			continue ;
		}
		for ( int i = 0 ; i < e[u].size() ; i ++ )
		if ( dis + e[u][i].second < d[e[u][i].first] ) {
			int v = e[u][i].first ;
			d[v] = dis + e[u][i].second ;
			Heap.push( make_pair( -d[v] , v ) ) ;
		}
	}
	if ( d[N] > 1000000000 ) {
		sprintf( tmp , "%d" , N ) ;
		string ss = tmp ;
		Return( "There is no path from 1 to " + ss + "." ) ;
	}
	sprintf( tmp , "%d" , N ) ;
	string ss1 = tmp ;
	sprintf( tmp , "%d" , d[N] ) ;
	string ss2 = tmp ;
	Return( "Correct! The shortest distance is " + ss2 + "." ) ;
	return 0;
}
