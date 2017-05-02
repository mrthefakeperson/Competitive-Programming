#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define fst first
#define snd second
#define _ make_pair
#define push push_back

using namespace std;

int items[405];
int visited[405][405];

int collect(int a,int b)   //inclusive
{
    if(visited[a][b]!=0){
        return visited[a][b];
    }
    if(a==b){
        visited[a][a]=items[a];
        return items[a];
    }
    if(a>b)
        return 0;
    visited[a][b]=-1;
    int lBound=a,rBound=b;
    while(lBound<rBound)
    {
        if(collect(a,lBound)==collect(rBound,b) && collect(lBound+1,rBound-1)!=-1){
            visited[a][b]=max(visited[a][b],collect(a,lBound)+collect(lBound+1,rBound-1)+collect(rBound,b));
        }
        if(collect(a,lBound)<collect(rBound,b)){
            lBound++;
        }
        else{
            rBound--;
        }
    }

    return visited[a][b];
}
int main()
{
    int n;scanf("%i",&n);
    for(int e=0;e<n;e++)
    {
        scanf("%i",&items[e]);
    }
    int accMax=0;
    for(int e=0;e<n;e++)
    {
        for(int ee=e;ee<n;ee++)
        {
            accMax=max(accMax,collect(e,ee));
        }
    }
    printf("%i\n",accMax);

	return 0;
}