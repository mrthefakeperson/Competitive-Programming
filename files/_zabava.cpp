#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;
int buildings[1000001];
long long visited[101][501];
int a, b, c;
long long distribute(int clear, int student)
{
	long long clears = clear, students = student,upOne;
	if (clears == 0){
		return (students + 1)*students / 2;
	}
	else{
		upOne = students - ((students / (clears + 1))*(clears + 1));
		return upOne*(students / (clears + 1) + 1)*(students / (clears + 1) + 2) / 2 + ((clears + 1 - upOne)*(students / (clears + 1))*(students / (clears + 1) + 1) / 2);
	}
}
long long controlNoise(int w, int amt)
{
	long long mn;
	if (visited[w][amt] == 0){
		if (w == b){
			visited[w][amt] = distribute(amt, buildings[w]);
		}
		else{
			mn = distribute(0, buildings[w])+controlNoise(w+1,amt);
			for (int e = 1; e <= amt; e++)
			{
				mn = min(mn, controlNoise(w + 1, amt - e) + distribute(e, buildings[w]));
			}
			visited[w][amt] = mn;
		}
	}
	return visited[w][amt];
}
int main()
{
	
	scanf("%i%i%i", &a, &b, &c);
	for (int e = 0; e < a; e++)
	{
		int n; scanf("%i", &n);
		buildings[n]++;
	}
	printf("%llu", controlNoise(1, c));
	
	//int n, m; scanf("%i%i", &n, &m);
	//printf("%llu\n", distribute(n, m));
	scanf(" ");

	return 0;
}