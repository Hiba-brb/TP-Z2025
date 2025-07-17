  /**--------------------------------------------------------**/
  /**       C o n v e r s i o n   Z vers C (Standard)        **/
  /**             Réalisée par Pr D.E ZEGOUR                 **/
  /**             E S I - Alger                              **/
  /**             Copywrite 2014                             **/
  /**--------------------------------------------------------**/
  #include <conio.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>

  typedef int bool ;
  typedef char * string255 ;
  typedef char * string2 ;

  #define True 1
  #define False 0

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define BOLD    "\033[1m"




  /** Implémentation **\: ARBRE BINAIRE DE CHAINES DE CARACTERES**/

  /** Arbres de recherche binaire **/

  typedef string255 Typeelem_As   ;
  typedef struct Noeud_As * Pointeur_As ;

   typedef struct output_info
    {
     int success_path_triplet;
     int fail_path_triplet;
     int total_path_triplet;

     int success_path_bst0;
     int fail_path_bst0;
     int total_path_bst0;
     } output_info;

    output_info arr[10];



  struct Noeud_As
    {
      Typeelem_As  Val ;
      Pointeur_As Fg ;
      Pointeur_As Fd ;
      Pointeur_As Pere ;
     } ;

  Typeelem_As Info_As( Pointeur_As P )
    { return P->Val;   }

  Pointeur_As Fg_As( Pointeur_As P)
    { return P->Fg ; }

  Pointeur_As Fd_As( Pointeur_As P)
    { return P->Fd ; }

  Pointeur_As Pere_As( Pointeur_As P)
    { return P->Pere ; }

  void Aff_info_As ( Pointeur_As P, Typeelem_As Val)
    {
       strcpy( P->Val , Val );
    }

  void Aff_fg_As( Pointeur_As P, Pointeur_As Q)
    { P->Fg =  Q;  }

  void Aff_fd_As( Pointeur_As P, Pointeur_As Q)
    { P->Fd =  Q ; }

  void Aff_pere_As( Pointeur_As P, Pointeur_As Q)
    { P->Pere =  Q ; }

  void Creernoeud_As( Pointeur_As *P)
    {
      *P = (struct Noeud_As *) malloc( sizeof( struct Noeud_As))   ;
      (*P)->Val = malloc(255 * sizeof(string255));
      (*P)->Fg = NULL;
      (*P)->Fd = NULL;
      (*P)->Pere = NULL;
    }

  void Liberernoeud_As( Pointeur_As P)
    { free( P ) ; }


  /** Implémentation **\: PILE DE ARBRES BINAIRES DE CHAINES DE CARACTERES**/
  /** Piles **/

  typedef Pointeur_As Typeelem_PAs ;
  typedef struct Maillon_PAs * Pointeur_PAs ;
  typedef   Pointeur_PAs  Typepile_PAs  ;

  struct Maillon_PAs
    {
      Typeelem_PAs  Val ;
      Pointeur_PAs Suiv ;
    } ;

  void Creerpile_PAs( Pointeur_PAs *P )
    { *P = NULL ; }

  bool Pilevide_PAs ( Pointeur_PAs P )
    { return  (P == NULL ); }

  void Empiler_PAs ( Pointeur_PAs *P,  Typeelem_PAs Val )
    {
      Pointeur_PAs Q;

      Q = (struct Maillon_PAs *) malloc( sizeof( struct Maillon_PAs))   ;
      Q->Val = Val ;
      Q->Suiv = *P;
      *P = Q;
    }

  void Depiler_PAs ( Pointeur_PAs *P,  Typeelem_PAs *Val )
    {
      Pointeur_PAs Sauv;

      if (! Pilevide_PAs (*P) )
        {
          *Val = (*P)->Val ;
          Sauv = *P;
          *P = (*P)->Suiv;
          free(Sauv);
        }
      else printf ("%s \n", "Pile vide");
    }




  /* Traitement des fichiers ouverts */

  struct _Noeud
    {
      FILE * Var_fich ;
      char * Nom_fich ;
      int Sauv_pos;
      struct _Noeud *Suiv ;
    } ;

  typedef struct _Noeud * _Ptr_Noeud;

  _Ptr_Noeud  _Pile_ouverts  = NULL;

  /* Teste si un fichier est ouvert */
  _Ptr_Noeud _Ouvert ( char * Fp)
    {
      _Ptr_Noeud P;
      bool Trouv ;
      P = _Pile_ouverts; Trouv = False ;
      while ((P != NULL) && ! Trouv )
        if ( strcmp(P->Nom_fich, Fp) == 0)
        Trouv = True;
        else P = P->Suiv;
      return P;
    }

  /* Ajouter un fichier ouvert */
  void _Empiler_ouvert ( char *Fp, FILE *Fl)
    {
      _Ptr_Noeud  P ;
      P = (_Ptr_Noeud) malloc( sizeof( struct _Noeud)) ;
      P->Nom_fich = Fp;
      P->Var_fich = Fl;
      P->Suiv = _Pile_ouverts;
      _Pile_ouverts = P;
    }

  /* Supprimer un fichier ouvert et rendre son nom*/
  char * _Depiler_ouvert ( FILE *Fl)
    {
      char * Fp = malloc (100);
      _Ptr_Noeud P,  Prec  ;
      P= _Pile_ouverts;
      Prec = NULL;
      while (P->Var_fich != Fl )
        { Prec = P ; P = P->Suiv ;}
      strcpy(Fp, P->Nom_fich);
      if (Prec != NULL)
        Prec->Suiv = P->Suiv;
      else _Pile_ouverts = P->Suiv;
      free (P);
      return Fp ;
    }


  /** Fichiers **/

  typedef char _Tx[255];
  typedef string255 Typestruct1_s;
  typedef _Tx Typestruct1_s_Buf;


  /** Machine abstaite sur les fichiers **/

  void Ouvrir_s ( FILE **s , char *Fp , char * Mode )
    {
      _Ptr_Noeud P = _Ouvert(Fp);
      if ( P != NULL )
      /* Le fichier est d?j? ouvert */
        {
         P->Sauv_pos = ftell (P->Var_fich);
         fclose(P->Var_fich);
        }
      /* Le fichier est non ouvert */
      if ( strcmp(Mode,"A") == 0)
        *s = fopen(Fp, "r+b");
      else
        *s = fopen(Fp, "w+b");
      _Empiler_ouvert( Fp, *s);
    }

  void Fermer_s ( FILE * s )
    {
      char * Fp = malloc(100);
      _Ptr_Noeud P;
      strcpy(Fp, _Depiler_ouvert(s));
      fclose(s) ;
      /* Ya-til un fichier ouvert avec le m?me nom ?  */
      /* Si Oui, le R?ouvrir ? la position sauvegard?e */
      P =  _Ouvert (Fp);
      if ( P != NULL)
      {
        s = fopen(P->Nom_fich, "r+b");
        fseek(s, P->Sauv_pos, 0);
      }
    }

  void Ecrireseq_s ( FILE * s, Typestruct1_s Buf  )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Ecriredir_s ( FILE * s, Typestruct1_s Buf, int N )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fseek(s, (long) (N-1)* sizeof(  Typestruct1_s_Buf), 0);
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Lireseq_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      if (fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s) != 0) {
      for(J=0; J<= strlen(Buffer); ++J)
        Buf [J] = Buffer[J]  ;
      }
    }

  void Liredir_s ( FILE * s, Typestruct1_s Buf, int N)
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      fseek(s, (long) (N-1)* sizeof( Typestruct1_s_Buf), 0 );
      fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s);
      for(J=0; J<= strlen(Buffer); ++J)
        Buf [J] = Buffer[J]  ;
    }

  void Rajouter_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fseek(s, 0, 2); /* Fin du fichier */
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  bool Finfich_s (FILE * s)
    {
      long K = ftell(s);
      fseek(s, 0, 2); /* Fin du fichier */
      long K2 = ftell(s);   /* position ? partir du debut */
      if  (K==K2)
        { fseek(s, K, 0); return 1;}
      else
        { fseek(s, K, 0); return 0;}
    }

  int Alloc_bloc_s (FILE * s)
    {
      long K;
      fseek(s, 0, 2); /* Fin du fichier */
      K = ftell(s);   /* position ? partir du debut */
      K = K / sizeof (Typestruct1_s_Buf);
      K ++;
      return(K);
    }

  /** Implémentation **\: FILE DE ARBRES BINAIRES DE CHAINES DE CARACTERES**/
  /** Files d'attente **/

  typedef Pointeur_As Typeelem_FAs ;
  typedef  struct Filedattente_FAs * Pointeur_FAs ;
  typedef  struct Maillon_FAs * Ptliste_FAs ;

  struct Maillon_FAs
    {
      Typeelem_FAs Val ;
      Ptliste_FAs Suiv  ;
    };

  struct Filedattente_FAs
    {
      Ptliste_FAs Tete, Queue ;
    };

  void Creerfile_FAs ( Pointeur_FAs *Fil   )
    {
      *Fil = (struct Filedattente_FAs *) malloc( sizeof( struct Filedattente_FAs)) ;
      (*Fil)->Tete = NULL ;
      (*Fil)->Queue = NULL ;
    }

  bool Filevide_FAs (Pointeur_FAs Fil  )
    { return  Fil->Tete == NULL ;}

  void Enfiler_FAs ( Pointeur_FAs Fil , Typeelem_FAs Val   )
    {
      Ptliste_FAs Q;

      Q = (struct Maillon_FAs *) malloc( sizeof( struct Maillon_FAs))   ;
      Q->Val = Val ;
      Q->Suiv = NULL;
      if ( ! Filevide_FAs(Fil) )
        Fil->Queue->Suiv = Q ;
      else Fil->Tete = Q;
        Fil->Queue = Q;
    }

  void Defiler_FAs (Pointeur_FAs Fil, Typeelem_FAs *Val )
    {
      if (! Filevide_FAs(Fil) )
        {
          *Val = Fil->Tete->Val ;
          Fil->Tete =  Fil->Tete->Suiv;
        }
      else printf ("%s \n", "File d'attente vide");
    }


  /** Variables du programme principal **/
  Pointeur_As T0=NULL;
  Pointeur_As T1=NULL;
  Pointeur_As T2=NULL;
  Pointeur_As T3=NULL;

  Pointeur_As bst0=NULL;
  Pointeur_As bst1=NULL;
  Pointeur_As bst2=NULL;
  Pointeur_As bst3=NULL;


  string255 N1;
  string255 N2;
  int N;
  int L;
  bool B;
  string2 X;
  string2 Y;
  string2 Z;

  /** Fonctions standards **/

  char *Caract ( string255 Ch , int I )
    {
      char *s = malloc(2);
      s[0] = Ch[I-1];
      s[1] = '\0';
      return  s;
    }

  int Aleanombre( int N )
    { return ( rand() % N ); }

  char  *Aleachaine ( int N )
    {
      int k;
      char  * Chaine = malloc(N+1);

      char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
      char Chr2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      for (k=0;k<N; k++)
        switch ( rand() % 2 ){
        case 0 :  *(Chaine+k) = Chr1[rand() % 26] ; break ;
        case 1 :  *(Chaine+k) = Chr2[rand() % 26] ; break ;
        }
      Chaine[k] =  '\0' ;

      return (Chaine);
    }


  /** Prototypes des fonctions **/

  int  Compute_xyz (Pointeur_As *R) ;
  int  Calculer_profondeur (Pointeur_As *R) ;
  void Search_bst3 (Pointeur_As *R , string255 *Word , bool *Bool3 , int *Path3);
  void Word_search_operation (Pointeur_As *R1 , Pointeur_As *R2 , Pointeur_As *R3 , string255 *Word , bool *Bool , int *Path);
  int  Range_search (Pointeur_As *R , string255 *Word1 , string255 *Word2) ;
  void Rotate_left (Pointeur_As *R , Pointeur_As *A);
  void Rotate_right (Pointeur_As *R , Pointeur_As *A);
  void Inorder_taversal (Pointeur_As *R);
  void Remplir_arbre (Pointeur_As *R1 , Pointeur_As *R2,Pointeur_As *R3, Pointeur_As *R0);
  void Insert_bst1 (Pointeur_As *R , string255 *Word);
  void Insert_bst3 (Pointeur_As *R , string255 *Word);
  void Search_bst1 (Pointeur_As *R , string255 *Word , bool *Bool1 , int *Path1);
  void Check_tree_3 (Pointeur_As *P);
  void Insert_bst0 (Pointeur_As *R , string255 *Word);
  void Search_bst0 (Pointeur_As *R , string255 *Word , bool *Bool , int *Path);
  void Insert_bst2 (Pointeur_As *R , string255 *Word);
  void Insert_bst21 (Pointeur_As *R , string255 *Word);
  int Range_search_count_nodes(Pointeur_As *R, string255 *Word1, string255 *Word2);
  void Module3(Pointeur_As *R0, Pointeur_As *R1, Pointeur_As *R2, Pointeur_As *R3);
  void Compter_xyz (Pointeur_As *R);
  int  Taille_file (Pointeur_FAs *F) ;
  void afficher_entete();
