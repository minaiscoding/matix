#include "bib.h"

#include "bib.h"

// Allouche Imene - Khadir Amina G1 representaion 1

//declaration du pointeur vers le maillon de la 1�re repr�sentation
typedef struct maillon *pointer;
// la machine abstraite
void alocate(pointer *p)
{
     *p = (maillon*)malloc(sizeof(maillon));
     (*p)->next = NULL;

}
void free_it(pointer p)
{
    free(p);
}

pointer to_next(pointer p)
{
     return(p->next);
}
int value(pointer p)
{
    return((p)->value);
}
int column_number(pointer p)
{
    return ((p)->column);
}
int line_number(pointer p)
{
    return ((p)->line);
}


void aff_adr(pointer *p,pointer q)
{
    (*p)->next = q;
}
void aff_value(pointer *p,int value)
{
    (*p)->value = value;
}
void aff_line(pointer *p , int line)
{
    (*p)->line = line;
}
void aff_column(pointer *p , int column)
{
    (*p)->column = column;
}
//demande des valeurs de la matrice
void ask_for_matrix(pointer *start ,int lines, int columns)
{
    // i <==> nombre de ligne de la matrice
    // j <==> nombre de colones de la matrice
    // number <==> la valeur du maillon � cr�er
    int i,j,number;

    for (i=0  ;i<lines ;i++)
    {
        for (j=0  ;j<columns ; j++)
        {
            printf("matrix[%i][%i] = ",i,j);
            scanf("%i",&number);

            //si la valeur n'est pas nulle on cr�e un maillon
            if (number!=0)
            {
                create_new_node(start,i,j,number);
            }

        }
        printf("\n");
    }}
//cr�er un maillon pour les valeurs non nulles
void create_new_node(pointer *start, int row,int column,int non_zero_element)
{
    pointer ptr, temp;

    //allouer l'espace pour le maillon � chainer
    alocate(&temp);
        if(temp==NULL)
        {
                printf("\nOut of Memory Space:\n");
                exit(0);
        }



    //remplir les champs du maillon par les donn�es
    aff_adr(&temp,NULL);
    aff_value(&temp,non_zero_element);
    aff_line(&temp,row);
    aff_column(&temp, column);


      //si la liste est vide alors le maillon est la tete de la liste
      if(*start==NULL)
        {
            *start=temp;
        }

      //sinon on parcours la liste jusqu'� la fin
      else
        {
                ptr=*start;
                while(to_next(ptr)!=NULL)
                {
                        ptr=to_next(ptr);
                }

                //on ins�re le maillon � la fin
                aff_adr(&ptr,temp);
        }
}

//afficher la liste sous forme de matrice en affichant les valeurs nulles manquantes
void PrintList(pointer *start,int lines_number, int columns_number)
{
        // i <==> nombre de ligne de la matrice
        // j <==> nombre de colones de la matrice
        int i,j;


        //si la liste est vide on affiche directement que des z�ros
        if(*start==NULL)
        {
            for (i=0  ;  i<lines_number ; i++)
            {
                for (j=0  ;j<columns_number ;j++)
                {
                    printf("\t %i",0);
                }
            }
            printf("\n");
        }


        //sinon
        else
        {
                pointer ptr;
                ptr =*start;
                for (i=0  ;  i<lines_number ; i++)
                {
                    for (j=0  ;j<columns_number ;j++)
                    {
                        //si matrix[i][j] existe dans la liste donc on affiche sa valeur
                        if (ptr!=NULL && line_number(ptr)== i && column_number(ptr)==j)
                        {
                            printf("%d\t",value(ptr));
                            ptr=to_next(ptr);
                        }

                        //sinon alors sa valeur est nulle donc on affiche 0
                        else
                        {
                            printf("%d\t",0);
                        }
                    }
                    printf("\n");
                }
        }
}

//creation de la sous matrice
void matrix_transposee(pointer *new_head, pointer *start)
{
    //si la liste est vide alors on retourne directement la variable pointer *new_head comme �tant un pointer NIL
    if(*start==NULL)
    {
        exit(0);
    }


    //sinon
    else
    {
        pointer here;
        here =*start;
        // on parcours la liste et on inverse le num�ro de ligne et de colone � chaque reprise
        //on les ins�re dans la place convenable grace � la foncion insert_node_order
        while(here!=NULL)
        {
            insert_node_order(new_head ,line_number(here),column_number(here),value(here));
            here=to_next(here);
        }
    }
}


//inserer le maillon par ordre de ligne et de colone (son emplacement dans la matrice)
void insert_node_order(pointer *new_head , int line, int column, int value)
{
    pointer temp,ptr;

    //alloueur le maillon � inserer
    alocate(&temp);
    if(temp==NULL)
    {
        printf("\nOut of Memory Space:\n");
        exit(0);
    }

    //remplir les champ du maillon par les donn�es
    aff_adr(&temp,NULL);
    aff_value(&temp,value);
    aff_line(&temp,column);
    aff_column(&temp,line);


    //si la liste est vide alors le maillon sera dans la tete
    if(*new_head==NULL)
    {
        *new_head=temp;
    }


    //sinon
    else
    {
        ptr=*new_head;
        //insertion au d�but si l'emplacement du maillon deverait etre avant l'emplacement du maillon qui se retrouve dans la tete
        if ((line_number(ptr)>column) || (line_number(ptr)==column && column_number(ptr)>line))
        {
            aff_adr(&temp,*new_head);
            //le maillon devient la tete
            *new_head=temp;
        }


        //insertion au milieu/fin par rapport � la valeur de ligne et colone du maillon (emplacement dans la liste)
        else
        {
            //on parcours jusq'� y arriver au bon emplacement
            while(to_next(ptr)!=NULL && ((line_number(ptr)<column) || (line_number(ptr)==column && column_number(ptr)<line-1)))
            {
                ptr=to_next(ptr);
            }

            //on ins�re le maillon dans l'emplacement convenable
            aff_adr(&temp,to_next(ptr));
            aff_adr(&ptr, temp);
        }
    }
}


void extraction_submatrix(pointer *new_head, pointer *start ,int lines , int columns)
{
    //dl <==> la ligne de d�part
    //dc <==> la colone de d�part
    //al <==> la ligne d'arriv�e
    //ac <==> la colone d'arriv�e
    int dl,dc,al,ac;

    //�diter les valeurs des lignes et colones de d�part et d'arriv�e
    submatrix_conditions(&dl,&dc,&al,&ac,lines,columns);

    pointer ptr;
    ptr=*start;

    //parcourir la matrice de d�part
    while(ptr!=NULL && (line_number(ptr)<al || (line_number(ptr)== al && column_number(ptr)<=ac)))
    {
        //on extrait que les maillons qui sont entre [dl,al] et [dc,ac]
        if (line_number(ptr)>=dl && column_number(ptr)>=dc && column_number(ptr)<=ac)
            //creer le maillon en mettant � jour les nouvelles valeur des num�ros de lignes et colones
            create_new_node(new_head,line_number(ptr)-dl, column_number(ptr)-dc,value(ptr));

        ptr=to_next(ptr);
    }


    printf("la sous-matrice a �t� cr�e dynamiquement avec succ�s etes vous sur de vous contenter de �a sans l'afficher? \n");
    printf("si vous voulez l'afficher pour v�rifier sa cr�ation tapez y sinon n : ");
    char answer;
    scanf(" %c",&answer);
    if (answer =='y')
    {
        printf("\n");
        PrintList(new_head, al-dl+1, ac-dc+1);
        printf("\n");
    }
}

