#include <bits/stdc++.h>
#define _ make_pair

using namespace std;

int n;
int items[35];
bool visited[340][340][8][5][30];
void fireworks(int x, int y, int direction, int distance, int i)
{
    if (!visited[x][y][direction][distance][i]) {
        //printf("%i,%i %i %i %i\n", x,y,direction,distance,i);
        visited[x][y][direction][distance][i] = true;
        if (distance != 0) {
            int xx,yy;
            switch (direction) {
            case 0:
                xx = x; yy = y+1;
                break;
            case 1:
                xx = x+1; yy = y+1;
                break;
            case 2:
                xx = x+1; yy = y;
                break;
            case 3:
                xx = x+1; yy = y-1;
                break;
            case 4:
                xx = x; yy = y-1;
                break;
            case 5:
                xx = x-1; yy = y-1;
                break;
            case 6:
                xx = x-1; yy = y;
                break;
            case 7:
                xx = x-1; yy = y+1;
                break;
            }
            fireworks(xx,yy,direction,distance-1,i);
        }
        else if (i != n-1) {
            switch (direction) {
            case 0:
                fireworks(x-1,y+1,7,items[i+1],i+1);
                fireworks(x+1,y+1,1,items[i+1],i+1);
                break;
            case 1:
                fireworks(x,y+1,0,items[i+1],i+1);
                fireworks(x+1,y,2,items[i+1],i+1);
                break;
            case 2:
                fireworks(x+1,y+1,1,items[i+1],i+1);
                fireworks(x+1,y-1,3,items[i+1],i+1);
                break;
            case 3:
                fireworks(x+1,y,2,items[i+1],i+1);
                fireworks(x,y-1,4,items[i+1],i+1);
                break;
            case 4:
                fireworks(x+1,y-1,3,items[i+1],i+1);
                fireworks(x-1,y-1,5,items[i+1],i+1);
                break;
            case 5:
                fireworks(x,y-1,4,items[i+1],i+1);
                fireworks(x-1,y,6,items[i+1],i+1);
                break;
            case 6:
                fireworks(x-1,y-1,5,items[i+1],i+1);
                fireworks(x-1,y+1,7,items[i+1],i+1);
                break;
            case 7:
                fireworks(x-1,y,6,items[i+1],i+1);
                fireworks(x,y+1,0,items[i+1],i+1);
                break;
            }
        }
    }
}
int main()
{
    scanf("%i", &n);
    for (int e = 0; e < n; e++) {
        scanf("%i", &items[e]);
        items[e]--;
    }
    fireworks(170,170,0,items[0],0);
    int k = 0;
    for (int x = 0; x < 340; x++) {
        for (int y = 0; y < 340; y++) {
            bool acc = false;
            for (int e = 0; e < 8; e++)
                for (int ee = 0; ee < 5; ee++)
                    for (int eee = 0; eee < n; eee++)
                        acc = acc || visited[x][y][e][ee][eee];
            if (acc) k++;
        }
    }
    printf("%i\n", k);
}