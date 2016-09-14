#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define fst first
#define snd second
#define _ make_pair
#define push push_back

using namespace std;

const int SQ = 500;		//500?
int x, y, xx, yy;
long long timeline[400005], timeCheck[400005]; long long ans[400005];
long long total[400005];
long long overhead[805], stored[805], amtUnder[805];
bool sorter(pair<int, pair<int, int> > a, pair<int, pair<int, int> > b) {
	return a.fst < b.fst;
}
void add(int incl, int factor)
{

	int e = 0;
	while (e <= incl)
	{
		if (e%SQ == 0 && e + SQ <= incl){
			stored[e / SQ] += factor * amtUnder[e / SQ];
			overhead[e / SQ] += factor;
			e += SQ;
		}
		else{
			total[e] += factor * timeline[e];
			stored[e / SQ] += factor * timeline[e];
			e++;
		}
	}

	/*
	for (int e = 0; e <= incl; e++)
	{
	total[e] += factor; // *timeline[e];
	}
	*/
}
long long getSum(int excl)
{

	int e = 0; long long acc = 0;
	while (e < excl)
	{
		if (e%SQ == 0 && e + SQ < excl){
			acc += stored[e / SQ];
			e += SQ;
		}
		else{
			acc += overhead[e / SQ] * timeline[e] + total[e];
			e++;
		}
	}
	return acc;

	/*
	int acc = 0;
	for (int e = 0; e < excl; e++)
	{
	acc += total[e] * timeline[e];
	}
	return acc;
	*/
}
int find(int e, int s)
{
	int place = -1, jump = s;
	while (jump > 0)
	{
		if (timeCheck[place + jump] <= e && place+jump<s){
			place += jump;
		}
		jump /= 2;
	}
	while (timeCheck[place + 1] <= e && place + 1 < s) place++;
	return place;
}
pair<int,int> sim(int start, int boundl, int boundr, int change, int ss)		//interval inclusive
{
	if (change == 0 && boundl <= start && start <= boundr){
		return _(-5, 400005);
	}
	else if ((change <= 0 && start<boundl) || (change >= 0 && start>boundr)){
		return _(-10, -10);
	}
	else{
		int b, e;
		if (boundl <= start && start <= boundr){
			b = -1;
		}
		else{
			if (change > 0){
				b = (boundl - 1 - start) / change;
			}
			else{
				b = (start - boundr - 1) / -change;
			}
		}
		if (change > 0){
			e = (boundr - start) / change;
		}
		else{
			e = (start - boundl) / -change;
		}
		//time b is the last second this ship cannot be hit, e is the last second this ship can be hit

		return _(find(b,ss), find(e,ss));
	}

}
pair<int, int> simulate(pair<pair<int, int>, pair<int, int> > anon,int bound)
{
	int a = anon.fst.fst, b = anon.fst.snd, c = anon.snd.fst, d = anon.snd.snd;
	pair<int, int> iX = sim(a, x, xx, c, bound), iY = sim(b, y, yy, d, bound);
	if (iX.snd <= iY.fst || iY.snd <= iX.fst) return _(-5, -5);
	else{
		return _(max(iX.fst, iY.fst), min(iX.snd, iY.snd));
	}
	/*
	int ind = 0;
	int st, end;
	while ((!(x <= anon.fst.fst + timeCheck[ind] * c && anon.fst.fst + timeCheck[ind] * c <= xx) || !(y <= anon.fst.snd + timeCheck[ind] * d && anon.fst.snd + timeCheck[ind] * d <= yy)) && ind < bound)
	{
		ind++;
	}
	st = ind-1;
	while ((x <= anon.fst.fst + timeCheck[ind] * c && anon.fst.fst + timeCheck[ind] * c <= xx) && (y <= anon.fst.snd + timeCheck[ind] * d && anon.fst.snd + timeCheck[ind] * d <= yy) && ind < bound)
	{
		ind++;
	}
	end = ind-1;
	//printf("%i,%i\n", st, end);
	if (st == end) return _(-1, -1);
	else return _(st, end);
	*/
}
int main()
{
	int n, m; scanf("%i%i", &n, &m);
	scanf("%i%i%i%i", &x, &y, &xx, &yy);
	vector<pair<int, int> > ships;
	vector < pair<pair<int, int>, pair<int, int> > > shipHolder;
	for (int e = 0; e < n; e++)
	{
		int a, b, c, d; scanf("%i%i%i%i", &a, &b, &c, &d);
		shipHolder.push(_(_(a, b), _(c, d)));
	}
	//for (int e = 0; e < n; e++) printf("(%i,%i)\n", ships[e].fst, ships[e].snd);
	int time_ = 0, accTime = 0, query = 0;
	vector<pair<int, pair<int, int> > > queries;
	for (int e = 0; e < m; e++)
	{
		int t, a, b; scanf("%i%i%i", &t, &a, &b);
		if (t == 1){
			accTime += a;
			timeCheck[time_] = accTime;
			timeline[time_] = b;
			amtUnder[time_ / SQ] += b;
			time_++;
		}
		else{
			queries.push(_(b, _(query, time_)));
			queries.push(_(a - 1, _(-query - 1, time_)));
			query++;
		}
	}
	for (int e = 0; e < n; e++)
	{
		ships.push(simulate(shipHolder[e],time_));
	}

	sort(queries.begin(), queries.end(), sorter);
	int qPoint = 0,sPoint = 0;
	//for (int e = 0; e < n; e++)
	while (qPoint<queries.size() && sPoint<ships.size())
	{
		if (queries[qPoint].fst <= sPoint){
			//while (queries[qPoint].fst == e)
			//{
			//printf("Q #%i %i\n", queries[qPoint].snd.fst, queries[qPoint].snd.snd);
			if (queries[qPoint].snd.fst >= 0){
				ans[queries[qPoint].snd.fst] += getSum(queries[qPoint].snd.snd);
			}
			else{
				ans[-(queries[qPoint].snd.fst + 1)] -= getSum(queries[qPoint].snd.snd);
			}
			qPoint++;
			//}
		}
		else{
			//if (ships[sPoint].snd != -1){
				add(ships[sPoint].fst, -1);
				add(ships[sPoint].snd, 1);
			//}
			sPoint++;
		}
	}
	for (int e = qPoint; e < queries.size(); e++)
	{
		if (queries[e].snd.fst >= 0){
			ans[queries[e].snd.fst] += getSum(queries[e].snd.snd);
		}
		else{
			ans[-(queries[e].snd.fst + 1)] -= getSum(queries[e].snd.snd);
		}
	}
	for (int e = 0; e < query; e++)
	{
		printf("%lld\n", ans[e]);
	}

	scanf(" ");
	return 0;
}