//�les conditions sur la lignes et colone de d�part et d'arriv�e
void submatrix_conditions(int* dl,int*dc,int*al,int*ac,int lines , int columns)
{

    //dl <==> la ligne de d�part
    //dc <==> la colone de d�part
    //al <==> la ligne d'arriv�e
    //ac <==> la colone d'arriv�e

     printf("extraction d'une sous matrice aura besoin d'un point de d�part et d'arriv�...\n");

     printf("ligne de d�part: ");
     scanf("%i",dl);
     while(*dl>lines-1)
     {
         printf("d�passement de nombre de lignes de matrice saisie, saisissez une ligne de d�part plus petite:");
         scanf("%i",dl);
     }



     printf("colone de d�part: ");
     scanf("%i",dc);
     while(*dc>columns-1)
     {
         printf("d�passement de nombre de colones de matrice saisie, saisissez une colone de d�part plus petite:");
         scanf("%i",dc);
     }


     printf("ligne d'arriv�e: ");
     scanf("%i",al);
     while(*al>lines-1 || *al<*dl)
     {
         if(*al>lines-1)
         {
                printf("d�passement de nombre de lignes de matrice saisie, saisissez une ligne d'arriv�e plus petite:");
                scanf("%i",al);
         }
         else
         {
                printf("la ligne de d'arriv�e doit etre sup�rieure ou �gale � la ligne de d�part try another: ");
                scanf("%i",al);
         }
     }


     printf("colone d'arriv�e: ");
     scanf("%i",ac);
     while(*ac>columns-1 || (*ac<*dc))
     {
         if (*ac>columns-1)
         {
            printf("d�passement de nombre de colones de matrice saisie, saisissez une colone d'arriv�e plus petite:");
            scanf("%i",ac);
         }
         else
         {
            printf("la colone d'arriv� doit etre sup�rieure ou �gale � la colone de d�part, try another: ");
            scanf("%i",ac);
         }
     }
}

//additionner deux matrices de tetes : pointer* first_matrix et pointer* second_matrix
pointer add_matrixes(pointer *first_matrix , pointer *second_matrix , int lines,int columns,int additions)
{

    pointer ptr1,ptr2,temp,another_matrix,result;
    result=NULL;
    another_matrix=NULL;
    ptr1 = *first_matrix;
    ptr2 = *second_matrix;

    if (additions==2)
    {
                //parcourir les deux matrices au meme temps pour un meilleur coup de temps
                while (ptr1 !=NULL && ptr2 !=NULL)
                {
                    //si le nombre de ligne et colones des deux maillons sont identiques
                    if(line_number(ptr1)==line_number(ptr2) && column_number(ptr1)==column_number(ptr2))
                    {
                        //on cr�e le maillon et la valeur de son champ est �gale � la somme des valeurs du champ value des deux matrices
                        create_new_node(&result,line_number(ptr1),column_number(ptr1),value(ptr1)+value(ptr2));

                        //on avance dans les deux listes avec un pas (maillon)
                        ptr1=to_next(ptr1);
                        ptr2=to_next(ptr2);
                    }


                    //sinon
                    else
                    {
                        //si le maillon de 1�re liste a un emplacement inf�rieur � celui de la 2�me liste
                        if (line_number(ptr1)<line_number(ptr2) || (line_number(ptr1)==line_number(ptr2) && column_number(ptr1)<column_number(ptr2)))
                        {
                            //on cr�e le maillon correspendannt au maillon de la 1�me liste
                            //la valeur du champs value == valeur du champs value du maillon de la 1ere liste
                            create_new_node(&result,line_number(ptr1),column_number(ptr1),value(ptr1));
                            //on avance que dans la 1ere liste
                            ptr1=to_next(ptr1);
                        }


                        //sinon si le maillon de 2�me liste a un emplacement inf�rieur � celui de la 1�me liste
                        else
                        {
                            //on cr�e le maillon correspendannt au maillon de la 2�me liste
                            //la valeur du champs value == valeur du champs value du maillon de la 2eme liste
                            create_new_node(&result,line_number(ptr2),column_number(ptr2),value(ptr2));
                            //on avance que dans la 2eme liste
                            ptr2=to_next(ptr2);
                        }
                    }
                }


                //tant qu'on est pas arriv� � la fin de la 1�re liste
                while (ptr1 !=NULL)
                {
                        //on cr�e les maillons correspendants aux maillons restants de la la 1�re liste
                        create_new_node(&result,line_number(ptr1),column_number(ptr1),value(ptr1));
                        ptr1=to_next(ptr1);
                }

                //tant qu'on est pas arriv� � la fin de la 2�me liste
                while (ptr2 !=NULL)
                {
                    //on cr�e les maillons correspendants aux maillons restants de la la 2�me liste
                    create_new_node(&result,line_number(ptr2),column_number(ptr2),value(ptr2));
                    ptr2=to_next(ptr2);
                }
         return (result);
    }


    else
    {
            printf("\n******** lire une matrice **********\n");
            ask_for_matrix(&another_matrix,lines,columns);
            temp = add_matrixes(first_matrix,second_matrix,lines,columns,2);
            return add_matrixes(&temp,&another_matrix,lines,columns,additions-1);
    }
}
void operation_or(pointer *first_matrix ,pointer* second_matrix , pointer *result)
{
    pointer ptr1, ptr2;
    ptr1 = *first_matrix;
    ptr2 = *second_matrix;


    //on parcours les deux listes au meme temps pour un meilleur coup de temps
    while (ptr1 !=NULL && ptr2 !=NULL)
    {
        //si le nombre de ligne et colones des deux maillons sont identiques
        if(line_number(ptr1)==line_number(ptr2) && column_number(ptr1)==column_number(ptr2))
        {
           //on cr�e le maillon et la valeur de son champ est �gale � 1
           create_new_node(result,line_number(ptr1),column_number(ptr1),1);
           //on avance dans les deux listes avec un pas (maillon)
           ptr1=to_next(ptr1);
           ptr2=to_next(ptr2);
        }


        else
        {
            //sinon si le maillon de 1�re liste a un emplacement inf�rieur � celui de la 2�me liste
            if (line_number(ptr1)<line_number(ptr2) || (line_number(ptr1)==line_number(ptr2) && column_number(ptr1)<column_number(ptr2)))
            {
                //on cr�e le maillon correspendannt au maillon de la 1�me liste
                //la valeur du champs value  est �gale � 1
                create_new_node(result,line_number(ptr1),column_number(ptr1),1);
                //on avance que dans la 1ere liste
                ptr1=to_next(ptr1);
            }

            //sinon si le maillon de 2�me liste a un emplacement inf�rieur � celui de la 1�me liste
            else
            {
                //on cr�e le maillon correspendannt au maillon de la 2�me liste
                //la valeur du champs value est �gale � 1
                create_new_node(result,line_number(ptr2),column_number(ptr2),1);
                //on avance que dans la 2eme liste
                ptr2=to_next(ptr2);
            }
        }
    }

    //tant qu'on est pas arriv� � la fin de la 1�re liste
    while (ptr1 !=NULL)
    {
            //on cr�e les maillons correspendants aux maillons restants de la la 1�re liste
            create_new_node(result,line_number(ptr1),column_number(ptr1),1);
            ptr1=to_next(ptr1);
    }

    //tant qu'on est pas arriv� � la fin de la 2�me liste
    while (ptr2 !=NULL)
    {
        //on cr�e les maillons correspendants aux maillons restants de la la 2�me liste
        create_new_node(result,line_number(ptr2),column_number(ptr2),1);
        ptr2=to_next(ptr2);
    }
}

