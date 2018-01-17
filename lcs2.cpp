#include <iostream>

using namespace std;

int lcs[2][50010];
int main()
{

	string s1, s2;
	register int i,j, k, b;

	ios::sync_with_stdio(false);

	cin>>s1>>s2;
	
	for (i = 1; i <= s1.length(); ++i)
	{
		k=i%2;
		if(k==0)
			b=1;
		else
			b=0;
		for (j = 1; j <= s2.length(); ++j)
		{
			if (s1[i - 1] == s2[j - 1])
				lcs[k][j] = lcs[b][j - 1] + 1;

			else
				lcs[k][j] = max(lcs[b][j], lcs[k][j - 1]);
		}
	}
	
	cout<<lcs[s1.length()][s2.length()];

	return 0;
}
	