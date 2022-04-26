#ifndef BIB_H_INCLUDED
#define BIB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
// Allouche Imene - Khadir Amina G1 representation 1
//la structure du maillon de la 1ère représentation
typedef struct maillon
{
    int value;
    int line;
    int column;
    struct maillon *next;
}
maillon;

//déclaration du pointeur vers le maillon de la 1ère représentation
typedef struct maillon *pointer;


//déclaration du pointeur vers le maillon de la 1ère représentation
typedef struct maillon *pointer;







//la machine abstraite
void alocate(pointer *p);                   //alloueur un maillon
void free_it(pointer p);                    //liberer un maillon

pointer to_next(pointer p);                 //suivant du maillon
int value(pointer p);                       //valeur du maillon
int column_number(pointer p);               //numero de colone du maillon
int line_number(pointer p);                 //numero de ligne du maillon

void aff_adr(pointer *p,pointer q);         //aff_adr() editer le champ next
void aff_value(pointer *p,int value);       //aff_val() editer le champ value
void aff_line(pointer *p , int line);       //aff_ligne() editer le champ ligne
void aff_column(pointer *p , int column);   //aff_colone() editer le champ colone












//les fonctiosn de la 1ere representation





//
void ask_for_matrix(pointer *start, int lines, int columns);





//creer un nouveau maillon et inserer à la fin de la liste en précisant tous les champs
void create_new_node(pointer *start ,int row,int column,int non_zero_element);




//affiche le vrai contenu de la matrice crée sans les valeurs nulles comme suit:
/*
    line    column  value
     .        .       .
     .        .       .
     .        .       .
     .        .       .
*/
void display(pointer *start);







//afficher le contenu de la liste sous forme d'une matrice
//en completant l'affichage des valeurs nulles dans les espaces manquants comme suit:
/*
    .   .   .   .
    .   .   .   .
    .   .   .   .
    .   .   .   .
    .   .   .   .
*/
void PrintList(pointer *start, int lines_number, int columns_number);








//cree la transposee d'une matrice et retourne sa tete dans la variable pointer *new_head
void matrix_transposee(pointer *new_head, pointer *start);




//inserer un maillon mais en ordre selon la 1ere representation
//la position de l'insertion du maillon est déduite du nombre de ligne et colone du maillon
//ce module sera utilisée dans la creation de la transposée pour un coup de temps meilleur
void insert_node_order(pointer *new_head , int line, int column, int value);





//exige des conditions sur le numéro de ligne et de colone de départ et d'arrivée
//selon la matrice de départ
//pour eviter toute faute de segmentation ou d'incohérence
void submatrix_conditions(int* dl,int*dc,int*al,int*ac,int lines , int columns);



//extraire une sous matrice à partir de la matrice principal et retourner sa tete
//dans la variable *new_head
void extraction_submatrix(pointer *new_head, pointer *start , int lines, int columns);



//exige des conditions sur le nombre de ligne et de colone des sous blocs
//selon la matrice de départ
//pour eviter toute faute de segmentation ou d'incohérence
void division_sous_bloc_conditions(int lines, int columns, int *line_number, int *column_number);




void division_sous_bloc(pointer *start, int lines, int columns);
void search_the_node(pointer *start,int row, int column,pointer* node,int*found);


//libère l'espace mememoire alloué pour une liste de la 1ère representation à partir de la tete de la liste
void freeList(pointer *start);


//additioner deux matrices de la meme dimension et retourner la tete de la matrice résultat
//dans la variable pointer *result
pointer add_matrixes(pointer *first_matrix , pointer *second_matrix , int lines,int columns,int additions);


//multiplier deux matrices et retourner la tete de la nouvelle matrice
//dans la variable result
void multiply_matrixes(pointer* first_matrix, pointer* second_matrix, pointer *result ,int lines,int colines,int columns);







//fait le ou logique entre deux matrices de meme dimension et retourne la tete de la nouvelle matrice
//dans la variable pointer* result
void operation_or(pointer *first_matrix ,pointer* second_matrix , pointer *result);


