#include <bits/stdc++.h>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

int main()
{
    int n,d;scanf("%i%i",&n,&d);
    let bottom=0;
    vector<pair<int,int> > hull;
    hull.push(_(0,-d));
    for(let e=0;e<n;e++)
    {
        int v;scanf("%i",&v);
        while(hull[bottom].snd<e-d) bottom++;
        let a=v+hull[bottom].fst;
        while((int)(hull.size())>bottom && hull[hull.size()-1].fst>=a) hull.pop_back();
        hull.push(_(a,e));
    }
    printf("%i\n",hull[hull.size()-1].fst);

	return 0;
}
