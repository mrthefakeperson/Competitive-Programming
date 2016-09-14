#include <cstdio>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

char grid[505][505];
long long ways[505][505][505];
int main()
{
    freopen("palpath.in","r",stdin);
    freopen("palpath.out","w",stdout);
    
    int n;scanf("%i",&n);
    for(let e=0;e<n;e++)
    {
        for(let ee=0;ee<n;ee++)
        {
            scanf(" %c",&grid[e][ee]);
        }
    }
    ways[0][0][n-1]=1;
    for(let layer=0;layer<n;layer++)   //layer=x+y for all (x,y) in the diagonal
    {
        //printf("%i\n",layer);
        for(let x=0;x<=layer;x++)
        {
            let y=layer-x;
            for(let xx_=0;xx_<=layer;xx_++)
            {
                let yy_=layer-xx_;
                let xx=n-1-xx_,yy=n-1-yy_;
                if(x-1>=0 && xx+1<n && grid[x-1][y]==grid[xx+1][yy]){
                    ways[layer][x][xx]+=ways[layer-1][x-1][xx+1];
                }
                if(x-1>=0 && yy+1<n && grid[x-1][y]==grid[xx][yy+1]){
                    ways[layer][x][xx]+=ways[layer-1][x-1][xx];
                }
                if(y-1>=0 && xx+1<n && grid[x][y-1]==grid[xx+1][yy]){
                    ways[layer][x][xx]+=ways[layer-1][x][xx+1];
                }
                if(y-1>=0 && yy+1<n && grid[x][y-1]==grid[xx][yy+1]){
                    ways[layer][x][xx]+=ways[layer-1][x][xx];
                }
                ways[layer][x][xx]%=1000000007;
            }
        }
    }
    let acc=0LL;
    for(let e=0;e<n;e++)
    {
        acc+=ways[n-1][e][e];
        acc%=1000000007;
    }
    printf("%I64d\n",acc);

	return 0;
}
