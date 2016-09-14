#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#ifdef getchar
#undef getchar
#endif
#define getchar() (*_pinp?*_pinp++:(_inp[fread(_pinp=_inp, 1, 4096, stdin)]='\0', *_pinp++))
char _inp[4097], *_pinp = _inp;
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(__=getchar()); x=(x<<3)+(x<<1)+__-'0');}while(0)

using namespace std;
char __;
int stuff[200005];
int groups[700], under[700], overhead[700];
const int SQ = 300;
vector<int> a;

int main()
{
	int m, n, q; scan(m); scan(n); scan(q);
	for (int e = 0; e < n; e++)
	{
		scan(stuff[e]);
		groups[e / SQ] += stuff[e];
		under[e / SQ]++;
	}
	for (int ee = 0; ee < q; ee++)
	{
		int op; scan(op);
		if (op == 1){
			int l, r, inc; scan(l); scan(r); scan(inc);
			l--; r--;
			int e = l;
			for (; e%SQ != 0 && e <= r; e++)
			{
				stuff[e] = (stuff[e] + inc) % m;
				groups[e / SQ] = (groups[e / SQ] + inc) % m;
			}
			for (; e + SQ <= r; e += SQ)
			{
				groups[e / SQ] = (groups[e / SQ] + inc*under[e / SQ]) % m;
				overhead[e / SQ] = (overhead[e / SQ] + inc) % m;
			}
			for (; e <= r; e++)
			{
				stuff[e] = (stuff[e] + inc) % m;
				groups[e / SQ] = (groups[e / SQ] + inc) % m;
			}
		}
		else{
			int l, r; scan(l); scan(r);
			l--; r--;
			int e = l; int a1 = 0, a2 = 0, a3 = 0;
			for (; e%SQ != 0 && e <= r; e++)
			{
				a1 += overhead[e / SQ] + stuff[e];
			}
			for (; e + SQ <= r; e += SQ)
			{
				a2 += groups[e / SQ]; a2 %= m;
			}
			for (; e <= r; e++)
			{
				a3 += overhead[e / SQ] + stuff[e];
			}
			printf("%i\n", (a1%m + a2 + a3%m) % m);
		}
	}

	scanf(" ");
	return 0;
}