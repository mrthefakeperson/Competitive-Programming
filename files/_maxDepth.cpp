#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#define fst first
#define snd second
using namespace std;

vector<int> adj[500001];
int visitDepth[500001]; bool visited[500001];
pair<int, int> maxSndMax[500001];
int ans[500001];

int fillDepth(int node)
{
	int acc = 0;
	visited[node] = true;
	if (adj[node].size() == 1 && visited[adj[node][0]]){
		visitDepth[node] = 1;
		return 1;
	}
	else{
		for (int dest : adj[node])
		{
			if (!visited[dest]){
				acc = max(acc, fillDepth(dest));
			}
		}
		visitDepth[node] = acc + 1;
		return acc + 1;
	}
}
void rotateTree(int node)
{
	int mxx = 0, sndmxx = 0; visited[node] = false;
	//int acc = 1;
	for (int dest : adj[node])
	{
		int prevNodeVal;
		if (visited[dest]){
			prevNodeVal = visitDepth[dest];
		}
		else{
			if (visitDepth[node] == maxSndMax[dest].fst){
				prevNodeVal = maxSndMax[dest].snd+1;
			}
			else{
				prevNodeVal = maxSndMax[dest].fst+1;
			}
		}
		if (prevNodeVal > mxx){
			sndmxx = mxx;
			mxx = prevNodeVal;
		}
		else if (prevNodeVal > sndmxx){
			sndmxx = prevNodeVal;
		}
	}

	//printf("node %i: %i > %i\n", node, mxx, sndmxx);

	ans[node] = mxx+1; maxSndMax[node] = make_pair(mxx, sndmxx);
	for (int dest : adj[node])
	{
		if (visited[dest]){
			rotateTree(dest);
		}
	}
}
int main()
{
	int n; scanf("%i", &n);
	for (int e = 1; e < n; e++)
	{
		int a, b; scanf("%i%i", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	ans[1]=fillDepth(1);
	int mxx = 0, sndmxx = 0; visited[1] = false;
	for (int ee : adj[1])
	{
		if (visitDepth[ee] > mxx){
			sndmxx = mxx;
			mxx = visitDepth[ee];
		}
		else if (visitDepth[ee] > sndmxx){
			sndmxx = visitDepth[ee];
		}
	}
	maxSndMax[1] = make_pair(mxx, sndmxx);
			//find all the other depths
	for (int dest : adj[1]) rotateTree(dest);
	for (int e = 1; e <= n; e++) printf("%i\n", ans[e]);
	//scanf(" ");
}