void operation_oux(pointer *first_matrix ,pointer* second_matrix , pointer *result)
{
    pointer ptr1 , ptr2;
    ptr1 = *first_matrix;
    ptr2 = *second_matrix;


    //parcourir les deux matrices au meme temps pour un meilleur coup de temps
    while (ptr1 !=NULL && ptr2 !=NULL)
    {
        //si le nombre de ligne et colones des deux maillons sont identiques
        if(line_number(ptr1)==line_number(ptr2) && column_number(ptr1)==column_number(ptr2))
        {
            //on avance dans les deux listes avec un pas (maillon) sans cr�er le maillon
            ptr1=to_next(ptr1);
            ptr2=to_next(ptr2);
        }

        //sinon
        else
        {
            //si le maillon de 1�re liste a un emplacement inf�rieur � celui de la 2�me liste
            if (line_number(ptr1)<line_number(ptr2) || (line_number(ptr1)==line_number(ptr2) && column_number(ptr1)<column_number(ptr2)))
            {
                //on cr�e le maillon correspendannt au maillon de la 1�me liste avec une valeur de 1
                create_new_node(result,line_number(ptr1),column_number(ptr1),1);
                //on avance que dans la 1ere liste
                ptr1=to_next(ptr1);
            }

            //sinon si le maillon de 2�me liste a un emplacement inf�rieur � celui de la 1�me liste
            else
            {
                //on cr�e le maillon correspendannt au maillon de la 2�me liste avec une valeur de 1
                create_new_node(result,line_number(ptr2),column_number(ptr2),1);
                //on avance que dans la 2eme liste
                ptr2=to_next(ptr2);
            }
        }
    }



    //tant qu'on est pas arriv� � la fin de la 1�re liste
    while (ptr1 !=NULL)
    {
            //on cr�e les maillons correspendants aux maillons restants de la la 1�re liste
            create_new_node(result,line_number(ptr1),column_number(ptr1),1);
            ptr1=to_next(ptr1);
    }

    //tant qu'on est pas arriv� � la fin de la 2�me liste
    while (ptr2 !=NULL)
    {
        //on cr�e les maillons correspendants aux maillons restants de la la 2�me liste
        create_new_node(result,line_number(ptr2),column_number(ptr2),1);
        ptr2=to_next(ptr2);
    }
}


void operation_et(pointer *first_matrix ,pointer* second_matrix , pointer *result)
{
    pointer ptr1 ,ptr2;
    ptr1 = *first_matrix;
    ptr2 = *second_matrix;

    //parcourir les deux matrices au meme temps pour un meilleur coup de temps
    while (ptr1 !=NULL && ptr2 !=NULL)
    {
        //si le nombre de ligne et colones des deux maillons sont identiques
        if(line_number(ptr1)==line_number(ptr2) && column_number(ptr1)==column_number(ptr2))
        {
            //on cr�e le maillon correspendannt au maillon des deux listes
            create_new_node(result,line_number(ptr1),column_number(ptr1),1);
            //on avance dans les deux listes avec un pas (maillon)
            ptr1=to_next(ptr1);
            ptr2=to_next(ptr2);
        }

        else
        {
            //si le maillon de 1�re liste a un emplacement inf�rieur � celui de la 2�me liste
            if (line_number(ptr1)<line_number(ptr2) || (line_number(ptr1)==line_number(ptr2) && column_number(ptr1)<column_number(ptr2)))
                //on avance que dans la 1ere liste
                ptr1=to_next(ptr1);

            //sinon si le maillon de 2�me liste a un emplacement inf�rieur � celui de la 1�me liste
            else
                //on avance que dans la 2eme liste
                ptr2=to_next(ptr2);
        }
    }
}


void operation_non(pointer *start, pointer *result, int lines, int columns)
{
    pointer ptr;
    ptr = *start;
    //i <==> le nombre de lignes de la matrice
    //j <==> le nombre de colones d ela matrice
    int i,j;

    for (i=0  ;i<lines; i++)
    {
        for (j=0  ;j<columns ;j++)
        {
            if (ptr==NULL || line_number(ptr)>i || (line_number(ptr)==i && column_number(ptr)>j))
                create_new_node(result,i,j,1);
            else
                ptr=to_next(ptr);
        }
    }
}


void division_sous_bloc_conditions(int lines, int columns, int *line_size, int *column_size)
{

    //line_size <==> le nombre de ligne demand� dans les sous-blocs
    //column_size <==> le nombre de colones demand� dans les sous-blocs

    printf("combien de lignes vous voulez avoir dans vos sous-blocs: ");
    scanf("%i",line_size);
    while(lines % (*line_size) !=0)
    {
        printf("�a devait etre un multiple de nombre de ligne de la matrice m�re try again: ");
        scanf("%i",line_size);
    }


    printf("combien de colones vous voulez avoir dans vos sous-blocs: ");
    scanf("%i",column_size);

    while(columns % (*column_size) !=0)
    {
        printf("�a devait etre un multiple de nombre de colone de la matrice m�re try again: ");
        scanf("%i",line_size);
    }
}

void division_sous_bloc(pointer *start, int lines, int columns)
{
    //line_size <==> le nombre de ligne demand� dans les sous-blocs
    //column_size <==> le nombre de colones demand� dans les sous-blocs
    int line_size, column_size;

    //r�cup�rer les valeurs de line_size et column_size
    division_sous_bloc_conditions(lines,columns,&line_size,&column_size);


    //le nombre de sous blocs est �gale �:
    int blocs =(lines / line_size) * (columns / column_size);

    //stocker les tete des sous blocs cr�es dans un tableau
    pointer headers_list[blocs];


    //initialiser les listes des sous blocs � des listes vide NIL
    int i;
    for (i=0  ;i<blocs  ;i++)
    {
        headers_list[i] = NULL;
    }

    pointer ptr;
    ptr = *start;
    //parcourir la liste
    while (ptr!=NULL)
    {
        //i est l'index ou stocker le maillon dans l'index sp�cifi� dans le tableau
        //i est donn� par l'equation:
        i=(columns/column_size)*(line_number(ptr)/line_size)+(column_number(ptr)/column_size);
        //creer le maillon avec mise � jour du num�rode ligne et colone de chaque maillon
        create_new_node(&headers_list[i] ,(line_number(ptr)%line_size),(column_number(ptr)%column_size),value(ptr));
        ptr = to_next(ptr);
    }





    //afficher les sous blocs cr�es
    printf("\n\nles sous-blocs ont �t� cr�es dynamiquement avec succ�s etes vous sur de vous contenter de �a sans les afficher? \n");
    printf("si vous voulez les afficher pour v�rifier leurs cr�ation tapez y sinon n : ");
    char answer;
    scanf(" %c",&answer);
    if (answer =='y')
    {
        for (i=0  ;i<blocs  ;i++)
        {
            printf("\n\n le sous blocs num�ro %i: \n",i);
            PrintList(&headers_list[i],line_size,column_size);
        }
    }

}
void search_the_node(pointer *start,int row, int column,pointer* node,int*found)
{
   pointer ptr;
   *found=1;
   ptr=*start;
   //tantt qu'on est pas arriv� � l'emplacement du maillon on avance
   while(ptr!=NULL && ((line_number(ptr)<row || (line_number(ptr)==row && column_number(ptr)<column))))
       ptr=to_next(ptr);

    //si le maillon existe on retourne le maillon sinon found=1 donc il n'existe pas
    if (ptr!=NULL && line_number(ptr)==row && column_number(ptr)==column)
    {
        *found=0;
        *node=ptr;
    }
}
void multiply_matrixes(pointer* first_matrix, pointer* second_matrix, pointer *result ,int lines,int colines,int columns)
{
    // lines <==> nombre de ligne de la 1ere matrice
    // collines <==> nombre de colone de la 1ere matrice (nombre de lignes de la 2eme matrice �galement)
    // columns<==> nombre de colones de la 2eme matrice
    pointer node1,node2;
    int i,j,k,sum,found1,found2;
    for (i=0  ;i<lines ;i++)
    {
        for (j=0  ;j<columns  ;j++)
        {
            sum=0;
            for (k=0  ;k<colines ;k++)
            {
                //rechercher les maillons correspendants pour faire la multiplication
                search_the_node(first_matrix,i,k,&node1,&found1);
                search_the_node(second_matrix,k,j,&node2,&found2);
                //s'ils existent alors on retourne les maillon et on multiplie leur valeurs
                if (found1==0 && found2==0)
                    sum+=value(node1)*value(node2);
            }

            if (sum != 0)
                //si le resultat n'est pas nulle on cr�e le maillon
                create_new_node(result,i,j,sum);
        }
    }

}


