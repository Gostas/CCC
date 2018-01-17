#include <cstring>
#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;

int dist[100000];
bool visit[100000];
list<int> sorted_vertices;

struct nodes
{
	int dest, w;
};

struct Graph
{
	int v;
	vector<vector<nodes>> adj;

	Graph(int V)
	{
		this->v = V;
		adj.resize(v + 10);
	}
};

void dfs_util(Graph g, int node)
{
	visit[node] = true;

	for (vector<nodes>::iterator i = g.adj[node].begin(); i != g.adj[node].end(); ++i)
	{
		if (!visit[(*i).dest])
			dfs_util(g, i->dest);
	}
	sorted_vertices.insert(sorted_vertices.begin(),node);
}

void dfs(Graph g)
{
	for (int i = 0; i<g.v; ++i)
	{
		if (!visit[i])
			dfs_util(g, i);
	}
}

void TopologicalSort(Graph g)
{
	dfs(g);
}

int main()
{
	int v, e, s, d;	//number of vertices, edges, starting node, destination node
	register int j, a, b, w;
	vector<nodes>::iterator k;

	ios::sync_with_stdio(false);

	cin >> v >> e >> s >> d;

	Graph g(v);

	for (int i = 0; i<e; ++i)
	{
		cin >> a >> b >> w;
		g.adj[a].push_back({ b,w });
	}

	TopologicalSort(g);

	memset(dist, INT_MAX+2, sizeof(dist));
	dist[s] = 0;

	for (int i = s + 1; i <= d; ++i)
	{
		for (j = s; j<i; ++j)
		{
			for (k = g.adj[j].begin(); k != g.adj[j].end(); ++k)
			{
				if (k->dest == i)
				{
					dist[i] = min(dist[i], dist[j] + k->w);
					break;
				}
			}
		}
	}
	cout << dist[d];

	return 0;
}