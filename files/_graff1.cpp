#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#define _ make_pair
#define fst first
#define snd second
#define push push_back
using namespace std;
vector<int> adj[1000001];
int upTree[1000001], depth[1000001];
int belongs[1000005];
int cc[1000005];
vector<pair<int, int> > cycles;
void HELP(int node, int previous, int dpth)
{
	upTree[node] = previous;
	depth[node] = dpth;
	for (int e = 0; e < adj[node].size(); e++)
	{
		int nn = adj[node][e];
		if (nn != previous){
			if (upTree[nn] == 0){
				HELP(nn, node, dpth + 1);
			}
			else{
				cycles.push(_(node, nn));
			}
		}
	}
}
int unravel(int w)
{
	if (belongs[w] == w) return w;
	else{
		belongs[w] = unravel(belongs[w]);
		return belongs[w];
	}
}
void commonParent(int node1, int node2)
{
	int n1 = node1, n2 = node2;

	while (n1 != n2)
	{
		//printf("%i     %i\n", n1, n2);
		if (depth[n1] > depth[n2]){
			if (belongs[n1] != n1){
				unravel(n1);
				n1 = belongs[n1];
			}
			else{
				n1 = upTree[n1];
			}
		}
		else{
			if (belongs[n2] != n2){
				unravel(n2);
				n2 = belongs[n2];
			}
			else{
				n2 = upTree[n2];
			}
		}
	}
	int target = n1;
	n1 = node1; n2 = node2;
	while (n1 != n2)
	{
		if (depth[n1] > depth[n2]){
			if (belongs[n1] != n1){
				//unravel(n1);
				n1 = belongs[n1];
				belongs[n1] = target;
			}
			else{
				belongs[n1] = target;
				n1 = upTree[n1];
			}
		}
		else{
			if (belongs[n2] != n2){
				//unravel(n2);
				n2 = belongs[n2];
				belongs[n2] = target;
			}
			else{
				belongs[n2] = target;
				n2 = upTree[n2];
			}
		}
	}
}
int main()
{
	int n, m; scanf("%i%i", &n, &m);
	for (int e = 0; e < m; e++)
	{
		int a, b; scanf("%i%i", &a, &b);
		adj[a].push(b);
		adj[b].push(a);
	}
	
	HELP(1, 1, 1);			//tree is rooted at 1
	
	for (int e = 1; e <= n; e++)
	{
		belongs[e] = e;
	}

	//detect cycles by adding critical edges to the spanning tree one by one
	//
	for (int e = 0; e < cycles.size(); e++)
	{
		pair<int, int> pp = cycles[e];
		commonParent(pp.fst, pp.snd);
		//disjoint use here
	}
	//
	for (int e = 1; e <= n; e++)
	{
		int b = unravel(e);
		cc[b]++;
	}
	long long acc = 0;
	for (int e = 0; e <= n; e++)
	{
		acc += ((long long)cc[e]) * ((long long)(n - cc[e]));
	}
	long long n_ = n;
	printf("%.5f", acc / ((double)(n_*(n_ - 1))));
	
	scanf(" ");
	return 0;
}