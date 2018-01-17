#include <iostream>
#include <vector>
using namespace std;

struct Edge
{
	int dest, w;
};

struct Graph
{
	int v;
	vector<vector<Edge>> adj;
	
	Graph(int V)
	{
		v=V;
		adj.resize(v);
	}
};

int findWeightOf(vector<Edge> s, int node)
{
	for(vector<Edge>::iterator i=s.begin();i!=s.end();++i)
	{
		if(i->dest==node)
			return i->w;
	}
}

int dp[1000][100000];

int main()
{
	register int i, j, a, w;
	vector<int>::iterator l;
	int v,e,k,s,t;
	Edge temp;

	ios::sync_with_stdio(false);
	cin>>v>>e>>k>>s>>t;

	vector<vector<int>>opp_adjNodes(v);

	Graph g(v);

	for(i=0;i<e;++i)
	{
		cin>>a>>temp.dest>>temp.w;
		g.adj[a].push_back(temp);
		opp_adjNodes[temp.dest].push_back(a);
	}
	
	for(i=0;i<g.v;++i)
		dp[0][i]=1e9;

	dp[0][s]=0;

	for(i=1;i<=k;++i)
	{
		for(j=0;j<v;++j)
		{
			if(j==s)
				continue;
			dp[i][j]=dp[i-1][j];

			for(l=opp_adjNodes[j].begin();l!=opp_adjNodes[j].end();++l)
				dp[i][j] = min(dp[i][j], dp[i-1][*l] + findWeightOf(g.adj[*l], j));
		}
	}

	cout<<dp[k][t];
	return 0;
}