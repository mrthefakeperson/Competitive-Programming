#include <cstdio>
#include <algorithm>
#include <utility>

#define fst first
#define snd second
#define _ make_pair

using namespace std;
int visited[2][20005];
pair<int, int> segments[20005];
int n;
int a_(int aa){
	return (aa < 0) ? -aa : aa;
}
int HELP(bool leftRight, int row)
{
	int place, rr,o,ll; pair<int, int> nexxt, th;
	if (row == n){
		if (visited[leftRight][row] == 0){
			place = segments[n].snd;
			if (leftRight)
				place = segments[n].fst;
			rr = n - place;
			if (!leftRight)
				rr += (segments[n].snd - segments[n].fst)*2;
			visited[leftRight][row]= rr;
		}
		return visited[leftRight][row];
	}
	else{
		if (visited[leftRight][row] == 0){
			nexxt = segments[row + 1];
			th = segments[row];
			place = th.snd; o = th.fst;
			if (leftRight){
				place = th.fst; o = th.snd;
			}
			ll = HELP(true, row + 1) + th.snd - th.fst + a_(o - nexxt.fst);
			rr = HELP(false, row + 1) + th.snd - th.fst + a_(o - nexxt.snd);
			visited[leftRight][row] = min(ll, rr) + 1;
		}
		return visited[leftRight][row];
	}
}
int main()
{
	scanf("%i", &n);
	for (int e = 0; e < n; e++)
	{
		int a, b; scanf("%i%i", &a, &b);
		segments[e+1] = _(a, b);
	}segments[0] = _(1, 0);
	printf("%i\n", HELP(true, 0)-1);

	scanf(" ");
	return 0;
}