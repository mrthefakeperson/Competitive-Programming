#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#define fst first
#define snd second
#define push push_back

using namespace std;

int baseTimes[16], addedTimes[16];
vector<pair<long long, long long>> bestTimeS[32729];
bool visited[32729];
long long bestTime[16][32769];		//bestTime[index of addedTime (final)][subset hash]
int n;
bool subset[16]; bool sorter(pair<long long, long long> a, pair<long long, long long> b)
{
	if (a.fst != b.fst) return a.fst > b.fst;
	else return a.snd < b.snd;
}
void fillSmallN(int subsetHash, int baseTimeInd)
{
	int pow = 1;
	vector<pair<long long, long long>> rr;
	for (int e = 1; e <= n; e++)
	{
		if (subset[e]){
			subset[e] = false;
			if (!visited[subsetHash - pow]){
				visited[subsetHash - pow] = true;
				fillSmallN(subsetHash - pow, baseTimeInd - 1);
			}
			subset[e] = true;
			for (pair<long long, long long> pp : bestTimeS[subsetHash - pow])
			{
				long long thing = baseTimes[baseTimeInd] + addedTimes[e];
				rr.push(make_pair(max(pp.fst, thing), max(pp.snd, thing - pp.fst)));
				//bestTime[subsetHash].push(make_pair(max(pp.fst, thing), max(pp.snd, thing - pp.fst)));
			}
		}
		pow *= 2;
	}
	//printf("%i\n", rr.size());
	sort(rr.begin(), rr.end(), sorter);
	pair<long long, long long> last = make_pair(-1, -1);
	for (pair<long long, long long> pp : rr)
	{
		if (!(pp.fst == last.fst || (pp.fst<last.fst && pp.snd>last.snd))){
			bestTimeS[subsetHash].push(pp);
		}
	}
}
long long fill(int ssubsetHash, int itemInd_last, int addedTimeInd_last)
{
	long long lastItem, rr;
	int pow;
	int subsetHash = 0; pow = 1;
	for (int e = 1; e <= n; e++)
	{
		if (subset[e]) subsetHash += pow;
		pow *= 2;
	}//printf("%i\n", subsetHash);*/
	//if (ssubsetHash != subsetHash) printf("problem\n");
	if (bestTime[addedTimeInd_last][subsetHash] == 0){
		lastItem = (long long)baseTimes[itemInd_last] + addedTimes[addedTimeInd_last];
		if (itemInd_last == 1) rr = lastItem;
		else{
			pow = 1;
			rr = 2099999991;
			for (int e = 1; e <= n; e++)
			{
				if (subset[e]){
					subset[e] = false;
					rr = min(rr, max(fill(subsetHash - pow, itemInd_last - 1, e), lastItem - baseTimes[itemInd_last - 1] - addedTimes[e]));
					subset[e] = true;
				}
				pow *= 2;
			}
		}
		bestTime[addedTimeInd_last][subsetHash] = rr;
	}
	return bestTime[addedTimeInd_last][subsetHash];
}
int main()
{
	scanf("%i", &n);
	for (int e = 1; e <= n; e++)
	{
		int nnn; scanf("%i", &nnn);
		baseTimes[e] = nnn;
	}
	for (int e = 1; e <= n; e++)
	{
		int nn; scanf("%i", &nn);
		addedTimes[e] = nn;
	}
	int pow, acc; long long _final;
	if (n > 6){
		pow = 1; acc = 0;
		for (int e = 1; e <= n; e++)
		{
			subset[e] = true;
			acc += pow;
			pow *= 2;
		}
		pow = 1;
		for (int e = 1; e <= n; e++){
			subset[e] = false;
			//itemInd_last = n;
			_final = min(_final, fill(acc - pow, n, e));
			subset[e] = true;
			pow *= 2;
		}
		printf("%lld\n", _final);
	}
	else{

		pow = 1; acc = 0;
		for (int e = 1; e <= n; e++)
		{
			subset[e] = true;
			acc += pow;
			visited[pow] = true;
			bestTimeS[pow].push(make_pair(baseTimes[1] + addedTimes[e], baseTimes[1] + addedTimes[e]));
			pow *= 2;
		}
		fillSmallN(acc, n);
		_final = 2099999999;
		for (pair<long long, long long> pp : bestTimeS[acc]) _final = min(_final, pp.snd);
		printf("%lld\n", _final);
	}
	scanf(" ");

	return 0;
}