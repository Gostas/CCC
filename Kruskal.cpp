#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

struct Edge
{
	int src, dest, w;
};

bool comp(Edge a, Edge b) { return a.w < b.w; }

struct Subset
{
	int rank, par;
};

struct Graph
{
	int V, E;
	Edge *edges;

	//vector<Edge>edges;

	Graph(int v, int e)
	{
		this->V = v;
		this->E = e;
		//edges.resize(e);
		this->edges = new Edge[e];	
	}
};


int find(Subset sub[], int x)
{
	if (sub[x].par != x)
		sub[x].par = find(sub, sub[x].par);

	return sub[x].par;
}


void Union(Subset subs[], int x, int y)
{
	register int xroot, yroot;

	xroot = find(subs, x);
	yroot = find(subs, y);

	if (subs[xroot].rank > subs[yroot].rank)
		subs[yroot].par = xroot;

	else if (subs[xroot].rank < subs[yroot].rank)
		subs[xroot].par = yroot;

	else
	{
		subs[xroot].rank++;
		subs[yroot].par = xroot;
	}
}

vector<Edge> KruskalMST(Graph graph)
{
	Subset *subs = new Subset[graph.V];
	vector<Edge> mst;

	register int xroot, yroot;
	int i, e;

	for (i = 0; i < graph.V; ++i)
	{
		subs[i].rank = 0;
		subs[i].par = i;
	}


	//sort(graph.edges.begin(), graph.edges.end(), comp);
	sort(graph.edges,graph.edges+graph.E,comp);	

	//for(i=0;i<graph.E;++i)
	//	cout << graph.edges[i].src << " " << graph.edges[i].dest << " " << graph.edges[i].w << "\n";
	e = 0;
	i = 0;

	while (e < graph.V - 1)
	{
		xroot = find(subs, graph.edges[i].src);
		yroot = find(subs, graph.edges[i].dest);

		if (xroot != yroot)
		{
			mst.push_back(graph.edges[i]);
			Union(subs, xroot, yroot);
			e++;
		}
		i++;
	}

	return mst;
}

int main()
{
	ios::sync_with_stdio(false);

	ifstream in("kruskal.in");
	ofstream out("kruskal.out");

	vector<Edge> mst;

	int v, e, total_weight = 0;

	in >> v >> e;

	Graph graph(v, e);

	for (int i = 0; i < e; ++i)
		in >> graph.edges[i].src >> graph.edges[i].dest >> graph.edges[i].w;

	mst = KruskalMST(graph);

	for (vector<Edge>::iterator it = mst.begin(); it != mst.end(); ++it)
	{
		out << it->src << " " << it->dest << " " << it->w << "\n";
		total_weight += it->w;
	}

	out << "Total minimum spanning tree weight is " << total_weight << ".";

	in.close();
	out.close();
	return 0;
}