//lib�rer une liste
void freeList(pointer *start)
{
   pointer tmp;
   //parcourir la liste
   while (*start != NULL)
    {
       //liberer maillon par maillon
       tmp = *start;
       *start = to_next(*start);
       free_it(tmp);
    }
}

//afficher les maillons cr�es de la liste
void display(pointer *start)
{
        pointer ptr;
        //si la liste est vide on l'indique
        if(start==NULL)
        {
                printf("\nList is empty:\n");
                return;
        }

        //sinon on parcourt la liste et � chaque fois on indique les champs ligne, colone et valeur cr�es
        else
        {
                ptr=*start;
                printf("\nLine\tColumn\tValue\n");
                while(ptr!=NULL)
                {
                        printf("%d\t",line_number(ptr));
                        printf("%d\t",column_number(ptr));
                        printf("%d\t",value(ptr) );
                        ptr=to_next(ptr);
                        printf("\n");
                }
        }
}

void Menu_1()
{

    //le menu et les options
    printf("    *************************************************\n");
    printf("    *                                               *\n");
    printf("    *  Vous avez choisi la 1ere representation      *\n");
    printf("    *                                               *\n");
    printf("    *************************************************\n\n\n");

    printf("veuillez consulter nos diverses fonctions et en choisir une:\n");
    printf("\n    1-  Lecture d'une matrice creuse enti�re\n");
    printf("\n    2-  Affichage d'une matrice creuse enti�re\n");
    printf("\n    3-  Extraction d'une sous matrice\n");
    printf("\n    4-  Division d'une matrice en sous-blocs de taille �gale\n");
    printf("\n    5-  Transpos�e d'une matrice\n");
    printf("\n    6-  Addition de deux ou plusieurs matrices\n");
    printf("\n    7-  Multiplication de deux matrices\n");
    printf("\n    8-  Op�rations logiques : NON\n");
    printf("\n    9-  Op�rations logiques : ET\n");
    printf("\n    10-  Op�rations logiques : OU\n");
    printf("\n    11-  Op�rations logiques : OUX\n");




    //le choix des options
    printf("\n\nsaisissez le num�ro de votre option: ");
    int option;
    scanf(" %i",&option);
    while (option<1 || option>11)
    {
        printf("pas d'option correspondante � un tel num�ro saisissez un autre: ");
        scanf(" %i",&option);
    }

    printf("***************************************     \n");





            printf("\nsuper! maintenant pour cr�er la matrice on aura besoin de plus d'info sur celle ci: \n\n");
            printf("nombre de lignes : ");
            int lines;
            scanf("%i",&lines);

            printf("nombre de colones ");
            int columns;
            scanf("%i",&columns);

            pointer start=NULL;
            ask_for_matrix(&start,lines,columns);



                switch(option)
                {
                        case 1:



                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *   Lecture et creation de la matrice creuse:   *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        printf("\nla matrice a �t� cr�e dynamiquement avec succ�s etes vous sur de vous contenter de �a sans l'afficher? \n");
                                        printf("si vous voulez l'afficher pour v�rifier sa cr�ation tapez y sinon n : ");
                                        char answer;
                                        scanf(" %c",&answer);
                                        if (answer =='y')
                                        {
                                            printf("\n");
                                            PrintList(&start,lines, columns);
                                            printf("\n");
                                            display(&start);
                                        }
                                        freeList(&start);
                                        break;



                        case 2:

                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *      affichage entier de la matrice creuse:   *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        PrintList(&start,lines, columns);
                                        freeList(&start);
                                        break;



                        case 3:


                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *      soustraction d'une sous matrice:         *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        pointer submatrix_head= NULL;
                                        extraction_submatrix(&submatrix_head, &start ,lines, columns);


                                        printf("\n\n le contenu de la liste cr�e: \n");
                                        display(&submatrix_head);

                                        freeList(&start);
                                        freeList(&submatrix_head);
                                        break;



                        case 4:


                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *      division de la matrice en sous blocs:    *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        division_sous_bloc(&start,lines,columns);
                                        freeList(&start);
                                        break;




                        case 5:

                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *    creation de la transpos�e de la matrice:   *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        pointer new_head = NULL;
                                        matrix_transposee(&new_head,&start);

                                        printf("\n\n l'affichage entier de la transpos�e: \n");
                                        PrintList(&new_head , columns, lines);
                                        printf("\n\n le contenu de la liste cr�e: \n");
                                        display(&new_head);

                                        freeList(&start);
                                        freeList(&new_head);
                                        break;



                        case 6:

                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *   l'addition de deux ou plusieurs matrices    *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        printf("une deuxi�me matrice de meme taille est indisponsable inserez ses valeurs:\n");

                                        pointer second_matrix=NULL;
                                        pointer result=NULL;
                                        ask_for_matrix(&second_matrix,lines,columns);
                                        printf("combien de matrice voudriez-vous additionner?");
                                        int additions;
                                        do
                                        {
                                            printf("nombre de matrices � additionner(sup�rieure ou �gale � 2): ");
                                            scanf("%i",&additions);
                                        }
                                        while(additions<2);


                                        printf("\n***************************************     \n\n");
                                        //add_matrixes(&start,&second_matrix,&result);
                                        result=add_matrixes(&start,&second_matrix,lines,columns,additions);

                                        printf("\n\n l'affichage entier du r�sultat de l'addition des deux matrices: \n");
                                        PrintList(&result,lines, columns);
                                        printf("\n\n le contenu de la liste cr�e: \n");
                                        display(&result);

                                        freeList(&start);
                                        freeList(&second_matrix);
                                        freeList(&result);
                                        break;


                        case 7:


                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *      la multiplication de deux matrices:      *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        printf("    une deuxi�me matrice est indispensable pour la multiplication: \n");
                                        printf("    le nombre de lignes de celles ci �gale aux nombre de colones de la premi�re il en manque que:\n");
                                        second_matrix=NULL;
                                        result=NULL;

                                        printf("    le nombre de colones:  ");
                                        int col2;
                                        scanf("%i",&col2);
                                        ask_for_matrix(&second_matrix,columns,col2);
                                        multiply_matrixes(&start,&second_matrix,&result,lines,columns,col2);

                                        printf("\n\n l'affichage entier du r�sultat de la multiplication des deux matrices: \n");
                                        PrintList(&result,lines,col2);
                                        printf("\n\n le contenu de la liste cr�e: \n");
                                        display(&result);

                                        freeList(&start);
                                        freeList(&second_matrix);
                                        freeList(&result);
                                        break;

                        case 8:


                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *           l'operation logique NON:            *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        result=NULL;
                                        operation_non(&start,&result,lines,columns);

                                        printf("\n\n l'affichage entier du r�sultat du NON logique de la matrice: \n");
                                        PrintList(&result,lines, columns);
                                        printf("\n\n le contenu de la liste cr�e: \n");
                                        display(&result);

                                        freeList(&start);
                                        freeList(&result);
                                        break;




                        case 9:


                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *           l'operation logique ET:             *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        printf("une deuxi�me matrice de meme taille est indisponsable inserez ses valeurs:\n");
                                        second_matrix=NULL;
                                        result=NULL;
                                        ask_for_matrix(&second_matrix,lines,columns);
                                        printf("\n      ***************************************     \n\n");
                                        operation_et(&start,&second_matrix,&result);

                                        printf("\n\n l'affichage entier du r�sultat du ET logique des deuxs matrices: \n");
                                        PrintList(&result,lines, columns);
                                        printf("\n\n le contenu de la liste cr�e: \n");
                                        display(&result);

                                        freeList(&start);
                                        freeList(&second_matrix);
                                        freeList(&result);
                                        break;




                        case 10:


                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *            l'operation logique OU:            *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        printf("une deuxi�me matrice de meme taille est indisponsable inserez ces ses valeurs:\n");
                                        second_matrix=NULL;
                                        result=NULL;
                                        ask_for_matrix(&second_matrix,lines,columns);
                                        printf("\n      ***************************************     \n\n");
                                        operation_or(&start,&second_matrix,&result);

                                        printf("\n\n l'affichage entier du r�sultat du OU logique des deuxs matrices: \n");
                                        PrintList(&result,lines, columns);
                                        printf("\n\n le contenu de la liste cr�e: \n");
                                        display(&result);

                                        freeList(&start);
                                        freeList(&second_matrix);
                                        freeList(&result);
                                        break;




                        case 11:


                                        printf("    *************************************************\n");
                                        printf("    *                                               *\n");
                                        printf("    *      l'operation logique OU Exclusif:         *\n");
                                        printf("    *                                               *\n");
                                        printf("    *************************************************\n\n\n");
                                        printf("une deuxi�me matrice de meme taille est indisponsable inserez ces ses valeurs:\n");
                                        second_matrix=NULL;
                                        result=NULL;
                                        ask_for_matrix(&second_matrix,lines,columns);
                                        printf("\n      ***************************************     \n\n");
                                        operation_oux(&start,&second_matrix,&result);

                                        printf("\n\n l'affichage entier du r�sultat du OU exclusif logique des deuxs matrices: \n");
                                        PrintList(&result,lines, columns);
                                        printf("\n\n le contenu de la liste cr�e: \n");
                                        display(&result);

                                        freeList(&start);
                                        freeList(&second_matrix);
                                        freeList(&result);
                                        break;
                }

}






