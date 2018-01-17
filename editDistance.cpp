#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream in("strings.in");
	register int i, j, k;
	int t;
	int **edits;
	char c;

	vector<char>s1;
	vector<char>s2;

	ios::sync_with_stdio(false);

	in >> t;
	for (k = 0; k<t; ++k)
	{
		in >> c >> noskipws;
		while (c != '\n')
		{
			s1.push_back(c);
			in >> c;
		}

		while (in>>c && c!='\n')
			s2.push_back(c);

		edits = new int*[s1.size() + 1];

		for (i = 0; i <= s1.size(); ++i)
		{
			edits[i] = new int[s2.size() + 1];
			edits[i][0] = i;
		}

		for (i = 0; i <= s2.size(); ++i)
			edits[0][i] = i;

		for (i = 1; i <= s1.size(); ++i)
		{
			for (j = 1; j <= s2.size(); ++j)
			{
				if (s1[i - 1] == s2[j - 1])
					edits[i][j] = edits[i - 1][j - 1];
				else
					edits[i][j] = 1 + min(edits[i][j - 1], min(edits[i - 1][j - 1], edits[i - 1][j]));
			}
		}
		/*for (i = 0; i <= s1.size(); ++i)
		{
			for (j = 0; j <= s2.size(); ++j)
				cout << edits[i][j] << " ";
			cout << endl;
		}*/
		cout << edits[s1.size()][s2.size()] << "\n";
		delete[] edits;
		s1.erase(s1.begin(), s1.begin() + s1.size());
		s2.erase(s2.begin(), s2.begin() + s2.size());
	}

	in.close();

	return 0;
}