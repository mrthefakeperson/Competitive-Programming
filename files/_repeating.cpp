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

int ll[105];
int lookup[305][305];
int HELP[305][305];
int ac[305];
int main()
{
    int n,R;scanf("%i%i",&n,&R);
    for(let e=0;e<n;e++) scanf("%i",&ll[e]);
    for(let e=1;e<=300;e++)
    {
        for(let ee=1;ee<=300;ee++) ac[ee]=0;
        for(let ee=0;ee<n;ee++)
        {
            let br=ll[ee];
            if(br>=e){
                ac[br]++;
                for(let e_=br+1;e_<=300;e_++)
                {
                    ac[e_]=max(ac[e_],ac[e_-1]);
                }
            }
        }
        for(let ee=e;ee<=300;ee++)
        {
            lookup[e][ee]=ac[ee];
        }
    }
/*
    for(let e=1;e<=4;e++)
    {
        for(let ee=1;ee<=4;ee++)
            printf("%i ",lookup[e][ee]);
        printf("\n");
    }
*/
    let leftovers=0;
    for(let e=1;e<=300;e++) leftovers=max(leftovers,lookup[e][e]);
    let ans=leftovers*R;
    for(let e=1;e<=min(n-1,R);e++)
    {
        for(let ee=e+1;ee<=300;ee++)
        {
            for(let e_=1;e_<ee;e_++)
            {
                HELP[e][ee]=max(HELP[e][ee],HELP[e-1][e_]+lookup[e_][ee]);
                ans=max(ans,HELP[e][ee]+leftovers*(R-e));
            }
        }
    }
    printf("%i\n",ans);
/*
    for(let e=1;e<=4;e++)
    {
        for(let ee=1;ee<=4;ee++)
            printf("%i ",HELP[e][ee]);
        printf("\n");
    }
*/
	return 0;
}