//************************************************************
// Khadir Amina - imene alouch G1
// la 2eme representation
// definition des type utilis�s
typedef struct ligne_ll* ptr_l;
typedef struct colone_ll* ptr_c;
typedef struct blocs* ptr_s;

// la machine abstraite
// 1- allouer
void allouer_ligne(ptr_l *p){
    *p = (ligne_ll*)malloc(sizeof(ligne_ll));
    (*p)->pointeur_down = NULL;
    (*p)->pointeur_droit = NULL;

}
void allouer_bloc(ptr_s *p){
    *p = (blocs*)malloc(sizeof(blocs));
    (*p)->suivant = NULL;
    (*p)->sM = NULL;

}
void allouer_colone(ptr_c *p){
    *p = (colone_ll*)malloc(sizeof(colone_ll));
    (*p)->suivant = NULL;

}
// 2- Liberer
void liberer_l(ptr_l p){
free(p);}
void liberer_c(ptr_c p){
free(p);}
// suivant
ptr_c suivant_c(ptr_c p) // la colone suivante d4une colone
{
    return ((p)->suivant);
}
ptr_l suivant_l(ptr_l p) // la ligne suivante d4une ligne
{
    return ((p)->pointeur_down);}
ptr_c suivant_lc(ptr_l p) // la premi�re colone de la ligne donn�e
    {
        return ((p)->pointeur_droit);
    }

ptr_s suivant_b(ptr_s b)
{
    return b->suivant;
}
// valeur et qutre donn�s
int valeur_c(ptr_c p)
{
    return((*p).val);
}
ptr_l mat(ptr_s p)
{
    return (p)->sM;
}
int num_colone(ptr_c p)
{
    return p->cln;
}
int num_ligne(ptr_l p)
{
    return p->ligne;
}
// affectation
void aff_mat(ptr_s *p,ptr_l mat) // pour sauvgarder le sous-bloc
{
    (*p)->sM = mat;
}
void aff_suivant(ptr_s *p,ptr_s q) // sous-bloc suivant
{
    (*p)->suivant = q;
}
void aff_adr_cc(ptr_c *p,ptr_c q)
{

    (*p)->suivant = q;
}
void aff_adr_lc(ptr_l *p,ptr_c q)
{

    (*p)->pointeur_droit = q;
}
void aff_adr_ll(ptr_l *p,ptr_l q)
{

    (*p)->pointeur_down = q;
}
void aff_val(ptr_c *p,int val)
{

    (*p)->val = val;
}
void aff_cln(ptr_c *p,int cln)
{

    (*p)->cln = cln;
}
void aff_ligne(ptr_l *p,int ligne)
{

    (*p)->ligne = ligne;
}

// les fonctions et les proc�dures
void lecture_ll(ptr_l *tete,int *l,int *c )
 // lecture d'une matrice

{
    int j,i,v;
    ptr_l r,p;

    ptr_c cl,one_cl,q;

    printf(" Entrer le nombre des lignes : ");
    scanf("%d",l);
    printf("\n Entrer le nombre des colone: ");
    scanf("%d",c);
    for(i=1;i<=*l;i++)
    {

        allouer_ligne(&r);
        aff_ligne(&r,i);
        printf("\n matrice[%d,1] : ",i);
        scanf("%d",&v);
        if(v!=0){

        allouer_colone(&one_cl);
        aff_adr_lc(&r,one_cl);
        aff_cln(&one_cl,1);
        aff_val(&one_cl,v);}
        if(i!=1){aff_adr_ll(&p,r);}
        else{*tete = r;}

        q = one_cl;
        p = r;


        for(j=2;j<=*c;j++){

            printf(" matrice[%d,%d] :  ",i,j);
            scanf("%d",&v);
        if(v!=0){
            allouer_colone(&cl);
            if(suivant_lc(r)==NULL){aff_adr_lc(&r,cl);}
            else{aff_adr_cc(&q,cl);};
            aff_cln(&cl,j);
            aff_val(&cl,v);
            q = cl;}}



    }


}
void lecture_meme(ptr_l *tete,int l,int c)
 // lecture d'une matrice qui a les meme dimensions qu'une matrice donn�e

{
    int j,i,v;
    ptr_l r,p;

    ptr_c cl,one_cl,q;

    for(i=1;i<=l;i++)
    {
        allouer_ligne(&r);
        aff_ligne(&r,i);
        printf("\n matrice[%d,1] : ",i);
        scanf("%d",&v);
        if(v!=0){

        allouer_colone(&one_cl);
        aff_adr_lc(&r,one_cl);
        aff_cln(&one_cl,1);
        aff_val(&one_cl,v);}
        if(i!=1){aff_adr_ll(&p,r);}
        else{*tete = r;}

        q = one_cl;
        p = r;


        for(j=2;j<=c;j++){

            printf(" matrice[%d,%d] :  ",i,j);
            scanf("%d",&v);
        if(v!=0){
            allouer_colone(&cl);
            if(suivant_lc(r)==NULL){aff_adr_lc(&r,cl);}
            else{aff_adr_cc(&q,cl);};
            aff_cln(&cl,j);
            aff_val(&cl,v);
            q = cl;}}



    }


}
void lect_vect(ptr_l *V,int l)
// lecture d'un vecteur conditionn�e selon les r�gles de multiplication d'une matrice et un vecteur