/*-------------------*/
void afficher_entete() {

     system("cls");


    printf(BOLD BLUE "\n============================================================\n" RESET);
    printf(BOLD GREEN "             TP Z 2024/2025       \n" RESET);
    printf(BOLD CYAN  "     Optimized Word Search Using BST Variants    \n" RESET);
    printf(BOLD YELLOW "\n   Realized by  : Bouarab Hiba | Boucenna Leila \n" RESET);
    printf(BOLD YELLOW "   Group : 14 \n" RESET);
    printf(BOLD BLUE "============================================================\n\n" RESET);
}

  /*---------------------------*/
  int  Compute_xyz (Pointeur_As *R)
    {
      /** Variables locales **/
      int  Compute_xyz2 ;
      Pointeur_As P=NULL;
      Pointeur_PAs Pil=NULL;
      int Count;

      /** Corps du module **/
      if (*R!=NULL){
     Count  =  0 ;
     printf ( "\n THE TOTAL NUMBER OF WORDS STARTING WITH Z,Y,a:" ) ;
     Creerpile_PAs (& Pil ) ;
     P  =  *R ;
     while( ( P != NULL ) || ( ! Pilevide_PAs ( Pil ) ))  {
       while( P != NULL)  {
         Empiler_PAs (& Pil , P ) ;
         P  =  Fg_As ( P ) ;

 } ;
       if( ! Pilevide_PAs ( Pil ))   {
         Depiler_PAs (& Pil , &P ) ;
         if( (strcmp( Caract ( Info_As ( P ) , 1 ), "Y") == 0  ) || (strcmp( Caract ( Info_As ( P ) , 1 ), "a") == 0  ) || (strcmp( Caract ( Info_As ( P ) , 1 ), "Z") == 0  )) {
           ;
           Count  =  Count + 1 ;

         } ;
         P  =  Fd_As ( P ) ;
         }
       else
         {
         P  =  NULL ;

       } ;

 } ;
     printf ( " %d \n", Count ) ;
     Compute_xyz2  =  Count ;

     return Compute_xyz2 ;
    }
    else
        printf("\n EMPTY TREE TRY AGAIN.");
    }

    /* CALCULER_PROFONDEUR */
