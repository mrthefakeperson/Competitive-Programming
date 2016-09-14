#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;
/*
int gcd(int a, int b)
{
	int aa = sqrt(a);
	int mmm = 1;
	for (int e = aa; e >0; e--)
	{
		if (a%e == 0){
			if (b%e == 0 && e > mmm) mmm = e;
			if (b % (a / e) == 0 && a / e > mmm) mmm = a / e;
		}
	}
	return mmm;
}
int visited[100000001];
*/
bool check(long xx)
{
	int x = xx;
	while (x % 6 == 0){ x /= 6; }
	if (x % 2 == 1){
		while (x>1 && x % 3 == 0){ x /= 3; }
	}
	else{
		while (x % 2 == 0){ x /= 2; }
	}
	return (x == 1);
}
bool rr = true;
int main()
{
	int n; scanf("%i", &n);
	int last; scanf("%i", &last);
	for (int e = 1; e < n; e++)
	{
		int nn; scanf("%i", &nn);
		/*
		int d = gcd(last, nn);
		int a = last / d, b = nn / d;
		//printf("%i %i\n", a, b);
		if (!check(a) || !check(b)){
			rr = false; break;
		}
		*/
		int a = last, b = nn;
		while (a % 2 == 0) a /= 2;
		while (a % 3 == 0) a /= 3;
		while (b % 2 == 0) b /= 2;
		while (b % 3 == 0) b /= 3;
		if (a != b){
			rr = false;
			break;
		}
		last = nn;
	}
	if (rr) { printf("Yes\n"); }
	else { printf("No\n"); }

	//scanf(" ");

	return 0;
}