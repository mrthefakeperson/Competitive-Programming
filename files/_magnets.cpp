#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <iostream>

#define fst first
#define snd second
#define _ make_pair
#define push push_back

using namespace std;
//int grid[4000][4000];
//int accRow[4000];
int accRow[4000], accRow2[4000];
vector<pair<int, int> > magnets;

int dd(pair<int, int> a, pair<int, int> b)
{
	return abs(a.fst - b.fst) + abs(a.snd - b.snd);
}

bool sorter2(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	return a.fst.snd < b.fst.snd;
}

int main()
{
	int n; scanf("%i", &n);
	
	for (int e = 0; e < n; e++)
	{
		int a, b; scanf("%i%i", &a, &b);
		magnets.push(_(a, b));
	}
	vector<pair<pair<int, int>, int> > black, white;
	int m; scanf("%i", &m);
	for (int ee = 0; ee < m; ee++)
	{
		int x, y; scanf("%i%i", &x, &y);
		int clD = 100000;
		for (int e = 0; e < n; e++)
		{
			clD = min(clD, dd(_(x, y), magnets[e]));
		}
		clD--;
		if (clD != -1)
		{
			if ((x - clD + y) % 2 == 0)
			{
				white.push(_(_(x - clD + y, y + 1 - (x - clD - 1)), -1));
				white.push(_(_(x + clD + 1 + y + 1, y + 1 - (x + clD + 1)), -1));
				white.push(_(_(x + y - clD, y - clD - x), 1));
				white.push(_(_(x + y + clD + 2, y + clD + 2 - x), 1));
				black.push(_(_(x - clD + y + 1, y + 1 - (x - clD)), -1));
				black.push(_(_(x + clD + y + 1, y + 1 - (x + clD)), -1));
				black.push(_(_(x + y - clD + 1, y - clD + 1 - x), 1));
				black.push(_(_(x + y + clD + 1, y + clD + 1 - x), 1));
			}
			else
			{
				black.push(_(_(x - clD + y, y + 1 - (x - clD - 1)), -1));
				black.push(_(_(x + clD + 1 + y + 1, y + 1 - (x + clD + 1)), -1));
				black.push(_(_(x + y - clD, y - clD - x), 1));
				black.push(_(_(x + y + clD + 2, y + clD + 2 - x), 1));
				white.push(_(_(x - clD + y + 1, y + 1 - (x - clD)), -1));
				white.push(_(_(x + clD + y + 1, y + 1 - (x + clD)), -1));
				white.push(_(_(x + y - clD + 1, y - clD + 1 - x), 1));
				white.push(_(_(x + y + clD + 1, y + clD + 1 - x), 1));
			}
		}
	}
	//sort(white.begin(), white.end(), sorter1);
	sort(white.begin(), white.end(), sorter2);
	//sort(black.begin(), black.end(), sorter1);
	sort(black.begin(), black.end(), sorter2);

	int max_ = 0;
	int mmm = 0;
	int lastY = 0;
	//int accRow[4000];
	for (int e = 0; e < white.size(); e++)
	{
		pair<pair<int, int>, int> aaa = white[e];
		int a = aaa.fst.fst / 2, b = aaa.fst.snd, c = aaa.snd;

		if (lastY != b){
			lastY = b;
			int sw = 0;
			for (int ee = 0; ee < 4000; ee++)
			{
				sw += accRow[ee];
				mmm = max(mmm, sw);
			}
		}

		if (a < 0) accRow[0] += c;
		//else if (a >= 4000) accRow[3999] += c;
		else if (!(a>=4000)) accRow[a] += c;
	}
	int sw_ = 0;
	for (int ee = 0; ee < 4000; ee++)
	{
		sw_ += accRow[ee];
		mmm = max(mmm, sw_);
	}
	max_ = mmm;
	mmm = 0;
	lastY = 0;
	//int accRow2[4000];
	for (int e = 0; e < black.size(); e++)
	{
		pair<pair<int, int>, int> aaa = black[e];
		int a = aaa.fst.fst / 2, b = aaa.fst.snd, c = aaa.snd;

		if (lastY != b){
			lastY = b;
			int sw = 0;
			for (int ee = 0; ee < 4000; ee++)
			{
				sw += accRow2[ee];
				mmm = max(mmm, sw);
			}
		}

		if (a < 0) accRow2[0] += c;
		//else if (a >= 4000) accRow2[3999] += c;
		else if (!(a >= 4000)) accRow2[a] += c;
	}
	sw_ = 0;
	for (int ee = 0; ee < 4000; ee++)
	{
		sw_ += accRow2[ee];
		mmm = max(mmm, sw_);
	}
	max_ = max(max_, mmm);

	printf("%i\n", max_);
	//scanf(" ");
	
	return 0;
}