#include <bits/stdc++.h>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

int r,c,h,w;
int quality[3005][3005],buffer[3005][3005];
bool check(int q)
{
    for(let e=0;e<r;e++)
    {
        for(let ee=0;ee<c;ee++)     //shifted by (+1,+1)
        {
            buffer[e+1][ee+1]=buffer[e][ee+1]+buffer[e+1][ee]-buffer[e][ee];
            if(quality[e][ee]<=q) buffer[e+1][ee+1]++;
            //printf("%i ",buffer[e+1][ee+1]);
        }//printf("\n");
    }
    for(let e=h;e<=r;e++)
    {
        for(let ee=w;ee<=c;ee++)
        {
            if(buffer[e][ee]-buffer[e-h][ee]-buffer[e][ee-w]+buffer[e-h][ee-w]>h*w/2)
                return true;
        }
    }
    return false;
}
int main()
{
    scanf("%i%i%i%i",&r,&c,&h,&w);
    for(let e=0;e<r;e++)
    {
        for(let ee=0;ee<c;ee++)
            scanf("%i",&quality[e][ee]);
    }
    let place=0,jump=r*c;
    while(jump>0)
    {
        //printf("%i\n",place+jump);
        if(!check(place+jump))
            place+=jump;
        jump/=2;
    }
    while(!check(place)) place++;
    printf("%i\n",place);

	return 0;
}