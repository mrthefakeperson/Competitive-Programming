#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
//int lastVisited;			//so the recursive function can't go back and forth
bool visited[400001];
vector<int> adj[400001];
vector<pair<int, int> > qq;
int n, biggestSoFar, mm;
long long amtWays;



pair<int, long long> exploreForDepth(int node)		//looks forward, ignoring the last node checked; returns the max depth and the number of ways to achieve so
{
	//int donotvisit = lastVisited,tempMaxDepth=0,tempAmtWays=0;
	//int tempMaxDepth = 0, tempAmtWays = 0;// , sndMaxDepth = 0;
	//lastVisited = node;
			//is it this?
	long long maxDepth = 0, waysForMax = 1;
	visited[node] = true;
	if (adj[node].size() == 1 && visited[adj[node][0]]){
		//printf("node %i: end node returned (1,1)\n",node);
		return make_pair(1, 1);
	}
	else{		
		for (vector<int>::size_type e = 0; e < adj[node].size(); e++)
		{
			pair<int, int> ts;
			if (!visited[adj[node][e]]){
				ts = exploreForDepth(adj[node][e]);
				//printf("node %i: (%i,%i)\n", adj[node][e], ts.first, ts.second);
				if (ts.first + maxDepth+1>biggestSoFar){
					biggestSoFar = ts.first+1+maxDepth;
					amtWays = ts.second*waysForMax;
				}
				else if (ts.first+maxDepth+1 == biggestSoFar){
					amtWays += ts.second*waysForMax;
				}
				if (ts.first > maxDepth){
					maxDepth = ts.first;
					waysForMax = ts.second;
				}
				else if (ts.first == maxDepth){
					waysForMax += ts.second;
				}
			}
		}
		/*
		for (vector<int>::size_type e = 0; e < adj[node].size(); e++)
		{
			if (!visited[adj[node][e]]){
				rr.push_back(exploreForDepth(adj[node][e]));
			}
		}
		for (vector<pair<int, int> >::size_type e = 0; e < rr.size(); e++)		//check for cycles using only the max so far
		{
			if (tempMaxDepth + rr[e].first + 1 > mm)
				mm = tempMaxDepth + rr[e].first + 1;

			if (rr[e].first + 1 > tempMaxDepth){
				tempMaxDepth = rr[e].first + 1;
				tempAmtWays = rr[e].second;
			}
			else if (rr[e].first + 1 == tempMaxDepth){
				tempAmtWays += rr[e].second;
			}
		}

		if (biggestSoFar <= tempMaxDepth * 2){			//this needs to change
			inspectForCycles(rr, tempMaxDepth - 1);
		}
		*/
		//printf("node %i: %i deep, %i ways\n", node, tempMaxDepth, tempAmtWays);

		return make_pair(maxDepth+1, waysForMax);
	}
}

int main()
{
	scanf("%i", &n);
	long long qqq = 0;
	for (int e = 1; e < n; e++)
	{
		int a, b; scanf("%i%i", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	//int _;
	//for (int e = 0; e < n; e++){ if (adj[e].size() == 1){ _ = e; } }
	//adj[0].push_back(n);
	exploreForDepth(1);
	/*
	if (qqq < amtWays) qqq = amtWays;
	amtWays = 0;
	for (int e = 2; e <= n; e++)
	{
		exploreForDepth(e);
		if (qqq < amtWays) qqq = amtWays;
		amtWays = 0;
	}
	*/
	/*
	if (n > 20000){ n /= 7; n *= 3; }
	pair<int, int> q = exploreForDepth(1); int tmpM=q.first;
	if (tmpM > biggestSoFar){
		biggestSoFar = tmpM;
		amtWays = q.second;
	}
	else if (tmpM == biggestSoFar){
		amtWays += q.second;
	}
	*/
	printf("%i %llu", biggestSoFar, amtWays);

	//scanf(" ");
	return 0;
}