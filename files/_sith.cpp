#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define fst first
#define snd second
#define _ make_pair
#define push push_back

using namespace std;

vector<int> adj[234569];
int join[234569];

void s(int a, int ID)
{
	if (join[a] == 0){
		join[a] = ID;
		for (int e_ = 0; e_ < adj[a].size(); e_++)
		{
			int e = adj[a][e_];
			for (int ee = 0; ee < adj[e].size(); ee++)
			{
				s(adj[e][ee], ID);
			}
		}
	}
}
int gr[234569];
int main()
{
	int n, m; scanf("%i%i", &n, &m);
	for (int e = 0; e < m; e++)
	{
		int a, b; scanf("%i%i", &a, &b);
		adj[a].push(b);
		adj[b].push(a);
	}
	for (int e = 1; e <= n; e++)
	{
		s(e, e);
	}
	for (int e = 1; e <= n; e++)
	{
		gr[join[e]]++;
	}
	double chance = 0.0;
	for (int e_ = 1; e_ <= n; e_++)
	{
		int e = gr[e_];
		chance += (double)e / n*e / n;
	}
	printf("%f\n", chance);

	scanf(" ");
	return 0;
}