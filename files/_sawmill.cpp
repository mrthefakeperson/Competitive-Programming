#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
vector<int> sources[1000001];
int adj[1000001];
double ans[1000001];
int main()
{
	int n, m; scanf("%i %i", &n, &m);
	for (int e = 0; e < m; e++)
	{
		int a, b; scanf("%i %i", &a, &b);
		adj[a]++;
		sources[b].push_back(a);
	}
	ans[1] = 1.0;
	for (int e = 2; e <= n; e++)
	{
		double answer = 0.0;
		for (int ee = 0; ee < sources[e].size(); ee++)
		{
			answer+=(double)(ans[sources[e][ee]])/adj[sources[e][ee]];
		}
		ans[e] = answer;
		if (adj[e] == 0)
		{
			printf("%.9f\n", answer);
		}
		//printf("e:%i", e);
	}


	//scanf(" ");
}