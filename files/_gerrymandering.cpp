#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define fst first
#define snd second
//#define _ make_pair
#define push push_back

using namespace std;

int ridings[1005][11];
int mander[1005][1005];
int sw[11];

int main()
{
	int n, p; scanf("%i%i", &n, &p);
	for (int e = 0; e < n; e++)
	{
		for (int ee = 0; ee < p; ee++)
		{
			scanf("%i", &ridings[e][ee]);
		}
	}
	for (int e = 0; e < n; e++)
	{
		for (int ee = 0; ee <= e; ee++)
		{
			//printf("%i %i\n", e, ee);
			if (ee == 0){
				for (int d = 0; d < p; d++)
					sw[d] = 0;
				int mx = 0, ind = 0;
				for (int e_ = e; e_ >= 0; e_--)
				{
					for (int ee_ = 0; ee_ < p; ee_++)
					{
						sw[ee_] += ridings[e_][ee_];
					}
				}
				for (int e_ = 0; e_ < p; e_++)
				{
					if (sw[e_] >= mx){
						mx = sw[e_];
						ind = e_;
					}
				}
				mander[e][0] = (ind == 0);
			}
			else{
				//printf("%i\n", ee);
				for (int d = 0; d < p; d++)
					sw[d] = 0;
				int accMax = 0;
				for (int e_ = e; e_ >= ee; e_--)
				{
					int mx = 0, ind = 0;
					for (int ee_ = 0; ee_ < p; ee_++)
					{
						sw[ee_] += ridings[e_][ee_];
						if (sw[ee_] >= mx){
							mx = sw[ee_];
							ind = ee_;
						}
					}
					accMax = max(accMax, (ind == 0) + mander[e_ - 1][ee - 1]);
				}
				mander[e][ee] = accMax;
			}
		}
	}
	/*
	for (int e = 0; e < n; e++)
	{
		for (int ee = 0; ee < n; ee++)
		{
			printf("%i ", mander[e][ee]);
		}printf("\n");
	}
	*/
	int lafin = n;
	for (int e = 0; e < n; e++)
	{
		if (mander[n - 1][e] * 2 > e + 1) lafin = e;
	}
	printf("%i\n", n - lafin - 1);

	scanf(" ");
	return 0;
}