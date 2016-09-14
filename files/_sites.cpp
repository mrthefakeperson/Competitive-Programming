#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

#define push push_back
#define fst first
#define snd second
#define _ make_pair
using namespace std;
vector<pair<int, int> > adj[100005];	//backwards matrix
int ppl[100005];
long long visited1[100005];
long long visited2[100005];
pair<long long, int> save[100005];		//amount to be saved by going to 2, number of people
//long long distFrom1[100005];
bool sorter(pair<long long, int> a, pair<long long, int> b)
{
	return a.fst > b.fst;
}
int main()
{
	int k, towns, roads;
	scanf("%i%i%i", &towns, &roads, &k);
	for (int e = 1; e <= towns; e++)
	{
		int amt; scanf("%i", &amt);
		ppl[e] = amt;
	}
	for (int e = 0; e < roads; e++)
	{
		int a, b, c; scanf("%i%i%i", &a, &b, &c);
		adj[b].push(_(a, c));
	}
	vector<pair<int, int> > searchList; searchList.push(_(1, 1));		//_(place, distance+1), remember to subtract one
	while (searchList.size() > 0)
	{
		vector<pair<int, int> > Nlist;
		for (int e = 0; e < searchList.size(); e++)
		{
			pair<int, int> path = searchList[e];
			if (visited1[path.fst] == 0 || visited1[path.fst] > path.snd){
				visited1[path.fst] = path.snd;
				for (int ee = 0; ee < adj[path.fst].size(); ee++)
				{
					pair<int, int> qq = adj[path.fst][ee];
					Nlist.push(_(qq.fst, qq.snd + path.snd));
					//printf("pushed %i,%i\n", qq.fst, qq.snd + path.snd);
				}
			}
		}
		searchList = Nlist;
	}
	//sub 1
	for (int e = 1; e <= towns; e++)
		visited1[e]--;
	//from 2
	searchList.clear(); searchList.push(_(2, 1));
	while (searchList.size() > 0)
	{
		vector<pair<int, int> > Nlist;
		for (int e = 0; e < searchList.size(); e++)
		{
			pair<int, int> path = searchList[e];
			if (visited2[path.fst] == 0 || visited2[path.fst] > path.snd){
				visited2[path.fst] = path.snd;
				for (int ee = 0; ee < adj[path.fst].size(); ee++)
				{
					pair<int, int> qq = adj[path.fst][ee];
					Nlist.push(_(qq.fst, qq.snd + path.snd));
					//printf("pushed %i,%i\n", qq.fst, qq.snd + path.snd);
				}
			}
		}
		searchList = Nlist;
	}
	for (int e = 1; e <= towns; e++)
		visited2[e]--;
	bool canDo = true;
	vector<pair<int, int> > must2;
	for (int e = 1; e <= towns; e++)
	{
		if (visited1[e] == -1 && visited2[e] == -1 && ppl[e] != 0)
			canDo = false;
		int aa = ppl[e];
		if (visited1[e] == -1){
			//if (visited2[e] == -1&&ppl[e]!=0){
				//canDo = false;
			//}
			//else{
				save[e] = _(-1, 0);
				must2.push(_(visited2[e], aa));
			//}
		}
		else if (visited2[e] == -1){
			save[e] = _(-1, aa);
		}
		else{
			save[e-1] = _(visited1[e] - visited2[e], ppl[e]);
		}
	}
	sort(save + 1, save + towns + 1, sorter);

	long long acc = 0;
	long long saved = 0;
	for (int e = 0; e < must2.size(); e++)
	{
		if (must2[e].snd > k){
			canDo = false;
		}
		else{
			acc += must2[e].fst * must2[e].snd;
			k -= must2[e].snd;
		}
	}
	for (int e = 1; e <= towns; e++)
	{
		pair<long long, int> pp = save[e];
		if (pp.fst <= 0) break;
		if (pp.snd > k){
			saved += k*pp.fst;
			break;
		}
		else{
			k -= pp.snd;
			saved += pp.fst*pp.snd;
		}
	}
	for (int e = 1; e <= towns; e++)
	{
		if (visited1[e] > 0)
			acc += visited1[e]*ppl[e];
	}
	if (canDo){
		printf("%lld\n", acc - saved);
	}
	else{
		printf("-1");
	}

	scanf(" ");
	return 0;
}