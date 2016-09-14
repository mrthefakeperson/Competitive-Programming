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

int cowHeights[1000005],heights[1000005],stuff[1000005];
int n,m,k;
bool attempt(int value)   //binary search this value
{
    for(let e=0;e<m;e++) stuff[e]=0;
    let pt1=0,pt2=0;
    while(pt1<n)
    {
        //printf("%i: %i,%i  /  %i,%i\n",value,pt1,cowHeights[pt1],pt2,cowHeights[pt2]);
        if(pt2==m) return false;
        if(stuff[pt2]==value) pt2++;
        if(pt2==m) return false;
        while(heights[pt2]<cowHeights[pt1]-k)
        {
            pt2++;
            if(pt2==m) return false;
        }
        if(heights[pt2]>cowHeights[pt1]) return false;
        stuff[pt2]++;
        pt1++;
    }
    return true;
}
int main()
{
    scanf("%i%i%i",&n,&m,&k);
    for(let e=0;e<n;e++) scanf("%i",&cowHeights[e]);
    for(let e=0;e<m;e++) scanf("%i",&heights[e]);
    sort(cowHeights,cowHeights+n);
    sort(heights,heights+m);
    let place=0,jump=n+1;
    if(!attempt(n+1)) printf("-1\n");
    else{
    while(jump>0)
    {
        //printf("%i,%i\n",place,jump);
        if(!attempt(place+jump)) place+=jump;
        jump/=2;
    }
    while(!attempt(place+1)) place++;
    printf("%i\n",place+1);
    }
	return 0;
}
