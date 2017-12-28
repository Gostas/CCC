#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct Edge
{
	int src, dst;
};

struct Graph
{
	int v, e;
	Edge *edges;
};

struct Subset
{
	int par, rank;
};

Graph CreateGraph(int V, int E)
{
	Graph newGraph;

	newGraph.v=V;
	newGraph.e=E;

	newGraph.edges=new Edge[E];

	return newGraph;
}

/*int find(Subset subs[], int x)
{
	if(subs[x].par==x)
		return subs[x].par;

	subs[x].par = find(subs,subs[x].par);
	return subs[x].par;
}*/

int find(Subset subs[], int x)
{
    if (subs[x].par != x)
        subs[x].par = find(subs, subs[x].par);
 
    return subs[x].par;
}
 

void Union(Subset subs[], int x, int y)
{
	register int xroot, yroot;

	xroot = find(subs, x);
	yroot = find(subs, y);

	if(subs[xroot].rank>subs[yroot].rank)
		subs[yroot].par = xroot;

	else if(subs[yroot].rank>subs[xroot].rank)
		subs[xroot].rank=yroot;
	else
	{
		subs[xroot].rank++;
		subs[yroot].par=xroot;
	}
}

bool isCycle(Graph graph)
{
	Subset *subs = new Subset[graph.v];
	register int x,y;
	
	for(int i=0;i<graph.v;++i)
	{
		subs[i].rank=0;
		subs[i].par=i;
	}

	for(int i=0;i<graph.e;++i)
	{
		x=find(subs, graph.edges[i].src);
		y=find(subs, graph.edges[i].dst);
		
		if(x==y)
			return true;
		Union(subs,x,y);

	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	
	ifstream in("edgesNoWeights.in");
	ofstream out("edgesNoWeights.out");

	Graph graph;
	int v,e;

	in>>v>>e;
	
	graph=CreateGraph(v,e);
	
	for(int i=0;i<e;++i)
		in>>graph.edges[i].src>>graph.edges[i].dst;
	if(isCycle(graph))
		out<<"The graph contains a cycle.";
	else
		out<<"The graph does not contain a cycle.";

	in.close();
	out.close();

	return 0;
}
	