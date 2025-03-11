#include <stdio.h>
#include <stdlib.h>

int sum(int x, int y);

int dalyba_su_liekana(int x, int y, int *liekana);

int sum(int x, int y)
{
    return x + y;
}

int dalyba_su_liekana(int x, int y, int *liekana)
{
    if(y == 0)
    {
        printf("Klaida, dalyba iš nulio negalima.\n");
        exit(1);
    }

    *liekana = x % y;

    return x / y;
}


int main()
{
    int x, y, liekana;

    printf("Įveskite pirmą skaičių:");
    scanf("%d", &x);

    printf("Įveskite antrą skaičių:");
    scanf("%d", &y);

    printf("Suma: %d\n", sum(x, y));
    
    printf("Dalyba: %d\n", dalyba_su_liekana(x, y, &liekana));

    printf("Liekana: %d\n", liekana);


    return 0;
}