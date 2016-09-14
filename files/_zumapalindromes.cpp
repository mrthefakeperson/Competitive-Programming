#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

int numbers[505];
int visited[505][505];
int HELP(int l,int r) //inclusive
{
    if(visited[l][r]==0){
        if(l>r) return 1;
        if(l==r)
            visited[l][r]=1;
        else{
            let accMin=999;
            if(numbers[l]==numbers[r])
                accMin=min(accMin,HELP(l+1,r-1));
            for(let e=l;e<r;e++)
            {
                accMin=min(accMin,HELP(l,e)+HELP(e+1,r));
            }
            visited[l][r]=accMin;
        }
    }
    return visited[l][r];
}
int main()
{
    int n;scanf("%i",&n);
    for(let e=0;e<n;e++)
        scanf("%i",&numbers[e]);
    printf("%i\n",HELP(0,n-1));

    return 0;
}
