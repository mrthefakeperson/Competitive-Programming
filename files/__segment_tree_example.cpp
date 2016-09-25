//solves the Touching Segments problem on Hackerrank by using a segment tree
#include <cstdio>
#include <algorithm>
#include <utility>
#define fst first
#define snd second
#define _ make_pair

using namespace std;
pair<int, int> segments[150001];
pair<int, bool> absegments[200002];			//start points and end points seperate, start -> true ; end -> false
int bestOfLeft[150005];
int maxTree[280002], overhead[280002];		//stores max of stuff

bool sorter(pair<int, int> a, pair<int, int> b)
{
	return a.fst < b.fst;
}
bool sorter2(pair<int, bool> a, pair<int, bool> b)
{
	if (a.fst == b.fst){
		return a.snd;
	}
	else{
		return a.fst < b.fst;
	}
}
void addRange(int r,int change,int nn)
{
	int jump = nn, sgIndex = 1;
	int found = 0;
	while (!(nn<=sgIndex && sgIndex<2*nn))
	{
		//printf("%i   %i   %i\n", found, jump, sgIndex);
		//int __; scanf("%i", &__);
		int nj = jump / 2;
		if (segments[found + nj].fst < r){
			maxTree[sgIndex*2] += change; overhead[sgIndex*2] += change;
			sgIndex = sgIndex * 2 + 1;
			jump /= 2;
			found += nj;
		}
		else{
			jump /= 2;
			sgIndex *= 2;
		}
	}
	//printf("searched for %i, found at %i\n", r, found);
	while (sgIndex != 1)
	{
		sgIndex /= 2;
		//sift up
		maxTree[sgIndex] = overhead[sgIndex] + max(maxTree[sgIndex * 2], maxTree[sgIndex * 2 + 1]);
	}
	
}
int HELP()
{
	int n; scanf("%i", &n);
	int pow = 1; while (pow < n) pow *= 2;
	for (int e = 0; e < n; e++)
	{
		int a, b; scanf("%i%i", &a, &b);
		segments[e] = _(a, b);
		absegments[e] = _(a, true);
		absegments[n + e] = _(b, false);
	}
	for (int e = n; e < pow; e++)
	{
		segments[e] = _(1000000005, 0);
	}
	sort(segments, segments + n, sorter);
	sort(absegments, absegments + 2 * n, sorter2);
	int sw = 0, maxx = 0; int acc = 0;
	for (int e = 0; e < 2 * n; e++)
	{
		pair<int, bool> pp = absegments[e];
		if (pp.snd){
			sw++;
		}
		else sw--;
		if (sw>maxx) maxx = sw;
		if (pp.snd){
			bestOfLeft[acc] = maxx;
			acc++;
		}
	}
	/*
	for (int e = 0; e < n; e++)
	{
		printf("%i\n", bestOfLeft[e]);
	}
	*/
	int mm = bestOfLeft[n-1];
	for (int e = n-1; e >0; e--)
	{
		pair<int, int> pp = segments[e];
		addRange(pp.fst, -1, pow);
		addRange(pp.snd+1, 1, pow);
		mm = max(mm, maxTree[1] + bestOfLeft[e - 1]);
		/*
		printf("%i,%i\n", pp.fst, pp.snd);
		for (int e = 0; e < pow * 2; e++)
		{
			printf("%i ", maxTree[e]);
		}
		printf("\n%i\n",maxTree[1]);
		*/
	}
	addRange(segments[0].fst, -1, pow);
	addRange(segments[0].snd + 1, 1, pow);
	mm = max(mm, maxTree[1]);

	return mm;
}
int main()
{
	int n__; scanf("%i", &n__);
	for (int e = 0; e < n__; e++)
	{
		printf("Case %i: %i\n", e + 1, HELP());
		for (int e = 0; e < 280002; e++)
		{
			maxTree[e] = 0;
			overhead[e] = 0;
		}
	}

	scanf(" ");
	return 0;
}