{
     int i,v;
    ptr_l r,p;

    ptr_c one_cl;
    printf(" - Pour multiplier une matrice par un vecteur il faut que le nombre des lignes de ce dernier soit le meme que le nombre des colones de notre matrice !/n dans notre cas le nombre des lignes du vecteur : %i",l);
     for(i=1;i<=l;i++)
    {
        allouer_ligne(&r);
        aff_ligne(&r,i);
        printf("\n matrice[%d,1] : ",i);
        scanf("%d",&v);
        if(v!=0){

        allouer_colone(&one_cl);
        aff_adr_lc(&r,one_cl);
        aff_cln(&one_cl,1);
        aff_val(&one_cl,v);}
        if(i!=1){aff_adr_ll(&p,r);}
        else{*V = r;}
        p = r;
    }
}

void afficher_ll(ptr_l tete,int l,int c)
 // afficher une matrice

{
ptr_l p;
int i,j;
ptr_c z;
p=tete;
  for(i=1;i<=l;i++)
  {
    for(j=1;j<=c;j++){
      while(num_ligne(p)<i){p=suivant_l(p);};
      if(num_ligne(p)==i){
        if(suivant_lc(p)==NULL){printf(" %d ",0);}
        else
            {

                  z=suivant_lc(p);


        while(num_colone(z)<j && suivant_c(z)!= NULL){z=suivant_c(z);}
        if(num_colone(z)!=j){printf(" %d ",0);}
        else
            {
                printf(" %d ",z->val);
            }
            }
      }


      else{printf(" %d ",0);}
    }
    printf("\n");

  }
}
ptr_l transpose(ptr_l liste,int l,int c)
// transpose une matrice

{
    ptr_l w,p,r,save,tete;
    ptr_c q,qj,k;
    int i,j;
    save = liste;
    for(i=1;i<=c;i++)
    {
        allouer_ligne(&r);
        if(i==1){
               tete = r;
        }
        else{
            aff_adr_ll(&p,r);
        }
        aff_ligne(&r,i);
        w = save;
        for(j=1;j<=l;j++)
        {


            q = suivant_lc(w);

            if(q!= NULL ){


            while(suivant_c(q)!= NULL && num_colone(q)<i){q=suivant_c(q);}
            if(num_colone(q)==i){
                    allouer_colone(&k);

            if(suivant_lc(r)==NULL){aff_adr_lc(&r,k);}
            else{aff_adr_cc(&qj,k);};

            aff_cln(&k,j);
            aff_val(&k,valeur_c(q));

            }}

            w = suivant_l(w);
            qj = k;

        }

        p = r;

    }
    /*************/
return tete;
}
void liberer_liste(ptr_l tete)

{
    ptr_l p = tete;
    while(suivant_l(p)!=NULL)
    {

        ptr_c z = suivant_lc(p);
        ptr_l tmp = p;
        p = suivant_l(p);
        liberer_l(tmp);
        while(z!=NULL)
            {
               ptr_c tmpZ = z;
                z = suivant_c(z);
                liberer_c(tmpZ);

                }
            }
    }
void condition(int lines,int columns,int*dl,int*dc,int*al,int*ac) // les conditions de l'extraction d'une sous matrice

{
     printf("extraction d'une sous matrice aura besoin d'un point de d�part et d'arriv�...\n");

     printf("ligne de d�part: ");
     scanf("%i",dl);
     while(*dl>lines)
     {
         printf("d�passement de nombre de lignes de matrice saisie, saisissez une ligne de d�part plus petite:");
         scanf("%i",dl);
     }



     printf("colone de d�part: ");
     scanf("%i",dc);
     while(*dc>columns)
     {
         printf("d�passement de nombre de colones de matrice saisie, saisissez une colone de d�part plus petite:");
         scanf("%i",dc);
     }


     printf("ligne d'arriv�e: ");
     scanf("%i",al);
     while(*al>lines || *al<
           *dl)
     {
         if(*al>lines)
         {
                printf("d�passement de nombre de lignes de matrice saisie, saisissez une ligne d'arriv�e plus petite:");
                scanf("%i",al);
         }
         else
         {
                printf("la ligne de d'arriv�e doit etre sup�rieure ou �gale � la ligne de d�part try another: ");
                scanf("%i",al);
         }
     }


     printf("colone d'arriv�e: ");
     scanf("%i",ac);
     while(*ac>columns || (*dl==*al && *ac<*dc))
     {
         if (*ac>columns)
         {
            printf("d�passement de nombre de colones de matrice saisie, saisissez une colone d'arriv�e plus petite:");
            scanf("%i",ac);
         }
         else
         {
            printf("la colone d'arriv� doit etre sup�rieure ou �gale � la colone de d�part car ligne d�part=ligne d'arriv�:");
            scanf("%i",ac);
         }
     }



}
ptr_l extraire(ptr_l liste,int ligne,int colone,int ligne_depart,int colone_depart,int ligne_arrive,int colone_arrive)


{
 int i; // index de ligne de depart
    ptr_l r,tete;
    ptr_l ri=NULL;
    ptr_c pre=NULL;
    ptr_l w = liste; // pointeur de parcour des lignes
    ptr_c q,new_c; // q pointeur de parcour des colones , qi est utilise pour liberer l'espace memoire
   while(w!=NULL && num_ligne(w)<ligne_depart){w = suivant_l(w);}

    for(i=1;i<=(ligne_arrive-ligne_depart+1);i++)
    {
        // cree ligne i
        allouer_ligne(&r);
        aff_ligne(&r,i);
        if(ri==NULL){tete = r;}
        else{aff_adr_ll(&ri,r);}
        ri = r;
        if(w!= NULL)
        {   q = suivant_lc(w);

            while(q!=NULL && num_colone(q)<colone_depart)
            {q = suivant_c(q);}
            while(q!=NULL && num_colone(q)<=colone_arrive)
            {
            allouer_colone(&new_c);
            aff_val(&new_c , valeur_c(q));
            aff_cln(&new_c,num_colone(q)-colone_depart+1);
            if(suivant_lc(r)==NULL){aff_adr_lc(&r,new_c);}
            else{aff_adr_cc(&pre,new_c);}
            pre = new_c;
            q = suivant_c(q);
            }

        }

        w = suivant_l(w);
    }
return tete;
}
// les op�rations logiques
ptr_l et(ptr_l l1,ptr_l l2)

