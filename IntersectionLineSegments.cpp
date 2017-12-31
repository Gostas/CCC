#include <iostream>
#include <algorithm>
using namespace std;

struct Point
{
	int x, y;
};

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

	Point p1, p2, p3, p4;
	int res1, res2;
	bool intersect = false;

	cout<<"Enter first line segment (x1, y1) & (x2, y2)\n";
	cin>>p1.x>>p1.y>>p2.x>>p2.y;

	
	cout<<"Enter second line segment (x3, y3) & (x4, y4)\n";
	cin>>p3.x>>p3.y>>p4.x>>p4.y;
	
	res1=CompLineSegm(p1,p2,p3);
	res2=CompLineSegm(p1,p2,p4);

	if(max(p1.x,p2.x) >= min(p3.x,p4.x) && max(p3.x,p4.x) >= min(p1.x,p2.x) && max(p1.y,p2.y) >= min(p3.y,p4.y) && max(p3.y,p4.y) >= min(p1.y,p2.y))
	{	//check if boxes intersect

		if(res1!=res2 || (res1==0 && res2 == 0))
		{	
			res1=CompLineSegm(p3,p4,p1);
			res2=CompLineSegm(p3,p4,p2);
	
			if(res1!=res2 || (res1==0 && res2 == 0)) 
			{
				cout<<"Line segments ("<<p1.x<<", "<<p1.y<<"), ("<<p2.x<<", "<<p2.y<<") and ";
				cout<<"("<<p3.x<<", "<<p3.y<<"), ("<<p4.x<<", "<<p4.y<<") intersect.\n";
				intersect = true;
			}
 		}
	}

	if(!intersect)
	{
		cout<<"Line segments ("<<p1.x<<", "<<p1.y<<"), ("<<p2.x<<", "<<p2.y<<") and ";
		cout<<"("<<p3.x<<", "<<p3.y<<"), ("<<p4.x<<", "<<p4.y<<") do not intersect.\n";
	}	
		

	return 0;
}
	