int Calculer_profondeur(Pointeur_As *R) {
    /** Variables locales **/
    int profondeur_gauche;
    int profondeur_droite;

    /** Corps du module **/
    if (*R == NULL) {
        return 0;
    } else {
        profondeur_gauche = Calculer_profondeur(&(*R)->Fg);
        profondeur_droite = Calculer_profondeur(&(*R)->Fd);

        // Returne la profondeur  maximal  des 2 sous arbres plus le noeud actuelle
        return (profondeur_gauche > profondeur_droite ? profondeur_gauche : profondeur_droite) + 1;
    }
}

  /*---------------------------------*/

  /*----------------------------*/
  void Search_bst3 (Pointeur_As *R , string255 *Word , bool *Bool1 , int *Path1)
{
    // verification des inputs
if (R == NULL || Word == NULL || Bool1 == NULL || Path1 == NULL) {
 *Bool1 = False;
 *Path1 = 0;
return;
}
// Initialization  des output
*Bool1 = False;
*Path1 = 0;
// cas arbre vide
if (*R == NULL) {
printf("\n EMPTY TREE TRY AGAIN.");
return;
}
Pointeur_As current = *R;
Pointeur_As result = NULL;
int pathLength = 0;
while (current != NULL) {
pathLength++;
// Extraire la premiere lettre
char firstChar = Caract(Info_As(current), 1)[0];
// verifier si ce mot est valide a la recherche
if (firstChar != 'Y' && firstChar!='Z' && firstChar != 'a') {
int cmp = strcmp(Info_As(current), *Word);
if (cmp == 0) {
result = current;
break;
} else if (cmp < 0) {
current = Fd_As(current); // Move to right child
} else {
current = Fg_As(current); // Move to left child
}
} else {
current = NULL;
}
}

if (result != NULL) {
*Bool1 = True;
*Path1 = pathLength;
} else {
*Path1 = pathLength - 1 ;
}

}

  /*----------------------------*/
  void Word_search_operation (Pointeur_As *R1 , Pointeur_As *R2 , Pointeur_As *R3 , string255 *Word , bool *Bool , int *Path)
    {
      /** Variables locales **/
      Pointeur_As Resultat=NULL;
      string2 L;

      /** Corps du module **/
  if (*R1==NULL || *R2==NULL || *R3==NULL  )
  {
      printf("\n EMPTY TREE.");

  }
  else{
     L = malloc(2 * sizeof(char));
     *Bool  =  False ;
     *Path  =  0 ;
     Resultat  =  NULL ;
     strcpy (L,   Caract ( *Word , 1 )) ;
     if( (strcmp( L, "Z") == 0  ) || (strcmp( L, "Y") == 0  ) || (strcmp( L, "a") == 0  )) {
       ;
       // printf ("\n SEARCH IN BST1" ) ;
       Search_bst1 ( & *R1 , & *Word , & *Bool , & *Path ) ;
       ;
       }
     else
       {
       if( (strcmp( L, "Y") > 0  ) || (strcmp( L, "Z") > 0  ) || (strcmp( L, "a") > 0  )) {
         ;
         // printf ( "\n SEARCH IN BST2" ) ;
          Search_bst0 ( & *R2 , & *Word , & *Bool , & *Path ) ;

         }
       else
         {
         //printf ("\n SEARCH IN BST3" ) ;
         Search_bst3 ( & *R3 , & *Word , & *Bool , & *Path ) ;

       } ;

     } ;
  }
    }
  /*----------------------------*/
  /*----------------------*/
  int  Range_search (Pointeur_As *R , string255 *Word1 , string255 *Word2)
    {
      /** Variables locales **/
      int  Range_search2 ;
      string255 Word_min;
      string255 Word_max;
      int Count;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     Word_min = malloc(255 * sizeof(char));
     Word_max = malloc(255 * sizeof(char));
     Count  =  0 ;

     if(strcmp( *Word1, *Word2) < 0 ) {
       strcpy (Word_min,   *Word1) ;
       strcpy (Word_max,   *Word2) ;
       }
     else
       {
       strcpy (Word_min,   *Word2) ;
       strcpy (Word_max,   *Word1) ;

     } ;
     if( *R != NULL) {
       if(strcmp( Word_min, Info_As ( *R )) <= 0 ) {
         _Px1 =  Fg_As ( *R ) ;
         Count  =  Count + Range_search ( &_Px1, & Word_min , & Word_max ) ;

       } ;
      /**R IS WITHIN THAT RANGE*/
       if( (strcmp( Word_min, Info_As ( *R )) <= 0  ) && (strcmp( Word_max, Info_As ( *R )) >= 0  )) {
         Count  =  Count + 1 ;
         printf ( " %s\n", Info_As(*R) ) ;

       } ;
       if(strcmp( Info_As ( *R ), Word_max) <= 0 ) {
         _Px2 =  Fd_As ( *R ) ;
         Count  =  Count + Range_search ( &_Px2, & Word_min , & Word_max ) ;

       } ;

     } ;
     Range_search2  =  Count ;

     return Range_search2 ;
    }
  /*----------------------*/

  /*----------------------*/
  void Rotate_left (Pointeur_As *R , Pointeur_As *A)
    {
      /** Variables locales **/
      Pointeur_As B=NULL;

      /** Corps du module **/
     B  =  Fd_As ( *A ) ;
     Aff_fd_As ( *A , Fg_As ( B ) ) ;
     if( Fg_As ( B ) != NULL) {
       ;
       Aff_pere_As ( Fg_As ( B ) , *A ) ;

     } ;
     Aff_pere_As ( B , Pere_As ( *A ) ) ;
     if( Pere_As ( *A ) == NULL) {
       ;
       *R  =  B ;
       }
     else
       {
       if( *A == Fg_As ( Pere_As ( *A ) )) {
         ;
         Aff_fg_As ( Pere_As ( *A ) , B ) ;
         }
       else
         {
         Aff_fd_As ( Pere_As ( *A ) , B ) ;

       } ;

     } ;
     Aff_fg_As ( B , *A ) ;
     Aff_pere_As ( *A , B ) ;

    }
  /*----------------------*/
  /*----------------------*/
  void Rotate_right (Pointeur_As *R , Pointeur_As *A)
    {
      /** Variables locales **/
      Pointeur_As B=NULL;

      /** Corps du module **/
     B  =  Fg_As ( *A ) ;
     Aff_fg_As ( *A , Fd_As ( B ) ) ;
     if( Fd_As ( B ) != NULL) {
       ;
       Aff_pere_As ( Fd_As ( B ) , *A ) ;

     } ;
     Aff_pere_As ( B , Pere_As ( *A ) ) ;
     if( Pere_As ( *A ) == NULL) {
       ;
       *R  =  B ;
       }
     else
       {
       if( *A == Fg_As ( Pere_As ( *A ) )) {
         Aff_fg_As ( Pere_As ( *A ) , B ) ;
         }
       else
         {
         Aff_fd_As ( Pere_As ( *A ) , B ) ;

       } ;

     } ;
     Aff_fd_As ( B , *A ) ;
     Aff_pere_As ( *A , B ) ;

    }
  /*----------------------*/

  /*------------------------*/
  void Inorder_taversal (Pointeur_As *R)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( *R != NULL) {
       _Px1 =  Fg_As ( *R ) ;
       Inorder_taversal ( &_Px1) ;
       printf ( "  %s  ", Info_As(*R) ) ;
       _Px2 =  Fd_As ( *R ) ;
       Inorder_taversal ( &_Px2) ;

     } ;

    }
  /*----------------------*/

  /*----------------------*/
  void Remplir_arbre (Pointeur_As *R1 , Pointeur_As *R2,Pointeur_As *R3,Pointeur_As *R0)
    {
      /** Variables locales **/
      FILE *F;
      Typestruct1_s S ;
      string255 C;
      int I;
      int K;
      string255 _Sx;

      *R1=NULL;
      *R2=NULL;
      *R3=NULL;
      *R0=NULL;


      /** Corps du module **/
     S = malloc(255 * sizeof(char));
     C = malloc(255 * sizeof(char));
     _Sx = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F1.z" , "N" ) ;
     for( I  =  1 ;I <= 101; ++I){
       K  =  Aleanombre(10 ) ;
       if( ( K != 0 ) && ( K != 1 ) && ( K != 2 )) {
         strcpy (S,   Aleachaine(Aleanombre(5 ) + 3 )) ;
         }
       else
         {
         if( K == 0) {
           ;
           strcpy (_Sx, "Y");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;

         } ;
         if( K == 1) {
           ;
           strcpy (_Sx, "Z");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;

         } ;
         if( K == 2) {
           ;
           strcpy (_Sx, "a");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;

         } ;

       } ;
       Ecrireseq_s ( F , S );
     } ;
     Fermer_s ( F ) ;
     Ouvrir_s (&F , "F1.z" , "A" ) ;
     I  =  0 ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy (C,   S) ;
       Insert_bst1 ( & *R1 , & C ) ;
       Insert_bst21( & *R2 , & C ) ;
       Insert_bst3 ( & *R3 , & C ) ;
       Insert_bst0 ( & *R0 , & C ) ;
       I  =  I + 1;
 } ;
     Fermer_s ( F ) ;

 if  (R0!=NULL && R1!=NULL && R2!=NULL && R3!=NULL)
 printf("\n BST0,BST1,BST2,BST3 GENERATED SUCCESSFULLY") ;
 else
 printf("\n BST0,BST1,BST2,BST3 GENERATED UNSUCCESSFULLY") ;



    }
  /*----------------------*/
  /*------------------------------*/
  /*insert in bst1*/
  void Insert_bst1 (Pointeur_As *R , string255 *Word)
    {
      /** Variables locales **/
      Pointeur_As Q=NULL;
      Pointeur_As V=NULL;
      Pointeur_As P=NULL;
      string2 L;
      string2 M;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     L = malloc(2 * sizeof(char));
     M = malloc(2 * sizeof(char));
     Creernoeud_As (& V ) ;
     Aff_info_As ( V , *Word ) ;
    /*si l arbre est vide la racine devient Q*/
     if( *R == NULL) {
       *R  =  V ;
       }
     else
       {
       P  =  *R ;
       Q  =  *R ;
       while( (strcmp( Info_As ( P ), *Word) != 0  ) && ( Q != NULL ))  {
         P  =  Q ;
         if(strcmp( Info_As ( P ), *Word) >= 0 ) {
           Q  =  Fg_As ( P ) ;
           }
         else
           {
           Q  =  Fd_As ( P ) ;

         } ;

 } ;
       if(strcmp( *Word, Info_As ( P )) == 0 ) {
         //printf ( " %s", "C EST UN DOUBLONS" ) ;
         }
       else
         {
         if(strcmp( Info_As ( P ), *Word) > 0 ) {
           Aff_fg_As ( P , V ) ;
           }
         else
           {
           Aff_fd_As ( P , V ) ;

         } ;
         Aff_pere_As ( V , P ) ;

       } ;
      /*I PUT THE SPECIAL WORD UP TO  THE ROOT  */
       strcpy (L,   Caract ( *Word , 1 )) ;
       if( (strcmp( "Y", L) == 0  ) || (strcmp( L, "Z") == 0  ) || (strcmp( L, "a") == 0  )) {
         while( ( Pere_As ( V ) != NULL ))  {
           if(strcmp( *Word, Info_As ( Pere_As ( V ) )) <= 0 ) {
             _Px1 =  Pere_As ( V ) ;
             Rotate_right ( & *R , &_Px1) ;
             }
           else
             {
             _Px2 =  Pere_As ( V ) ;
             Rotate_left ( & *R , &_Px2) ;

           } ;

           } ;

       } ;

     } ;
free(L);
    }
  /*insert in bst3*/
  void Insert_bst3 (Pointeur_As *R , string255 *Word)
    {
      /** Variables locales **/
      Pointeur_As Q=NULL;
      Pointeur_As V=NULL;
      Pointeur_As P=NULL;
      string2 L;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     L = malloc(2 * sizeof(char));
     Creernoeud_As (& V ) ;
     if( V == NULL) {
       ;
       printf ( " %s", "ALLOCATION PROBLEM" ) ;
       }
     else
       {
       Aff_info_As ( V , *Word ) ;
       if( *R == NULL) {
         *R  =  V ;
         }
       else
         {
         P  =  *R ;
         Q  =  *R ;
         while( (strcmp( Info_As ( P ), *Word) != 0  ) && ( Q != NULL ))  {
           P  =  Q ;
           if(strcmp( Info_As ( P ), *Word) >= 0 ) {
             Q  =  Fg_As ( P ) ;
             }
           else
             {
             Q  =  Fd_As ( P ) ;

           } ;

 } ;
         if(strcmp( *Word, Info_As ( P )) == 0 ) {
          // printf ( " %s", "C EST UN DOUBLONS" ) ;
           }
         else
           {
           if(strcmp( Info_As ( P ), *Word) > 0 ) {
             Aff_fg_As ( P , V ) ;
             }
           else
             {
             Aff_fd_As ( P , V ) ;

           } ;
           Aff_pere_As ( V , P ) ;

         } ;
         strcpy (L,   Caract ( *Word , 1 )) ;
         if( (strcmp( "Y", L) != 0  ) && (strcmp( L, "Z") != 0  ) && (strcmp( L, "a") != 0  )) {
           while( ( Pere_As ( V ) != NULL ))  {
             if(strcmp( *Word, Info_As ( Pere_As ( V ) )) <= 0 ) {
               _Px1 =  Pere_As ( V ) ;
               Rotate_right ( & *R , &_Px1) ;
               }
             else
               {
               _Px2 =  Pere_As ( V ) ;
               Rotate_left ( & *R , &_Px2) ;

             } ;

 } ;

         } ;

       } ;

     } ;
free(L);
    }
  /*--------------------*/

  /*--------------------*/

  void Insert_bst0 (Pointeur_As *R , string255 *Word)
    {
      /** Variables locales **/
      Pointeur_As Q=NULL;
      Pointeur_As V=NULL;
      Pointeur_As P=NULL;
      string2 L;

      /** Corps du module **/
     L = malloc(2 * sizeof(char));
     Creernoeud_As (& V ) ;
     if( V == NULL) {
       printf ( " %s", "ALLOCATION PROBLEM" ) ;
       }
     else
       {
       Aff_info_As ( V , *Word ) ;
       if( *R == NULL) {
         *R  =  V ;
         }
       else
         {
         P  =  *R ;
         Q  =  *R ;
         while( (strcmp( Info_As ( P ), *Word) != 0  ) && ( Q != NULL ))  {
           P  =  Q ;
           if(strcmp( Info_As ( P ), *Word) >= 0 ) {
             Q  =  Fg_As ( P ) ;
             }
           else
             {
             Q  =  Fd_As ( P ) ;

           } ;

 } ;
         if(strcmp( *Word, Info_As ( P )) == 0 ) {
          // printf ( " %s", "C EST UN DOUBLONS" ) ;
           }
         else
           {
           if(strcmp( Info_As ( P ), *Word) > 0 ) {
             Aff_fg_As ( P , V ) ;
             }
           else
             {
             Aff_fd_As ( P , V ) ;

           } ;
           Aff_pere_As ( V , P ) ;

         } ;

       } ;

     } ;
free(L);
    }

