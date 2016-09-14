#include <cstdio>
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

int connect[500005];
bool visited[500005];
bool visited2[500005];
int ans[500005];
int follow(int node)
{
    if(visited[node]){
        return ans[node];
    }
    visited[node]=true;
    ans[node]=follow(connect[node])+1;
    return ans[node];
}
int follow2(int node)
{
    if(visited2[node]){
        return ans[node];
    }
    visited2[node]=true;
    ans[node]=max(ans[node],follow2(connect[node]));
    return ans[node];
}
int main()
{
    int n;scanf("%i",&n);
    for(let e=0;e<n;e++)
    {
        scanf("%i",&connect[e]);connect[e]--;
    }
    for(let e=0;e<n;e++)
    {
        follow(e);
        follow2(e);
        printf("%i\n",ans[e]);
    }

	return 0;
}
