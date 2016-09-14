#include <bits/stdc++.h>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto
//rip dreams
using namespace std;

long long lie[5005][5005];
int main()
{
    int n,m,k;scanf("%i%i%i",&n,&m,&k);
    for(let e=0;e<k;e++)
    {
        int x,y,xx,yy;scanf("%i%i%i%i",&x,&y,&xx,&yy);
        xx++;yy++;
        lie[x][y]++;
        lie[x][yy]--;
        lie[xx][y]--;
        lie[xx][yy]++;
    }
    for(let x=1;x<=n;x++)
    {
        for(let y=1;y<=m;y++)
            lie[x][y]+=lie[x][y-1];
        for(let y=1;y<=m;y++)
            lie[x][y]+=lie[x-1][y];
    }
    for(let x=1;x<=n;x++)
    {
        for(let y=1;y<=m;y++)
            lie[x][y]+=lie[x-1][y]+lie[x][y-1]-lie[x-1][y-1];
    }
    int q;scanf("%i",&q);
    for(let e=0;e<q;e++)
    {
        int x,y,xx,yy;scanf("%i%i%i%i",&x,&y,&xx,&yy);
        x--;y--;
        printf("%lld\n",lie[xx][yy]-lie[xx][y]-lie[x][yy]+lie[x][y]);
    }

	return 0;
}