{
    ptr_l w1,w2,tete,r,p;
    ptr_c q1,q2,q,qw;

    w1 = l1;
    w2 = l2;

    p = NULL;
    while(w1 != NULL )
    {
        /* creation de nouvelle ligne */
        allouer_ligne(&r);
        aff_ligne(&r,num_ligne(w1));
        if(p == NULL){tete = r;}else{aff_adr_ll(&p,r);}
        /* parcours des colones */
        if(suivant_lc(w1)!=NULL && suivant_lc(w2)!=NULL)
        {
            q1 = suivant_lc(w1);
            q2 = suivant_lc(w2);

            while(q1!=NULL && q2 != NULL)// O(c-1)
            {
                if(num_colone(q1)<num_colone(q2)){
               while(suivant_c(q1) != NULL && num_colone(q1)<num_colone(q2) ) //O(c2-c1+1)
                {
                    q1 = suivant_c(q1);
                }}
                else{
                while(suivant_c(q2) != NULL && num_colone(q1)>num_colone(q2)) //O(c1-c2+1)
                {
                    q2 = suivant_c(q2);
                }}
                /* le seul cas ou on cree un maillon */
               if(num_colone(q1)==num_colone(q2)&& valeur_c(q1)>0 && valeur_c(q2)>0)
               {
                allouer_colone(&q);
                aff_val(&q,1);
                aff_cln(&q,num_colone(q2));
                if(suivant_lc(r)==NULL){aff_adr_lc(&r,q);}
                else{aff_adr_cc(&qw,q);}
                qw = q;

               }
               q2 = suivant_c(q2);
            q1 = suivant_c(q1);

            }

        }

       w1 = suivant_l(w1);
       w2 = suivant_l(w2);
        p = r;
}
return tete;
}
void non(ptr_l *l,int c)
{
    ptr_l w;
    ptr_c q ,p,qi,qs;

    int j,cli;
    w = *l;
    while(w!=NULL)
    {
        p = NULL;
        qi = suivant_lc(w);
        if(qi!=NULL){cli =  num_colone(qi);}
        for(j=1;j<=c;j++){
        if(qi==NULL || cli > j )
        {
            allouer_colone(&q);
            aff_val(&q,1);
            aff_cln(&q,j);
            if(p==NULL){aff_adr_lc(&w,q);}
            else{aff_adr_cc(&p,q);}
            p = q;
            }

        else if(qi != NULL && cli==j)
            {
                qs = qi;
                qi = suivant_c(qi);
                liberer_c(qs);

                if(cli == 1){aff_adr_lc(&w,qi);}
                else{aff_adr_cc(&q,qi);}
                if(qi!=NULL){cli = num_colone(qi);}

            }

        }
w = suivant_l(w);
}
}
ptr_l ou(ptr_l l1,ptr_l l2,int c)
{
    ptr_l tete;
    non(&l1,c);
    non(&l2,c);
    tete = et(l1,l2);
    non(&tete,c);
    return tete;
}
ptr_l oux(ptr_l l1,ptr_l l2, int c)
{
    ptr_l tete,tete1,tete2;
    tete1 = et(l1,l2);
    non(&l1,c);
    non(&l2,c);
    tete2 = et(l1,l2);
    tete = ou(tete1,tete2,c);
    non(&tete,c);
    return tete;


}
// les op�rqtions arithm�tiques
ptr_l add(ptr_l l1,ptr_l l2,int l,int c,int num)
{

    ptr_l w1,w2,r,ri,tete,l3,tmp;
    ptr_c q1,q2,qi,q;
    int j;
if(num==2){
 // on affect l'addition
    ri = NULL;
    w1 = l1;
    w2 = l2;

    while(w1!= NULL)
    {
        /* cree une ligne */
        allouer_ligne(&r);
        aff_ligne(&r,num_ligne(w1));
        if(ri == NULL){tete = r;}
        else{aff_adr_ll(&ri,r);}
        ri = r;

        /* parcour des matrice */
        q1 = suivant_lc(w1);
        q2 = suivant_lc(w2);
        for(j=1;j<=c;j++)
        {
            if((q1 != NULL && num_colone(q1)== j)  || (q2 != NULL && num_colone(q2)== j)  )
            {
                /* le cas ou on doit cree une colone */
                allouer_colone(&q);
                aff_cln(&q,j);
                if(suivant_lc(r)== NULL){aff_adr_lc(&r,q);}
                else{aff_adr_cc(&qi,q);}
                qi = q;
                if(q1 == NULL ||num_colone(q1)!= j ){aff_val(&q,valeur_c(q2));}
                else if(q2 == NULL || num_colone(q2)!= j){aff_val(&q,valeur_c(q1));}
                else{aff_val(&q,(valeur_c(q1)+valeur_c(q2)));
                    }
                if(q1!= NULL){q1 = suivant_c(q1);}
                if(q2!= NULL){q2 = suivant_c(q2);}
            }


        }


        w1 = suivant_l(w1);
        w2 = suivant_l(w2);
    }
return tete;
}
else{
    lecture_meme(&l3,l,c);
    tmp = add(l1,l2,l,c,2);
    return add(tmp,l3,l,c,num-1);
}
}
void MulV(ptr_l *M , ptr_l V)
{
    ptr_l w,v;
    ptr_c qw,qv,qi,tmp;
    w = *M;
    while(w != NULL)
    {
        v = V;
        qw = suivant_lc(w);
        while(qw!= NULL)
        {
            while(num_ligne(v)!= num_colone(qw)){v = suivant_l(v);}
            qv = suivant_lc(v);
            if(qv!=NULL){aff_val(&qw,valeur_c(qv));}
            else if(qi == NULL)
                {
                aff_adr_lc(&w,suivant_c(qw));
                tmp = qw;
                qw = suivant_c(qw);
                liberer_c(tmp);
                }
                else{
                    aff_adr_cc(&qi,suivant_c(qw));
                tmp = qw;
                qw = suivant_c(qw);
                liberer_c(tmp);
                }
            qi = qw;
            qw = suivant_c(qw);

        }
      w = suivant_l(w);
    }
}
ptr_l MulM(ptr_l M1,ptr_l M2,int l,int c1 ,int c2)
{
 ptr_l w1 ,w2,r,ri,tete;
 ri = NULL;

 ptr_c q1,q2,pre_c,new_c;
 int j,sum;
 w1 = M1;


 while(w1 != NULL )
 {
     w2 = M2;
      /* cree une ligne */
        allouer_ligne(&r);
        aff_ligne(&r,num_ligne(w1));
        if(ri == NULL){tete = r;}
        else{aff_adr_ll(&ri,r);}
        ri = r;
        aff_adr_lc(&r,NULL);
         pre_c= NULL;
     for(j = 1;j<=c2;j++)
     {
         sum = 0;
         q1 = suivant_lc(w1);
         w2 = M2;
         while(q1 != NULL)
         {

             while( num_ligne(w2)< num_colone(q1) )
             {w2 = suivant_l(w2);}
             q2 = suivant_lc(w2);
             while(q2 != NULL && num_colone(q2) != j){q2 = suivant_c(q2);}
             if(q2 != NULL)
                {sum += valeur_c(q1)*valeur_c(q2);}
            q1 = suivant_c(q1);
         }
        if(sum != 0){
                // le seul cas ou on cree une colone
            allouer_colone(&new_c);
            aff_val(&new_c,sum);
            aff_cln(&new_c,j);
            if(pre_c==NULL){aff_adr_lc(&r,new_c);}
            else{aff_adr_cc(&pre_c,new_c);}
            pre_c = new_c;


        }
     }
     w1 = suivant_l(w1);
 }
 return tete;
}

