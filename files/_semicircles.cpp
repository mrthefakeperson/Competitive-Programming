#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define i(x) scanf("%i",&x)

using namespace std;
const int MOD = 1000000007;

int fillGap[4020];
pair<int, int> circles[1505];
vector<int> under[1505];
int takeAway[1505][4005];
int buffer[4005];

void precompute(int next, int repeat)
{
	if (repeat == 0) return;
	for (int e = 0; e < next; e += 2)
	{
		long long _ = (long long)fillGap[e] * (long long)fillGap[next - 2 - e];
		fillGap[next] = (fillGap[next] + _ % MOD) % MOD;
	}
	precompute(next + 2, repeat - 1);
}
bool sorter(pair<int, int> a, pair<int, int> b){ return a.snd - a.fst < b.snd - b.fst; }
int getWidth(int ind){ return circles[ind].snd - circles[ind].fst + 1; }
void process_(int anon)
{
	//printf("processing node %i\n", anon);
	int width = getWidth(anon);
	if (under[anon].empty()){
		takeAway[anon][0] = 1;
	}
	else{
		for (int e = 0; e < under[anon].size(); process_(under[anon][e++]));
		//map the head
		for (int e_ = 0; e_ <= getWidth(under[anon][0]); e_++)
		{
			takeAway[anon][e_] = takeAway[under[anon][0]][e_];
		}
		int N_SQUARED = getWidth(under[anon][0]);//optimization
		//combinations with the tail
		for (int e_ = 1; e_ < under[anon].size(); e_++)
		{
			for (int e = 0; e < 4003; buffer[e++] = 0);
			for (int e = 0; e <= getWidth(under[anon][e_]); e++)
			{
				//for (int ee = 0; ee <= width; ee++)
				for (int ee = 0; ee <= N_SQUARED;ee++)//optimization
				{
					if (e + ee <= width){
						long long _ = ((long long)takeAway[under[anon][e_]][e] * takeAway[anon][ee]) % MOD;
						buffer[e + ee] = ((long long)buffer[e + ee] + _) % MOD;
					}
				}
			}
			for (int e = 0; e <= width; e++) takeAway[anon][e] = buffer[e];
			//for (int e = 0; e <= width; printf("%i  ", buffer[e++])); printf("\n\n");
			N_SQUARED += getWidth(under[anon][e_]);//optimization
		}
	}
	long long acc = 0;
	for (int e = 0; e <= width; e++)
	{
		if (width - e - 2 >= 0){
			long long _ = (long long)takeAway[anon][e] * fillGap[width - e - 2];
			acc += _ % MOD;
		}
	}
	takeAway[anon][width] = acc % MOD;
	//for (int e = 0; e <= width; printf("%i  ", takeAway[anon][e++])); printf("\n\n");
}

int main()
{
	int n; i(n);
	int k; i(k);
	for (int e = 0; e < k; e++)
	{
		int a, b; i(a); i(b);
		circles[e] = _(a - 1, b - 1);
	}
	//precompute catalan numbers
	fillGap[0] = 1;
	precompute(2, n / 2 + 5);

	//tree
	sort(circles, circles + k, sorter);
	circles[k] = _(-1, n);
	//like a normal person
	for (int e_ = 0; e_ <= k; e_++)
	{
		for (int ee_ = e_ + 1; ee_ <= k; ee_++)
		{
			pair<int, int> e = circles[e_];
			pair<int, int> ee = circles[ee_];
			if (ee.fst<e.fst && ee.snd>e.snd){
				under[ee_].push(e_);
				break;
			}
		}
	}
	process_(k);
	printf("%i", takeAway[k][n + 2]);

	scanf(" ");
	return 0;
}