void Search_bst1(Pointeur_As *R, string255 *Word, bool *Bool1, int *Path1) {
// Valid input parameters
 *Bool1 = False;
 *Path1 = 0;

if (R == NULL || Word == NULL || Bool1 == NULL || Path1 == NULL) {

return;
}


// Empty tree case
if (*R == NULL) {
return;
}

Pointeur_As current = *R;
Pointeur_As result = NULL;
int pathLength = 0;

while (current != NULL) {
pathLength++;

// Extract first character
char firstChar = Caract(Info_As(current), 1)[0];

// Check if node is valid for search
if (firstChar == 'Y' || firstChar == 'Z' || firstChar == 'a') {
int cmp = strcmp(Info_As(current), *Word);

if (cmp == 0) {
result = current;
break;
} else if (cmp < 0) {
current = Fd_As(current); // Move to right child
} else {
current = Fg_As(current); // Move to left child
}
} else {
current = NULL; // Invalid node, stop search
}
}

if (result != NULL) {
*Bool1 = True;
*Path1 = pathLength;
} else {
*Path1 = pathLength - 1 ;
}
}
  /*----------------------------*/
 void Search_bst0 (Pointeur_As *R , string255 *Word , bool *Bool , int *Path)
    {
      /** Variables locales **/
      Pointeur_As P=NULL;
      Pointeur_As Result=NULL;


      /** Corps du module **/
     *Bool  =  False ;
     *Path  =  1 ;
     Result  =  NULL ;
     if( *R != NULL) {

       P  =  *R ;
       while( ( Result == NULL ) && ( P != NULL ))  {

           if(strcmp( Info_As ( P ), *Word) == 0 ) {
             Result  =  P ;
             }
           else
             {
             if(strcmp( Info_As ( P ), *Word) < 0 ) {

               P  =  Fd_As ( P ) ;
               *Path  =  *Path + 1 ;
               }
             else
               {
               P  =  Fg_As ( P ) ;
               *Path  =  *Path + 1 ;

              } ;

              } ;

            } ;

           } ;
     if( ( Result != NULL )) {

       *Bool  =  True ;
       }
     else
       {
       *Path  =  *Path- 1 ;

     } ;


    }

   /*---------------------*/

  /*--------------------*/


