#include "bib.h"
int main()
{
    int choix;
    printf("    *************************************************\n");
    printf("    *                                               *\n");
    printf("    *   Bienvenu sur notre programme fascinant!     *\n");
    printf("    *                                               *\n");
    printf("    *************************************************\n\n\n");

    printf("Veuillez entrer : \n");
    printf("\n 1 pour utiliser la premier representaion \n");
    printf("\n 2 pour utiliser la 2 eme representaion \n");
    printf("\n input : ");
    scanf("%i",&choix);
    while(choix != 1 && choix != 2)
    {
        printf("\n Vous devez entrer soit 1 ou 2 !! \n");
        scanf("%i",&choix);
    }
    if(choix == 1)
    {
        Menu_1();
    }
    else if(choix == 2)
    {
        Menu_2();
    }


    return 0;
}