//fait le ou exclusif logique entre deux matrices de meme dimension et retourne la tete de la nouvelle matrice
//dans la variable pointer* result
void operation_oux(pointer *first_matrix ,pointer* second_matrix , pointer *result);


//fait le et logique entre deux matrices de meme dimension et retourne la tete de la nouvelle matrice
//dans la variable pointer* result
void operation_et(pointer *first_matrix ,pointer* second_matrix , pointer *result);


//fait le non logique sur une matrice et retourne la tete de la nouvelle matrice
//dans la variable pointer* result
void operation_non(pointer *start, pointer *result, int lines, int columns);



void Menu_1();
// *********************************************************************+



// Khadir Amina - imene alouch G1 representaion 2
// definition des type utilisés
typedef struct ligne_ll* ptr_l;
typedef struct colone_ll* ptr_c;
typedef struct blocs* ptr_s;
typedef struct blocs // la strecture va étre utilisée dans la division sous-bloc
{
    ptr_l sM;
    ptr_s suivant;
}blocs;
typedef struct ligne_ll
{
    int ligne;
    ptr_l pointeur_down;
    ptr_c pointeur_droit;
}ligne_ll;
typedef struct colone_ll
{
    int cln;
    int val;
    struct colone_ll *suivant;
}colone_ll;
// la machine abstraite
// 1- allouer
void allouer_ligne(ptr_l *p);
void allouer_bloc(ptr_s *p);
void allouer_colone(ptr_c *p);
// 2- Liberer
void liberer_l(ptr_l p);

void liberer_c(ptr_c p);
ptr_l suivant_l(ptr_l p);
ptr_c suivant_c(ptr_c p);
ptr_c suivant_lc(ptr_l p);
ptr_s suivant_b(ptr_s b);
int valeur_c(ptr_c p);
ptr_l mat(ptr_s p);
int num_colone(ptr_c p);
int num_ligne(ptr_l p);
void aff_mat(ptr_s *p,ptr_l mat); // pour sauvgarder le sous-bloc
void aff_suivant(ptr_s *p,ptr_s q); // sous-bloc suivant
void aff_adr_cc(ptr_c *p,ptr_c q);
void aff_adr_lc(ptr_l *p,ptr_c q);
void aff_adr_ll(ptr_l *p,ptr_l q);
void aff_val(ptr_c *p,int val);
void aff_cln(ptr_c *p,int cln);
void aff_ligne(ptr_l *p,int ligne);
void lecture_ll(ptr_l *tete,int *l,int *c); // lecture d'une matrice
void lecture_meme(ptr_l *tete,int l,int c); // lecture d'une matrice qui a les meme dimensions qu'une matrice donnée
void lect_vect(ptr_l *V,int l); // lecture d'un vecteur conditionnée selon les régles de multiplication d'une matrice et un vecteur
void afficher_ll(ptr_l tete,int l,int c); // afficher une matrice
ptr_l transpose(ptr_l liste,int l,int c);
void condition(int lines,int columns,int*dl,int*dc,int*al,int*ac); // les conditions de l'extraction d'une sous matrice
ptr_l extraire(ptr_l liste,int ligne,int colone,int ligne_depart,int colone_depart,int ligne_arrive,int colone_arrive);
// les opérations logiques
ptr_l et(ptr_l l1,ptr_l l2);
void non(ptr_l *l,int c);
ptr_l ou(ptr_l l1,ptr_l l2,int c);
ptr_l oux(ptr_l l1,ptr_l l2, int c);
// les opérqtions arithmétiques
ptr_l add(ptr_l l1,ptr_l l2,int l,int c,int num);
void MulV(ptr_l *M , ptr_l V);
ptr_l MulM(ptr_l M1,ptr_l M2,int l,int c1 ,int c2);
void division_sous_blocs_conditions(int lines, int columns, int *line_size, int *column_size);
void division_sous_blocs(ptr_s *liste_blocs ,ptr_l tete, int ligne, int colone, int *ls,int *cs);
void afficher_sb(ptr_s listeB ,int ls,int cs); // pour afficher les sous-blocs
void Menu_2();
#endif // BIB_H_INCLUDED