void Insert_bst2(Pointeur_As *R, string255 *Word) {

Pointeur_As Q = NULL;
Pointeur_As V = NULL;
Pointeur_As P = NULL;
Pointeur_As Curr = NULL;

string2 L;
int Depth;
int Target_depth;
int Curr_depth;
Pointeur_As _Px1 = NULL;
Pointeur_As _Px2 = NULL;


Creernoeud_As(&V);
  if (V == NULL) {
     printf("ALLOCATION PROBLEM\n");
  return;
}

Aff_info_As(V, *Word);

// Cas 1: arbre vide
   if (*R == NULL)
    {
      *R = V;
      return;
   }

P = *R;
Q = *R;
   while (Q != NULL && strcmp(Info_As(P), *Word) != 0) {
        P = Q;
   if (strcmp(Info_As(P), *Word) >= 0) {
       Q = Fg_As(P);
  } else {
   Q = Fd_As(P);
   }
   }

// Check les duplicats
if (strcmp(*Word, Info_As(P)) == 0) {
//printf("C EST UN DOUBLONS\n");
free(V); // liberee le noeud pas utiliser
return;
}

// Inserer un nouveau noeud
if (strcmp(Info_As(P), *Word) > 0) {
Aff_fg_As(P, V);
} else {
Aff_fd_As(P, V);
}
Aff_pere_As(V, P);

// Check si le mot commence par  X, Y, ou a (
strncpy(L, *Word, 1);
L[1] = '\0';
if (strcmp(L, "Y") == 0 || strcmp(L, "X") == 0 || strcmp(L, "a") == 0) {
Depth = Calculer_profondeur(R);
Target_depth = Depth / 2; // viser le millieu

if (Target_depth < 1) {
Target_depth = 1;
}

// Calculer la profondeur du nouveau noeud curr
Curr = V;
Curr_depth = 0;
while (Curr != NULL) {
Curr = Pere_As(Curr);
Curr_depth++;
}

// faire monter le noeud
while (Curr_depth > Target_depth + 1 && Pere_As(V) != NULL) {
if (V == Fg_As(Pere_As(V))) {
_Px1 = Pere_As(V);
Rotate_right( & *R, &_Px1);
} else {
_Px2 = Pere_As(V);
Rotate_left( & *R, &_Px2);
}

// Recalculer la profondeur apres les rotations
Curr = V;
Curr_depth = 0;
while (Curr != NULL) {
Curr = Pere_As(Curr);
Curr_depth++;
}
}

//faire decendre si le noeuds est trop haut
while (Curr_depth < Target_depth - 1 && V != *R) {
if (Fg_As(V) != NULL) {
Rotate_left( & *R, &V);
} else if (Fd_As(V) != NULL) {
Rotate_right( & *R, &V);
} else {
break;
}

// Recalculer la profondeur
Curr = V;
Curr_depth = 0;
while (Curr != NULL) {
Curr = Pere_As(Curr);
Curr_depth++;
}
}
}
}
  /*---------------------------------*/
  void Check_tree_3 (Pointeur_As *P)
    {
      /** Variables locales **/
      Pointeur_As R=NULL;
      Pointeur_PAs Pil=NULL;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     R  =  *P ;
     if( R != NULL) {
       if( ( Fg_As ( R ) == NULL ) && ( Fd_As ( R ) == NULL )) {
         printf ( " %s", Info_As(R) ) ;

       } ;
       if( Fg_As ( R ) != NULL) {
         _Px1 =  Fg_As ( R ) ;
         Check_tree_3 ( &_Px1) ;

       } ;
       if( Fd_As ( R ) != NULL) {
         _Px2 =  Fd_As ( R ) ;
         Check_tree_3 ( &_Px2) ;

       } ;

     } ;

    }
  /*---------------------------------*/

/*MODULE 2*/
void remplire_arb2 (Pointeur_As *R1 , Pointeur_As *R2,Pointeur_As *R3,Pointeur_As *R0)
    {
      /** Variables locales **/
      FILE *F1,*F2;
      Typestruct1_s S ;
      string255 C;
      int I;
      int K;
      string255 _Sx;
      int path_triplet, path_bst0,fail_triplet,fail_bst0;
      bool trouve;
      int lenght ;
      int index=0;

      /** Corps du module **/

     S = malloc(255 * sizeof(char));
     C = malloc(255 * sizeof(char));
     _Sx = malloc(255 * sizeof(char));

     printf("\n <====  SIMULATION MODULE 2  ====>\n");

 while (index<10)  {


       path_triplet=0;
       path_bst0=0;
       fail_triplet=0;
       fail_bst0=0;

     Ouvrir_s (&F1 , "F.z" , "N" ) ;
     for( I  =  1 ;I <= 10001; ++I){
           K  =  Aleanombre(10 ) ;
       if( ( K != 0 ) && ( K != 1 ) && ( K != 2 )) {
         strcpy (S,   Aleachaine(Aleanombre(5 ) + 3 )) ;
         }
       else
         {
         if( K == 0) {
           ;
           strcpy (_Sx, "Y");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;

         } ;
         if( K == 1) {
           ;
           strcpy (_Sx, "Z");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;

         } ;
         if( K == 2) {
           ;
           strcpy (_Sx, "a");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
         } ;
       } ;
       Ecrireseq_s ( F1 , S );
       } ;
     Fermer_s ( F1 ) ;

       I  =  0 ;
     Ouvrir_s (&F1 , "F.z" , "A" ) ;
      while( ! Finfich_s ( F1 )) {
       Lireseq_s ( F1 , S ) ;
       strcpy (C,   S) ;
       Insert_bst1 ( & *R1 , & C ) ;
       Insert_bst2 ( & *R2 , & C ) ;
       Insert_bst3 ( & *R3 , & C ) ;
       Insert_bst0 ( & *R0 , & C ) ;
       I  =  I + 1;
       } ;
       Fermer_s ( F1 );




 /*search all of the words in this file*/
      I  =  0 ;

      Ouvrir_s (&F1 , "F.z" , "A" ) ;

     while( ! Finfich_s ( F1 ))

    {
        Lireseq_s ( F1 , S ) ;
        strcpy (C,   S) ;/* in this case all search are successfull*/
        Word_search_operation (  R1 ,   R2 ,   R3 ,  & C , & trouve , &lenght) ;
        path_triplet=path_triplet + lenght;

        Search_bst0 (R0 , &C ,  &trouve , &lenght );
        path_bst0=path_bst0 + lenght;

         I  =  I + 1;
       }

       Fermer_s ( F1 ) ;

  /*Now create another file to test their words*/
       Ouvrir_s (&F2 , "F2.z" , "N" ) ;
     for( I  =  1 ;I <= 10001; ++I){
           K  =  Aleanombre(10 ) ;
       if( ( K != 0 ) && ( K != 1 ) && ( K != 2 )) {
         strcpy (S,   Aleachaine(Aleanombre(5 ) + 3 )) ;
         }
       else
         {
         if( K == 0) {
           ;
           strcpy (_Sx, "Y");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;

         } ;
         if( K == 1) {
           ;
           strcpy (_Sx, "Z");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;

         } ;
         if( K == 2) {
           ;
           strcpy (_Sx, "a");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
         } ;
       } ;
       Ecrireseq_s ( F2 , S );
       } ;
     Fermer_s ( F2 ) ;

      I=0;
       Ouvrir_s (&F2 , "F2.z" , "A" ) ;
 while( ! Finfich_s ( F1 ))

    {
        Lireseq_s ( F2 , S ) ;
        strcpy (C,   S) ;/* in this case all search are successfull*/



        Word_search_operation (  R1 ,   R2 ,   R3 ,  & C , & trouve , &lenght) ;
        if (trouve==True)

        {
           path_triplet=path_triplet + lenght;
        }
         if  (trouve==False)

        {
           fail_triplet= fail_triplet+ lenght;
        }

        Search_bst0 (R0 , &C ,  &trouve , &lenght );
        if (trouve==True)

        {
           path_bst0=path_bst0 + lenght;
        }
        if  (trouve==False)

        {
           fail_bst0 =+fail_bst0+lenght;
        }

       I  =  I + 1;
       }

       Fermer_s ( F2 ) ;

       arr[index].success_path_triplet=path_triplet;
       arr[index].success_path_bst0=path_bst0;
       arr[index].fail_path_triplet=fail_triplet;
       arr[index].fail_path_bst0=fail_bst0;
       arr[index].total_path_bst0 =fail_bst0+path_bst0;
       arr[index].total_path_triplet=fail_triplet+path_triplet;


       printf("\n ***********************************************************");
       printf("\n #Simulation num : %d ",index+1);
       printf("\n    *total succesful  paths in the triplet : %d",arr[index].success_path_triplet);
       printf("\n    *total path in bst0 : %d", arr[index].success_path_bst0 );
       printf("\n    *total unsuccesful  paths in the triplet : %d",arr[index].fail_path_triplet);
       printf("\n    *total ununsuccesful paths in bst0 : %d", arr[index].fail_path_bst0 );
       printf("\n    *total   paths in the triplet : %d",arr[index].total_path_triplet);
       printf("\n    *total   paths in bst0 : %d", arr[index].total_path_bst0);
       printf("\n ***********************************************************");



    index++;
remove("F.z");
remove("F2.z");
        *R0=NULL;
        *R1=NULL;
       *R2=NULL;
       *R3=NULL;


free(*R0);
free(*R1);
free(*R2);
free(*R3);
 }
    free(S);
    free(C);
    free(_Sx);




    printf("\n");
    printf("==============================================================\n");
    printf("| %-10s | %-30s | %-30s |\n", "SIMULATION", "BST0", "TRIPLET");
    printf("==============================================================\n");
    for (int i = 0; i <= 9; i++) {
        printf("| %s%d|E  | %-30d | %-30d |\n", "S", i+1, arr[i].success_path_bst0, arr[i].success_path_triplet);
        printf("..............................................................\n");
        printf("| %s%d|E! | %-30d | %-30d |\n", "S", i+1, arr[i].fail_path_bst0, arr[i].fail_path_triplet);
        printf("..............................................................\n");
        printf("| %s%d|ALL| %-30d | %-30d |\n", "S", i+1, arr[i].total_path_bst0, arr[i].total_path_triplet);
        printf("--------------------------------------------------------------\n");
    }
    printf("==============================================================\n");

    }



