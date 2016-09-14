//vv an O(n^1.75) solution vv

#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(__=getchar()); x=(x<<3)+(x<<1)+__-'0');}while(0)

using namespace std;

char __;
int SQ = 500;//317;   //let's screw with this a little
int SQ2 = 5556;//5555
int n;
int inv[100005];
int elements[100005]; pair<int, int> things[100005];
int groupSum[201][20];
vector<pair<int, pair<int, int> > > groups[201][20];
int groupOverhead[320];
long long ans[100005];
pair<pair<int, int>, int> queries[100005];	//((a,b),position)

void addOne(int above, int groupN)
{
	for (int e = 0; e <= n / SQ2; e++)
	{
		for (int ee = 0; ee < groups[groupN][e].size(); ee++)
		{
			if (groups[groupN][e][ee].snd.fst > above){
				groups[groupN][e][ee].fst++;
				groupSum[groupN][e]++;
			}
		}
	}
}
int getSum(int left, int right, int groupN)
{
	int e = n / SQ2;
	int acc = 0, el = 0;
	for (; e >= left / SQ2 + 1; e--)
	{
		acc += groupSum[groupN][e];
		el += groups[groupN][e].size();
	}
	for (int ee = groups[groupN][e].size() - 1; ee > -1; ee--)
	{
		if (groups[groupN][e][ee].snd.snd < left) break;
		acc += groups[groupN][e][ee].fst;
		el++;
	}
	return acc + el * groupOverhead[groupN];
}
bool sorter(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	return a.fst.snd < b.fst.snd;
}bool sorter2(pair<int, int> a, pair<int, int> b) { return a.fst < b.fst; }

int main()
{
	scan(n);

	for (int e = 0; e < n; e++)
	{
		int a; scan(a);
		things[e] = _(a, e);
	}
	stable_sort(things, things + n, sorter2);
	for (int e = 0; e < n; e++)
	{
		things[e] = _(things[e].snd, e);
	}
	stable_sort(things, things + n, sorter2);
	for (int e = 0; e < n; e++)
	{
		elements[e] = things[e].snd+1;
	}
	//compress
	int q; scan(q);
	for (int e = 0; e < q; e++)
	{
		int a, b; scan(a); scan(b);
		queries[e] = _(_(a-1, b-1), e);
	}

	stable_sort(queries, queries + q, sorter);
	int ai = 0, qi = 0;
	while (ai != n || qi != q)
	{
		if (ai == n || (qi!=q && queries[qi].fst.snd < ai)){
			long long acc = 0;
			/*
			for (int e = queries[qi].fst.fst; e <= queries[qi].fst.snd; e++)
			{
				acc += inv[e];
			}
			*/
			pair<int, int> qq = queries[qi].fst;
			for (int e_ = 0; e_ <= n/SQ; e_ ++)
			{
				acc += getSum(qq.fst, qq.snd, e_);
			}
			ans[queries[qi].snd] = acc;
			qi++;
		}
		else{
			int element = elements[ai];
			int ff = element / SQ, cc = element / SQ + 1;
			addOne(element, ff);
			for (int e = cc; e <= n/SQ; e ++)
			{
				groupOverhead[e]++;
			}
			int a = ai / SQ2;
			groups[ff][a].push(_(-groupOverhead[ff], _(element, ai)));
			groupSum[ff][a] -= groupOverhead[ff];
			
			ai++;
		}
	}

	for (int e = 0; e < q; e++)
	{
		printf("%lld\n", ans[e]);
	}

	//scanf(" ");
	return 0;
}