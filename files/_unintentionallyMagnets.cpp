#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(__=getchar()); x=(x<<3)+(x<<1)+__-'0');}while(0)

using namespace std;
char __;
//int grid[10005][10005];
int grid[4005][4005];
vector<pair<int, int> > magnets;
int dd(pair<int, int> a, pair<int, int> b)
{
	return abs(a.fst - b.fst) + abs(a.snd - b.snd);
}
int main()
{
	int n; scan(n);
	for (int e = 0; e < n; e++)
	{
		int a, b; scan(a); scan(b);
		magnets.push(_(a, b));
	}
	int m; scan(m);
	for (int e = 0; e < m; e++)
	{
		int a, b; scan(a); scan(b);
		int closestDist = 100000;
		for (int ee = 0; ee < magnets.size(); ee++)
		{
			closestDist = min(closestDist, dd(_(a, b), magnets[ee]));
		}
		
		int acc = 0;
		for (int x = a - closestDist + 1; x <= a + closestDist - 1; x++)
		{
			if (x >= 0 && x < 4000){
				grid[x][max(0, b - acc)]++;
				grid[x][min(4000, b + acc + 1)]--;
			}
			if (x < a)
				acc++;
			else
				acc--;
		}
		
	}
	/*
	for (int e = 0; e < 50; e++)
	{
		for (int ee = 0; ee < 50; ee++)
			printf("%i ", grid[e][ee]);
		printf("\n");
	}
	*/
	int mmm = 0;
	for (int e = 0; e < 4000; e++)
	{
		int acc = 0;
		for (int ee = 0; ee < 4001; ee++)
		{
			acc += grid[e][ee];
			mmm = max(mmm, acc);
		}
	}
	printf("%i\n", mmm);
	//scanf(" ");
	return 0;
}