void create_file2(Pointeur_As *R1 , Pointeur_As *R2,Pointeur_As *R3,Pointeur_As *R0)
    {
      /** Variables locales **/
      FILE *F;
      Typestruct1_s S ;
      string255 C;
      int I;
      int K;
      string255 _Sx;
      int f=0;
      /** Corps du module **/
     S = malloc(255 * sizeof(char));
     C = malloc(255 * sizeof(char));
     _Sx = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F2.z" , "N" ) ;
     for( I  =  1 ;I <= 10001; ++I){
       K  =  Aleanombre(10 ) ;
       if( ( K != 0 ) && ( K != 1 ) && ( K != 2 )) {
         strcpy (S,   Aleachaine(Aleanombre(5 ) + 3 )) ;
         }
       else
         {
         if( K == 0) {
           ;
           strcpy (_Sx, "Y");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;

         } ;
         if( K == 1) {
           ;
           strcpy (_Sx, "Z");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;

         } ;
         if( K == 2) {
           ;
           strcpy (_Sx, "a");
           strcpy (S,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;

         } ;

       } ;
       Ecrireseq_s ( F , S );
     } ;
     Fermer_s ( F ) ;
     Ouvrir_s (&F , "F2.z" , "A" ) ;
     I  =  0 ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy (C,   S) ;
       Insert_bst1 ( & *R1 , & C ) ;
       Insert_bst2 ( & *R2 , & C ) ;
       Insert_bst3 ( & *R3 , & C ) ;
       Insert_bst0 ( & *R0 , & C ) ;
       I  =  I + 1;
       } ;
     Fermer_s ( F ) ;
    }



/**BST21 CHANGED**/
void Insert_bst21(Pointeur_As *R, string255 *Word) {
    Pointeur_As Q = NULL, V = NULL, P = NULL, Curr = NULL;
    char L[2];
    int Depth, Target_depth, Curr_depth;
    Pointeur_As _Px1 = NULL, _Px2 = NULL;

    Creernoeud_As(&V);
    if (V == NULL) {
        printf("ALLOCATION PROBLEM\n");
        return;
    }

    Aff_info_As(V, *Word);

    if (*R == NULL) {
        *R = V;
        return;
    }

    // Recherche du point d'insertion
    P = *R;
    Q = *R;
    while (Q != NULL && strcmp(Info_As(P), *Word) != 0) {
        P = Q;
        if (strcmp(Info_As(P), *Word) >= 0)
            Q = Fg_As(P);
        else
            Q = Fd_As(P);
    }

    // Mot déjà présent
    if (strcmp(*Word, Info_As(P)) == 0) {
        free(V); // Libérer le nœud inutilisé
        return;
    }

    // Insertion du nouveau nœud
    if (strcmp(Info_As(P), *Word) > 0)
        Aff_fg_As(P, V);
    else
        Aff_fd_As(P, V);
    Aff_pere_As(V, P);

    // Si le mot commence par Y, Z ou a, faire équilibrage
    strcpy(L, Caract(*Word, 1)); // L reçoit le 1er caractère
    if (strcmp(L, "Y") == 0 || strcmp(L, "Z") == 0 || strcmp(L, "a") == 0) {
        Depth = Calculer_profondeur(R);
        Target_depth = Depth / 2;
        if (Target_depth < 1) Target_depth = 1;

        Curr = V;
        Curr_depth = 0;
        while (Curr != NULL) {
            Curr = Pere_As(Curr);
            Curr_depth++;
        }

        while (Curr_depth > Target_depth + 1 && Pere_As(V) != NULL) {
            if (V == Fg_As(Pere_As(V))) {
                _Px1 = Pere_As(V);
                Rotate_right(R, &_Px1);
            } else {
                _Px2 = Pere_As(V);
                Rotate_left(R, &_Px2);
            }

            Curr = V;
            Curr_depth = 0;
            while (Curr != NULL) {
                Curr = Pere_As(Curr);
                Curr_depth++;
            }
        }

        while (Curr_depth < Target_depth - 1 && V != *R) {
            if (Fg_As(V) != NULL) {
                Rotate_left(R, &V);
            } else if (Fd_As(V) != NULL) {
                Rotate_right(R, &V);
            } else {
                break;
            }

            Curr = V;
            Curr_depth = 0;
            while (Curr != NULL) {
                Curr = Pere_As(Curr);
                Curr_depth++;
            }
        }
    }
}
//-----------------------------------------------------------------------------
/**RANGE SEARCH AND COUNT NODES VISITED**/
int Range_search_count_nodes(Pointeur_As *R, string255 *Word1, string255 *Word2) {
    int count = 0;
    string255 Word_min = malloc(255 * sizeof(char));
    string255 Word_max = malloc(255 * sizeof(char));

    if (strcmp(*Word1, *Word2) < 0) {
        strcpy(Word_min, *Word1);
        strcpy(Word_max, *Word2);
    } else {
        strcpy(Word_min, *Word2);
        strcpy(Word_max, *Word1);
    }

    if (*R != NULL) {

        count = 1;

        if (strcmp(Word_min, Info_As(*R)) < 0) {
        Pointeur_As fg = Fg_As(*R);
count += Range_search_count_nodes(&fg, &Word_min, &Word_max);
        }
        if ((strcmp(Word_min, Info_As(*R)) <= 0) && (strcmp(Word_max, Info_As(*R)) >= 0)) {

        }
        if (strcmp(Info_As(*R), Word_max) < 0) {
          Pointeur_As fd = Fd_As(*R);
count += Range_search_count_nodes(&fd, &Word_min, &Word_max);
        }
    }

    free(Word_min);
    free(Word_max);

    return count;
}
//----------------------------------------------------------------------------------------
/**MODULE 3 AVEC LES TABLEAU**/

