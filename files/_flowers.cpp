#include <bits/stdc++.h>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;
const int SQ=500;
int ov[500],values[20005];
void add(int l,int r)
{
    let e=l+1;
    while(e<r)
    {
        if(e+SQ<=r && e%SQ==0){
            ov[e/SQ]++;
            e+=SQ;
        }
        else{
            values[e]++;
            e++;
        }
    }
}
int main()
{
    int n;scanf("%i",&n);
    for(let e=0;e<n;e++)
    {
        int a,b;scanf("%i%i",&a,&b);
        let aa=values[a]+ov[a/SQ],bb=values[b]+ov[b/SQ];
        printf("%i\n",aa+bb);
        values[a]-=aa;
        values[b]-=bb;
        add(a,b);
    }

	return 0;
}