void division_sous_blocs(ptr_s *liste_blocs ,ptr_l tete, int ligne, int colone, int *ls,int *cs)
{
    ptr_s ri,r;
    int i,j;
    ri = NULL;

    division_sous_bloc_conditions(ligne,colone,ls,cs);
    for(i=1;i<=ligne;i+=(*ls))
    {
        for(j=1;j<=colone;j= j+(*cs))
        {
            allouer_bloc(&r);
            aff_mat(&r,extraire(tete,ligne,colone,i,j,i+(*ls)-1,j+(*cs)-1));
            if(ri==NULL){*liste_blocs=r;}
            else{aff_suivant(&ri,r);}
            ri = r;
        }
    }

}
void afficher_sb(ptr_s listeB ,int ls,int cs) // pour afficher les sous-blocs
{
    int i;
    ptr_s p;
    i = 1;
    p = listeB;
    while(p!=NULL)
    {
        printf("\n - Le sous bloc numero %i : \n",i);
        afficher_ll(mat(p),ls,cs);
        i ++;
        p = suivant_b(p);
    }
}
void Menu_2()
{
    int choix;
    ptr_l liste,l1,l2,tete;
        int l,c;
        int ls,cs;
        ptr_s listeB;
      printf("    *************************************************\n");
    printf("    *                                               *\n");
    printf("    *  Vous avez choisi la 2eme representation      *\n");
    printf("    *                                               *\n");
    printf("    *************************************************\n\n\n");

    printf("veuillez consulter nos diverses fonctions et en choisir une:\n");
    printf("\n    1-  Lecture d'une matrice creuse enti�re\n");
    printf("\n    2-  Extraction d'une sous matrice\n");
    printf("\n    3-  Division d'une matrice en sous-blocs de taille �gale\n");
    printf("\n    4-  La somme de deux ou plusieur matrices\n");
    printf("\n    5-  Multiplication par un vecteur\n");
    printf("\n    6-  Multiplication de deux matrices\n");
    printf("\n    7-  Transpos�e d'une matrice\n");
    printf("\n    8-  Op�rations logiques : NON , ET , OU , OU exclusif\n");


    printf("\n Alors! que vous voulez faire? entrez le num�ro de l'operation : \n");
    scanf("%i",&choix);
    int O;
    switch(choix)
    {
    case 1:
        printf("\n super! maintenant pour cr�er la matrice on aura besoin de plus d'information sur celle ci: \n");

        lecture_ll(&liste,&l,&c);
        afficher_ll(liste,l,c);
        printf("\n Votre matrice a �t� sauvgard�e dans l'addresse memoire point�e par 'liste' , merci d'avoir utiliser notre programme <3  \n");
        break;
    case 2:
        printf("\n Vous avez choisi l'extraction , veuillez entrer la matrice initiale : \n");
        lecture_ll(&liste,&l,&c);
        int dl,dc,al,ac;
        ptr_l sous_M;
        condition(l,c,&dl,&dc,&al,&ac);
        sous_M = extraire(liste,l,c,dl,dc,al,ac);
        afficher_ll(sous_M,al-dl+1,ac-dc+1);
        printf("\n Votre matrice a �t� sauvgard�e dans l'addresse memoire point�e par 'sous_M' , merci d'avoir utiliser notre programme <3  ");
        break;
    case 3:

        printf("\n Vous avez choisi la division en sous blocs, veuillez entrer la matrice initial : \n");
        lecture_ll(&liste,&l,&c);
        division_sous_blocs(&listeB,liste,l,c,&ls,&cs);
        afficher_sb(listeB,ls,cs);
        break;
    case 4:
       printf("\n Vous avez choisi la somme des matrices, veuillez entrer le nombre des matrices � additionner : \n");
       int num;
       scanf("%i",&num);
       while(num<2){
        printf("\n Le nombre des matrices doit �tre superieur ou �gal � 2 ! \n Entrez un nombre valide : ");
        scanf("%i",&num);
       }
       printf("\n Entrez la premi�re matrice : \n");
       lecture_ll(&l1,&l,&c);
       printf("\n Entrez la 2�me matrice : \n");
       lecture_meme(&l2,l,c);
       liste = add(l1,l2,l,c,num);
       afficher_ll(liste,l,c);
        printf("\n Votre matrice a �t� sauvgard�e dans l'addresse memoire point�e par 'liste' , merci d'avoir utiliser notre programme <3  ");
       break;
    case 5:
        printf("Vous avez choisi la multiplication par un vecteur, veuillez entrer votre matrice : ");
        lecture_ll(&liste,&l,&c);
        ptr_l V;
        lect_vect(&V,l);
        MulV(&liste,V);
        afficher_ll(liste,l,c);
        printf("\n Votre matrice a �t� sauvgard�e dans l'addresse memoire point�e par 'liste' , merci d'avoir utiliser notre programme <3  ");
        break;
    case 6:
        printf("\n Vous avez choisi la multiplication entre deux matrices, veuillez entrer la premi�re matrice :\n  ");
        lecture_ll(&liste,&l,&c);
        ptr_l M2,matrice;
        int c2;
        printf("\n Le nombre des lignes de la deuxieme matrice est conditionn�e,\n  par contre vous pouvez choisi le nombre des colones :  ");
        scanf("%i",&c2);
        lecture_meme(&M2,c,c2);
        matrice = MulM(liste,M2,l,c,c2);
        afficher_ll(matrice,l,c2);
        printf("\n Votre matrice a �t� sauvgard�e dans l'addresse memoire point�e par 'matrice' , merci d'avoir utiliser notre programme <3 \n ");
        break;
    case 7:

        printf("\n vous avez choisi la transposition , veuillez  entrer votre matrice :\n ");
        lecture_ll(&liste,&l,&c);
        tete = transpose(liste,l,c);
        afficher_ll(tete,c,l);
        printf("\n Votre matrice a �t� sauvgard�e dans l'addresse m�moire point�e par 'liste' , merci d'avoir utiliser notre programme <3  ");
        break;
    case 8:
        printf("\n Vous avez choisi les op�ration logique, Veuillez entrer : \n 1 pour le et logique \n 2 pour le non \n 3 pour le ou \n 4 pour le ou execlusif");
        int op;
        scanf("%i",&op);
        switch(op)
        {
        case 1:
            printf("\nEntrez la premi�re matrice : \n");
            lecture_ll(&l1,&l,&c);
            printf("\nEntrez la deuxi�me matrice :\n") ;
            lecture_meme(&l2,l,c);
            ptr_l etl;
            etl = et(l1,l2);
            afficher_ll(etl,l,c);
            printf("\n Votre matrice a �t� sauvgard�e dans l'addresse m�moire point�e par 'etl' , merci d'avoir utiliser notre programme <3  ");

            break;
        case 2:
            printf("Entrez la matrice : \n");
            lecture_ll(&l1,&l,&c);
            non(&l1,c);
            printf("L'inverse de votre matrice : \n");
            afficher_ll(l1,l,c);
            printf("\n Votre matrice a �t� sauvgard�e dans l'addresse m�moire point�e par 'l1' , merci d'avoir utiliser notre programme <3  ");

            break;
        case 3:
            printf("\nEntrez la premi�re matrice : \n");
            lecture_ll(&l1,&l,&c);
            printf("\nEntrez la deuxi�me matrice : \n");
            lecture_meme(&l2,l,c);
            ptr_l oul;
            oul = ou(l1,l2,c);
            afficher_ll(oul,l,c);
            printf("\n Votre matrice a �t� sauvgard�e dans l'addresse m�moire point�e par 'oul' , merci d'avoir utiliser notre programme <3  ");

            break;
        case 4:

            printf("\nEntrez la premi�re matrice : \n");
            lecture_ll(&l1,&l,&c);
            printf("\nEntrez la deuxi�me matrice : \n");
            lecture_meme(&l2,l,c);
            ptr_l ouxl;
            ouxl = oux(l1,l2,c);
            afficher_ll(ouxl,l,c);
            printf("\n Votre matrice a �t� sauvgard�e dans l'addresse m�moire point�e par 'ouxl' , merci d'avoir utiliser notre programme <3  ");
            printf("Le cout : %i",O );
            break;
        }

    }


}