void Module3(Pointeur_As *R0, Pointeur_As *R1, Pointeur_As *R2, Pointeur_As *R3) {
    FILE *F1, *F2;
    Typestruct1_s S;
    string255 mot, mot1, mot2, prefixe;
    int i, j, K;
    int total_count_bst0, total_count_bst_opt;
    char c;

    S = malloc(255);
    mot = malloc(255);
    mot1 = malloc(255);
    mot2 = malloc(255);
    prefixe = malloc(255);

    printf("\n<====  MODULE 3 : RANGE SEARCH SUR 10 SIMULATIONS ====>\n");

    for (j = 1; j <= 10; j++) {
        total_count_bst0 = 0;
        total_count_bst_opt = 0;

        // Génération du fichier F.txt
        Ouvrir_s(&F1, "F.txt", "N");
        for (i = 1; i <= 10001; ++i) {
            K = Aleanombre(10);
            if (K == 0) strcpy(prefixe, "Y");
            else if (K == 1) strcpy(prefixe, "Z");
            else if (K == 2) strcpy(prefixe, "a");
            else prefixe[0] = '\0';

            strcpy(mot, prefixe);
            strcat(mot, Aleachaine(Aleanombre(5) + 3));
            fprintf(F1, "%s\n", mot);
        }
        Fermer_s(F1);

        // Réinitialiser les arbres
        *R0 = NULL; *R1 = NULL; *R2 = NULL; *R3 = NULL;

        // Insertion dans les BSTs
        F1 = fopen("F.txt", "r");
        if (F1 == NULL) {
            printf("Erreur d'ouverture de F.txt\n");
            return;
        }

        while (fgets(mot, 255, F1) != NULL) {
            mot[strcspn(mot, "\n")] = '\0';
            Insert_bst0(R0, &mot);
            Insert_bst1(R1, &mot);
            Insert_bst21(R2, &mot);
            Insert_bst3(R3, &mot);
        }
        fclose(F1);

        // Génération de F2.txt
        F2 = fopen("F2.txt", "w");
        if (F2 == NULL) {
            printf("Erreur lors de la création de F2.txt\n");
            return;
        }

        for (i = 0; i < 5000; i++) {
            K = Aleanombre(10);
            if (K == 0) strcpy(prefixe, "Y");
            else if (K == 1) strcpy(prefixe, "Z");
            else if (K == 2) strcpy(prefixe, "a");
            else prefixe[0] = '\0';
            strcpy(mot1, prefixe);
            strcat(mot1, Aleachaine(Aleanombre(5) + 3));

            K = Aleanombre(10);
            if (K == 0) strcpy(prefixe, "Y");
            else if (K == 1) strcpy(prefixe, "Z");
            else if (K == 2) strcpy(prefixe, "a");
            else prefixe[0] = '\0';
            strcpy(mot2, prefixe);
            strcat(mot2, Aleachaine(Aleanombre(5) + 3));

            fprintf(F2, "%s %s\n", mot1, mot2);
        }
        fclose(F2);

        // Lecture et traitement des 5000 paires
        F2 = fopen("F2.txt", "r");
        if (F2 == NULL) {
            printf("Erreur : Impossible d’ouvrir F2.txt\n");
            return;
        }

        for (i = 0; i < 5000; i++) {
            fscanf(F2, "%s %s", mot1, mot2);

            // Recherche dans BST0 pour référence
            total_count_bst0 += Range_search_count_nodes(R0, &mot1, &mot2);

            // Sélection du bon arbre en fonction de la première lettre
            c = mot1[0];
            if (c == 'X' || c == 'Y' || c == 'Z') {
                total_count_bst_opt += Range_search_count_nodes(R1, &mot1, &mot2);
            } else if (c > 'Z') {
                total_count_bst_opt += Range_search_count_nodes(R2, &mot1, &mot2);
            } else {
                total_count_bst_opt += Range_search_count_nodes(R3, &mot1, &mot2);
            }

            if ((i + 1) % 500 == 0) {
                printf("   > %d paires traitees\n", i + 1);
            }
        }
        fclose(F2);

        printf("\n[ Simulation %d / 10 ]\n", j);
        printf("   BST0  : %d noeuds visites\n", total_count_bst0);
        printf("   BST TRIO (BST1-BST2-BST3) : %d noeuds visites\n", total_count_bst_opt);
        printf("   Gain             : %.2f %%\n",
            100.0 * (1 - ((double)total_count_bst_opt / total_count_bst0)));
        printf("--------------------------------------------\n");
    }

    free(S);
    free(mot);
    free(mot1);
    free(mot2);
    free(prefixe);
}
/*-------------------------------*/
  /*-------------------------------*/
  void Compter_xyz (Pointeur_As *R)
    {
      /** Variables locales **/
      Pointeur_FAs F=NULL;
      int Niv;
      int I;
      int Size;
      Pointeur_As Node=NULL;
      string2 C;
      int Cmpa;
      int Cmpy;
      int Cmpz;

      /** Corps du module **/
     C = malloc(2 * sizeof(char));
     Creerfile_FAs (& F ) ;
     Niv  =  0 ;
     if( *R != NULL) {
       Enfiler_FAs ( F , *R ) ;

     } ;
     while( ! Filevide_FAs ( F )) {
       Cmpy  =  0 ;
       Cmpz  =  0 ;
       Cmpa  =  0 ;
       Size  =  Taille_file ( & F ) ;
       for( I  =  1 ;I <=  Size ; ++I){
         Defiler_FAs ( F , &Node ) ;
         strcpy (C,   Caract ( Info_As ( Node ) , 1 )) ;
         if(strcmp( C, "Y") == 0 ) {
           Cmpy  =  Cmpy + 1 ;
           }
         else
           {
           if(strcmp( C, "Z") == 0 ) {
             Cmpz  =  Cmpz + 1 ;
             }
           else
             {
             if(strcmp( C, "a") == 0 ) {
               Cmpa  =  Cmpa + 1 ;

             } ;

           } ;

         } ;
         if( Fg_As ( Node ) != NULL) {
           Enfiler_FAs ( F , Fg_As ( Node ) ) ;

         } ;
         if( Fd_As ( Node ) != NULL) {
           Enfiler_FAs ( F , Fd_As ( Node ) ) ;

         } ;

       } ;
       printf ( "\n-> Niveau " );
       printf ( " %d", Niv ) ;
       printf ( "\n | Y =  " );
       printf ( " %d", Cmpy ) ;
       printf ( "\n | Z =  " );
       printf ( " %d", Cmpz ) ;
       printf ( "\n | a =  " );
       printf ( " %d", Cmpa ) ;
       printf ( "\n------------------------------------------" ) ;
       Niv  =  Niv + 1 ;

 } ;

    }
  int  Taille_file (Pointeur_FAs *F)
    {
      /** Variables locales **/
      int  Taille_file2 ;
      int Count;
      Pointeur_FAs Tempfile=NULL;
      Pointeur_As Node=NULL;

      /** Corps du module **/
     Count  =  0 ;
     Creerfile_FAs (& Tempfile ) ;
     while( ! Filevide_FAs ( *F )) {
       Defiler_FAs ( *F , &Node ) ;
       Enfiler_FAs ( Tempfile , Node ) ;
       Count  =  Count + 1 ;

 } ;
     while( ! Filevide_FAs ( Tempfile )) {
       Defiler_FAs ( Tempfile , &Node ) ;
       Enfiler_FAs ( *F , Node ) ;

 } ;
     Taille_file2  =  Count ;

     return Taille_file2 ;
    }


