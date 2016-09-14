#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;
vector<int> adj[4005];
bool adj2[4005][4005];
int recog[4005];
int runningMin = -1;
int main()
{
	int n, m; scanf("%i%i", &n, &m);
	for (int e = 0; e < m; e++)
	{
		int a, b; scanf("%i%i", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
		adj2[a][b] = true;
		adj2[b][a] = true;
		recog[a]++;
		recog[b]++;
	}/*
	for (int e = 1; e <= n; e++)
	{
		printf("%i:%i\n", e, recog[e]);
	}
	*/
	for (int e = 1; e <= n; e++)
	{
		for (int ee = 0; ee < adj[e].size(); ee++)
		{
			for (int eee = ee + 1; eee < adj[e].size(); eee++)
			{
				int newMin=0;
				if (adj2[adj[e][ee]][adj[e][eee]]){
					//printf("%i,%i,%i\n", e, adj[e][ee], adj[e][eee]);
					newMin += recog[e] - 2;
					newMin += recog[adj[e][ee]] - 2;
					newMin += recog[adj[e][eee]] - 2;
					if (runningMin == -1) runningMin = newMin;
					else runningMin = min(runningMin, newMin);
				}
			}
		}
	}
	printf("%i\n", runningMin);

	//scanf(" ");

	return 0;
}