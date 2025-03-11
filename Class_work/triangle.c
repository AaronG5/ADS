// Parasyti programa kuri tikrina ar 3 taskai (koordinates sveiki skaiciai +/-) yra stataus trikampio virsunes
#include <stdio.h>
#include <math.h>

int distance(int p1[], int p2[])
{
    return (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]);
}

int isRightTriangle(int d1, int d2, int d3)
{
    if((d1 > 0 && d2 > 0 && d3 > 0) 
        && ((d1 == d2 + d3) || (d2 == d1 + d3) || (d3 == d1 + d2)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{   
    int p1[2], p2[2], p3[2];
    
    scanf("%d%d%d%d%d%d", &p1[0], &p1[1], &p2[0], &p2[1], &p3[0], &p3[1]);

    int dist1 = distance(p1, p2);
    int dist2 = distance(p1, p3);
    int dist3 = distance(p2, p3);

    if(isRightTriangle(dist1, dist2, dist3))
    {
        printf("Statusis.\n");
    }
    else
    {
        printf("Ne statusis.\n");
    }

    return 0;
}