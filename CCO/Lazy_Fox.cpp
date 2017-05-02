#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>

//running out of stack space!!O NO

using namespace std;
pair<int, int> adj[2000][2000],allData[2000],pp;
int visited[2000][2000];
int n,x,y,root,dist,c,tmp,mx;
/*
void printVisit(){
	for (int e = 0; e < n; e++)
	{
		for (int ee = 0; ee < n; ee++)
		{
			//printf("(%i,%i) ", adj[e][ee].first, adj[e][ee].second);
			printf("%i ", visited[e][ee]);
		}
		printf("\n");
	}
	}	*/			bool sorter(pair<int, int> a, pair<int, int> b){ return a.first < b.first; }

int findInList(int inWhat, int forWhat){
	int place = n / 2, jump = n / 2;
	while (jump != 1)
	{
		jump /= 2;
		if (adj[inWhat][place].first == forWhat) break;
		else if (adj[inWhat][place].first > forWhat) place -= jump;
		else place += jump;
	}
	while (adj[inWhat][place].first < forWhat) place++;
	while (adj[inWhat][place].first > forWhat) place--;
	return place;
}

int explore(int x, int y){
	int ss;
	if (visited[x][y] != 0) return visited[x][y];
	else{
		//printf("(%i,%i)\t", adj[x][y].first, adj[x][y].second);
		//printf("%i,%i; trying %i,%i with %i,%i to the left\n", x, y, adj[x][y].second, adjHelper[adj[x][y].second][adj[x][y].first] - 1, x, y - 1);
		//ss = adjHelper[adj[x][y].second*2000+ adj[x][y].first];
		ss = findInList(adj[x][y].second, adj[x][y].first);
		while (adj[adj[x][y].second][ss].first == adj[x][y].first) ss--;
		visited[x][y] = max(1 + explore(adj[x][y].second, ss), explore(x, y - 1)); return visited[x][y];
	}
}

int main(){
	scanf("%i", &n);
	for (int e = 0; e < n; e++)
	{
		//int x, y; 
		scanf("%i%i", &x, &y);
		allData[e] = make_pair(x, y);
	}
	for (int e = 0; e < n; e++)
	{
		for (int ee = e; ee < n; ee++)
		{		//
			root = (allData[e].first - allData[ee].first)*(allData[e].first - allData[ee].first) + (allData[e].second - allData[ee].second)*(allData[e].second - allData[ee].second);
			adj[e][ee] = make_pair(root, ee);
			adj[ee][e] = make_pair(root, e);
		}
		sort(adj[e], adj[e] + n, sorter);
	}
	/*
	for (int e = 0; e < n; e++)
	{
		for (int ee = 0; ee < n; ee++)
		{
			explore(e, ee);
		}	
		explore(e, n - 1);
	}	*/
	for (int e = 0; e < n; e++)
	{
		visited[e][0] = 1;
	}
	int mm = 0;
	
	for (int e = 0; e < n; e++)
	{
		//pair<int, int> pp = allData[e];
		pp = allData[e];
		
		//find where the distance from (0,0) has its greatest other distance which is strictly less
			//
		dist = pp.first*pp.first + pp.second*pp.second; //printf("dist:%i\n", dist);
		for (int ee = n - 1; ee > -1; ee--)
		{
			if (adj[e][ee].first < dist){
				//int c=visited[e][ee];
				c = explore(e, ee);
				//printf("%i,%i", e, adj[e][ee].first);
				if (c > mm) mm = c; break;
			}
		}	
	}
	printf("%i\n", mm);
	  //printVisit();

	  //scanf(" ");
	return 0;
}