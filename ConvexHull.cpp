#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point
{
	int x,y;
};

bool comp(Point a, Point b)
{
	int det;
	
	det=a.x*b.y-b.x*a.y;

	if(det>=0)
		return true;
	else
		return false;
}

int find(vector<Point> p)	//returns position of element with smallest y
{
	Point minm;
	int j=0;

	minm.y=1e9;

	for(int i=0;i<p.size();++i)
	{		
		if(p[i].y<minm.y)
		{	j=i;
			minm.y=p[i].y;
		}
	}	

	return j;
}

int CompLineSegm(Point a1, Point a2, Point b)
{
	int det;

	a2.y -= a1.y;	//move line segment a1a2 so a1 is at (0,0)
	a2.x -= a1.x;

	b.y -= a1.y;	//move point b by same value as a2 so we can compare them
	b.x -= a1.x;

	// p1*p2 = x1*y2 - x2*y1

	det = a2.x*b.y - b.x*a2.y;
	
	if(det==0)
		return 0;
	else if(det<0)
		return -1;
	else
		return 1;
}


int main()
{
	int N,minm;
	Point inp,a,b;
	vector<Point> points;
	vector<Point> s;	//the stack

	cin>>N;
	
	for(int i = 0; i < N; ++i)
	{
		cin>>inp.x>>inp.y;
		points.push_back(inp);
	}
	
	minm=find(points);

	swap(points[minm],points[0]);
	
	sort(points.begin()+1,points.end(),comp);

	//for(int i=0;i<N;++i)
	//	cout<<points[i].x<<","<<points[i].y<<endl;
	

	s.push_back(points[0]);
	s.push_back(points[1]);
	s.push_back(points[2]);	

	for(int i=3;i<points.size();++i)
	{
		a=s[s.size()-1];
		b=s[s.size()-2];
		while(CompLineSegm(b,a,points[i])<=0)
		{			
			s.pop_back();
			a=s[s.size()-1];
			b=s[s.size()-2];
		}

		s.push_back(points[i]);
	}

	cout<<"Convex hull:\n";
	for(int i=0;i<s.size();++i)
		cout<<"\t"<<s[i].x<<","<<s[i].y<<endl;	
	return 0;
}