/*--------------------------------*/
  int main(int argc, char *argv[])
    {
     srand(time(NULL));
     N1 = malloc(255 * sizeof(char));
     N2 = malloc(255 * sizeof(char));
     X = malloc(2 * sizeof(char));
     Y = malloc(2 * sizeof(char));
     Z = malloc(2 * sizeof(char));
     B  =  False ;
     L  =  0 ;
     strcpy (X,   "Y") ;
     strcpy (Y,   "Z") ;
     strcpy (Z,   "a") ;
     T0 = NULL;
     T1  =  NULL ;
     T2  =  NULL ;
     T3  =  NULL ;
     bst0= NULL;
     bst1= NULL;
     bst2= NULL;
     bst3= NULL;
int menu;
int total_search_triplet=0;
int total_search_bst0=0;
       afficher_entete();
       printf( RED " PRESS ANY KEY TO CONTINUE...\n");
       getch();
  do {
    system("cls");

        printf(BOLD CYAN "\n===== Lab Topic: " RESET BOLD YELLOW "Optimized Word Search Using BST Variants" RESET BOLD CYAN " =====\n\n" RESET);
        printf(BOLD GREEN "1" RESET " - " BOLD "Generate" RED "BST0" RESET", " CYAN "BST1" RESET"," CYAN" BST2" RESET ","  MAGENTA "BST3\n" RESET);
        printf(BOLD GREEN "2" RESET " - " BOLD "Compute numbers of words starting with " YELLOW "Y, Z, a in a BST \n" RESET);
        printf(BOLD GREEN "3" RESET " - " BOLD "Compute depth of one of the BST\n" RESET);
        printf(BOLD GREEN "4" RESET " - " BOLD"Perform inorder traversal\n" RESET);
        printf(BOLD GREEN "5" RESET " - " BOLD "Show all leaves in"  MAGENTA " BST3.\n" RESET);
        printf(BOLD GREEN "6" RESET " - " BOLD "Search word in " CYAN "BST1" RESET ", " CYAN "BST2" RESET ", "  MAGENTA "BST3\n" RESET);
        printf(BOLD GREEN "7" RESET " - " BOLD "Search in " RED "BST0\n" RESET);
        printf(BOLD GREEN "8" RESET " - " BOLD "Range search in " CYAN "BST1" RESET ", " CYAN "BST2" RESET ", "  MAGENTA "BST3\n" RESET);
        printf(BOLD GREEN "9" RESET " - " BOLD "Print words starting with  Z Y a by level.\n" RESET);
        printf(BOLD GREEN "10" RESET " - " BOLD "Module 2: Evaluate word search efficiency\n" RESET);
        printf(BOLD GREEN "11" RESET " - " BOLD "Module 3: Evaluate range search efficiency\n" RESET);
        printf(BOLD GREEN "0" RESET " - " RED "Exit\n" RESET);

        printf(BOLD "\nEnter your choice: " RESET);

    scanf("%d", &menu);

    switch (menu) {
    case 1: {  T0 = NULL;
               T1  =  NULL ;
               T2  =  NULL ;
               T3  =  NULL ;

               Remplir_arbre ( & T1 ,&T2, & T3 ,& T0) ;
               printf("\n Press any key to comeback to the menu.");
               getch();
               break;
            }
    case 2: {
               N  =  Compute_xyz ( & T1 ) ;
                printf("\n Press any key to comeback to the menu.");
               getch();
               break;
            }
    case 3: {  printf ("\n***COMPUTE DEPTH OF BST1--->" ) ;
               N  =  Calculer_profondeur ( & T1 ) ;
               printf ( " %d ", N ) ;

               printf ( "\n***COMPUTE DEPTH OFBST2--->" ) ;
               N  =  Calculer_profondeur ( & T2 ) ;
               printf ( " %d ", N ) ;

               printf ( "\n***COMPUTE DEPTH OF BST3--->" ) ;
               N  =  Calculer_profondeur ( & T3 ) ;
               printf ( " %d ", N ) ;

               printf ( "\n***COMPUTE DEPTH OF BST0--->" ) ;
               N  =  Calculer_profondeur ( & T0 ) ;
               printf ( " %d ", N ) ;
               printf("\n Press any key to comeback to the menu.");
               getch();


               break;
            }

    case 4: {  printf ("***INORDRE TRAVERSAL OF BST***\n" ) ;
               Inorder_taversal ( & T1 ) ;
               printf("\n Press any key to comeback to the menu.");
               getch();

               break;
            }

    case 5: {   printf ("***VIEW ALL LEAVES OF BST3***\n" ) ;
                Check_tree_3 ( & T3 ) ;
                printf("\n Press any key to comeback to the menu.");
                 getch();

               break;
            }

    case 6: { printf ("***SEARCH WORD IN BST1 BST 2 BST3 ***\n" ) ;
              printf ("PLEASE ENTER A WORD :" ) ;
              scanf ( " %[^\n]", N1 ) ;
              Word_search_operation ( & T1 , & T2 , & T3 , & N1 , & B , & L ) ;
             if( ( B == True )) {
                printf ( "-->FOUND\n" ) ;
                }
             else
               {
               printf ("-->NOT FOUND\n" ) ;

               } ;
               printf ( "LENGHT OF THE PATH: " );
               printf ( " %d\n", L ) ;
               printf("\n Press any key to comeback to the menu.");
               getch();

               break;
            }

    case 7: { printf ("***SEARCH WORD IN BST0 ***\n" ) ;
              printf ("PLEASE ENTER A WORD :" ) ;
              scanf ( " %[^\n]", N1 ) ;
              Search_bst0 (&T0, &N1, &B , &L);
               if( ( B == True )) {
                printf ( "-->FOUND\n" ) ;
                }
             else
               {
               printf ("-->NOT FOUND\n" ) ;

               } ;
               printf ( "LENGHT OF THE PATH: " );
               printf ( " %d\n", L ) ;



              printf("\n Press any key to comeback to the menu.");
              getch();

               break;
            }

     case 8: { printf ("*** SEARCH RANGE ***\n" ) ;
               printf ("ENTER THE FIRST WORD : " ) ;
               scanf ( " %[^\n]", N1 ) ;
               printf ("ENTER THE SECOND WORD : " ) ;
               scanf ( " %[^\n]", N2 ) ;
               printf ("HERE ARE THE WORDS WITHIN THIS RANGE :\n" ) ;
               N  =  Range_search ( & T1 , & N1 , & N2 ) ;
               printf ( " %s", "NOMBRE TOTAL DE NOEUDS DANS CETTE INTERVAL : " ) ;
               printf ( " %d\n", N ) ;
               printf("\n Press any key to comeback to the menu.");
               getch();

               break;
            }
      case 9: {
                  printf ("\n***NUMBER OF WORDS STARTING WITH Z Y a IN BST1***" ) ;
                  Compter_xyz ( & T1 ) ;
                  printf ("\n***********" ) ;
                  printf ("\n***NUMBER OF WORDS STARTING WITH Z Y a IN BST2***" ) ;
                  Compter_xyz ( & T2 ) ;
                  printf ("\n***********" ) ;
                  printf ("\n***NUMBER OF WORDS STARTING WITH Z Y a IN BST3***" ) ;
                  Compter_xyz ( & T3 ) ;
                  printf ("\n***********" ) ;
                  printf ("\n***NUMBER OF WORDS STARTING WITH Z Y a IN BST0***" ) ;
                  Compter_xyz ( & T0 ) ;
                  printf("\nPress any key to comeback to the menu.");
                  getch();
             break;
              }





    case 10: { printf ("***Module 2:Implement a simulation algorithm to evaluate word search efficiency***\n" ) ;
              remplire_arb2 (& bst1 ,& bst2,& bst3,& bst0);
              printf("\n Press any key to comeback to the menu.");
              getch();

               break;
            }

    case 11: { printf ("***Module 3:Implement a simulation algorithm to evaluate the efficiency of word range search***\n" ) ;
              Module3(&bst0,& bst1 ,& bst2,& bst3);
              printf("\n Press any key to comeback to the menu.");
              getch();

               break;
            }
  default:
    {
      printf("Invalid Choice...\n\n");
      printf("\n\t\t\t\t      Press any key to try again: ");
      getch();
    }
  }

} while (menu != 0);



     printf ( " %s", "***********" ) ;
     printf ( " %s", "***********" ) ;
     printf ( " %s", "FIN DU PROGRAM" ) ;
     printf ( " %s", "REALISE PAR :BOUCENNA LEILA ET BOUARAB HIBA G14" ) ;


      system("PAUSE");
      return 0;
    }
