#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define fst first
#define snd second
#define _ make_pair
#define push push_back

using namespace std;
long long liths[30005];
long long groups[62], overhead[62];
int SQ = 500;
//int SQ = 3;

int main()
{
	int n, q; scanf("%i%i", &n, &q);
	for (int e = 0; e < n; e++) scanf("%i", &liths[e]);
	long long m = liths[0];
	for (int e = 0; e < n; e++) m = min(m, liths[e]);
	//printf("initial: %i\n", m);
	for (int e = 0; e < n; e++) groups[e / SQ] = 1000000005;
	for (int e = 0; e < n; e++)
	{
		groups[e / SQ] = min(groups[e / SQ], liths[e]);
	}
	for (int ee = 0; ee < q; ee++)
	{
		int a, b, dec; scanf("%i%i%i", &a, &b, &dec); a--; b--;
		int e = a; long long mm = liths[a];
		for (; e % SQ != 0 && e <= b; e++)
		{
			liths[e] -= dec;
			//liths[e] = max(liths[e], 0);
			groups[e / SQ] = min(groups[e / SQ], liths[e] - overhead[e / SQ]);
			//groups[e / SQ] = max(groups[e / SQ], 0);
			mm = min(mm, liths[e] - overhead[e / SQ]);
			//printf("e: %i   ", e);
			//printf("e/SQ: %i    ", e / SQ);
		}
		for (; e + SQ <= b; e += SQ)
		{
			overhead[e / SQ] += dec;
			//overhead[e / SQ] = min(1000000005, overhead[e / SQ]);
			groups[e / SQ] -= dec;
			//groups[e / SQ] = max(groups[e / SQ], 0);
			mm = min(mm, groups[e / SQ]);
			//printf("e: %i   ", e);
			//printf("xxx e/SQ: %i    ", e / SQ);
		}
		for (; e <= b; e++)
		{
			liths[e] -= dec;
			//liths[e] = max(liths[e], 0);
			groups[e / SQ] = min(groups[e / SQ], liths[e] - overhead[e / SQ]);
			//groups[e / SQ] = max(groups[e / SQ], 0);
			mm = min(mm, liths[e] - overhead[e / SQ]);
			//printf("e: %i   ", e);
			//printf("e/SQ: %i    ", e / SQ);
		}
		//printf("e: %i\n", e);
		/*
		for (int e = 0; e < n; e++) printf("%i ", max(liths[e] - overhead[e / SQ], 0));
		printf("\n");
		for (int e = 0; e < n / SQ + 1; e++) printf("%i ", max(groups[e], 0));
		printf("\n");
		for (int e = 0; e < n / SQ + 1; e++) printf("%i ", overhead[e]);
		printf("\n");
		*/
		m = min(m, mm);
		printf("%lld %lld\n", max(mm, 0ll), max(m, 0ll));
	}

	scanf(" ");
	return 0;
}