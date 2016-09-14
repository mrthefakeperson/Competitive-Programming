#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#define fst first
#define snd second
using namespace std;
bool sorter(pair<pair<double, double>, int> a, pair<pair<double, double>, int> b)
{
	if (b.fst.snd > a.fst.snd){
		return false;
	}
	else if (a.fst.snd > b.fst.snd){
		return true;
	}
	else{
		return !(b.fst.fst > a.fst.fst);
	}
}
//pair<pair<double,double>,int> slopes[200001];
pair<pair<double, double>, int> buffer[25][400001];			//only two arrays are really necessary
void merge(int from, int onto, int lft, int rgt, int lLimit, int rLimit, int acc)
{			
	int l = lft, r = rgt,a=acc;
	while (l != lLimit && r != rLimit)
	{
		if (buffer[from][r].fst.fst <= buffer[from][l].fst.fst){
			buffer[onto][a] = make_pair(buffer[from][r].fst, buffer[from][r].snd + lLimit - l);
			++r; ++a;
		}
		else{
			buffer[onto][a] = buffer[from][l];
			++l; ++a;
		}
	}
	while (l < lLimit)
	{
		buffer[onto][a] = buffer[from][l];
		++l; ++a;
	}
	while (r < rLimit)
	{
		buffer[onto][a] = buffer[from][r];
		++r; ++a;
	}
}
int mergesort(int jumpp, int rLimit)
{
	int jump = jumpp,index=0;
	while (jump <= rLimit)
	{
		for (int e = 0; e < rLimit; e += jump)
		{
			merge(index, index+1, e, e + jump / 2, e + jump / 2, e + jump, e);
		}
		jump *= 2; ++index;
	}
	return index;
}
long long acc;
int main()
{
	int a;int b; scanf("%i%i", &a, &b);
	int aaa = 1; for (; aaa < a; aaa *= 2);
	for (int e = 0; e < aaa; e++) buffer[0][e] = make_pair(make_pair(2000015.0L+1.0L*e, 0.0L), -10);
	for (int e = 0; e<a; e++){
		int aa, bb; scanf("%i%i", &aa, &bb);
		double p1, p2;
		if (aa == 0) p1 = 1500000.0L;
		else p1 = (double)bb / (double)aa;// printf("%i,%i->%f\n", bb, aa, (double)bb / aa);
		if (aa == b) p2 = 1500000.0L;
		else p2 = (double)bb / ((double)b - (double)aa);// printf("%f,%i->%f", b, aa, b - aa);
		buffer[0][e] = make_pair(make_pair(p1, p2), 0);
	}

	sort(buffer[0], buffer[0] + a, sorter);
	/*
	for (int e = 0; e < a; e++)
	{
		printf("%f,%f\n", buffer[0][e].fst.fst, buffer[0][e].fst.snd);
	}
	*/
	int ind = mergesort(2, aaa);    //aa needs to be a power of 2 at the moment
	acc = 0;
	for (int e = 0; e < aaa; e++)
	{
		if (buffer[ind][e].fst.fst < 2000015.0){
			acc += (long long)buffer[ind][e].snd*(long long)buffer[ind][e].snd;
		}
	}
	printf("%llu\n", acc);
	//scanf(" ");
	return 0;
}