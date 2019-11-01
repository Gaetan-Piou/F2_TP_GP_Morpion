#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TAILLE 3

int demandeCoordonnee(int joueur, char absOrd);
int conditionVictoire(int joueur, int nTab[TAILLE][TAILLE]);
int changeTourJoueur(int tourJoueur);
void dessinPlateau(int nTab[TAILLE][TAILLE]);
void finPartie(int gagnant);

void main()
{
    int nTabJeu[TAILLE][TAILLE];    //Tableau gérant la grille de Morpion
    int i,j;                        //Variables utilisees dans les boucles for
    int victoire=0;                 //Variable verifiant si une condition de fin est verifiee : 0: Aucune condition de victoire, 1: Victoire du joueur 1, 2: Victoire du joueur 2, -1: Grille remplie & egalite
    int tourJoueur=1;               //Verifie quel joueur est en train de jouer
    int tours=0;                    //Verifie combien de tours sont passes
    int x,y;                        //Les coordonnees du prochain coup du joueur

    //Initialisation du tableau
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            nTabJeu[i][j] = 0;
        }
    }

    //On affiche la grille de morpion
    dessinPlateau(nTabJeu);


    //Boucle de jeu
    while(victoire==0) {

        //On demande les coordonnees X et Y du prochain coup au joueur, puis on verifie si ces dernieres ne sont pas occupees
        x=demandeCoordonnee(tourJoueur,'X');
        y=demandeCoordonnee(tourJoueur,'Y');
        while(nTabJeu[x][y] != 0) {
            printf("La case correspondant a ces coordonnees est deja occupee, veuillez reesayer\n");
            x=demandeCoordonnee(tourJoueur,'X');
            y=demandeCoordonnee(tourJoueur,'Y');
        }

        //On remplit la case donnee par le joueur
        nTabJeu[x][y] = tourJoueur;

        //On reaffiche la grille mise a jour
        dessinPlateau(nTabJeu);

        //On verifie si une condition de victoire a ete remplie
        victoire = conditionVictoire(tourJoueur,nTabJeu);

        //On incremente les tours et on met fin a la partie si 9 tours sont passes
        if(victoire == 0) {
            tours++;
            if(tours == 9) {
                victoire = -1;
            }
        }

        //On change de joueur pour le prochain tour
        tourJoueur = changeTourJoueur(tourJoueur);
    }

    //On affiche les resultats
    finPartie(victoire);

}


int demandeCoordonnee(int joueur, char absOrd) {
//BUT: Demander la position x ou y du prochain coup du joueur actif
//ENTREE:   int joueur: le joueur actif
//          char absOrd: determine si on demande la position X ou la position Y du prochain coup
//SORTIE:   La coordonnee donnee par le joueur

    int coordonnee;
    printf("Joueur %d, veuillez saisir la position %c de votre prochain coup (entre 1 et 3)\n",joueur,absOrd);
    fflush(stdin);
    scanf("%d",&coordonnee);
    while(coordonnee<1 || coordonnee>3) {
        printf("ERREUR ! La valeur saisie est incorrecte.\n Joueur %d, veuillez saisir la position %c de votre prochain coup (entre 1 et 3)\n",joueur,absOrd);
        fflush(stdin);
        scanf("%d",&coordonnee);
    }
    return coordonnee-1;

}

int conditionVictoire(int joueur, int nTabVerif[TAILLE][TAILLE]) {
//BUT: Verifier si une condition de victoire a ete remplie apres un coup
//ENTREE:   int joueur: le joueur ayant joue son tour
//          int nTabVerif[TAILLE][TAILLE]: la grille de morpion
//SORTIE:   0 si aucune condition de victoire n'a ete remplie
//          1 ou 2 si la condition de victoire a ete remplie par le joueur 1 ou 2

    int i,j;
    int compteur1=0;
    int compteur2=0;
    int aligne=0;

    //Verification des lignes et colonnes
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(nTabVerif[j][i]==joueur) {
                compteur1++;
            } else {
            }
            if(nTabVerif[i][j]==joueur) {
                compteur2++;
            } else {
            }
        }
        if(compteur1==3 || compteur2==3) {
            aligne=joueur;
        } else {
            compteur1=0;
            compteur2=0;
        }
    }

    //Verification des diagonales
    if(aligne==0) {
        for(i=0; i<3; i++) {
            if(nTabVerif[i][i] == joueur) {
                compteur1++;
            }
            if(nTabVerif[2-i][i] == joueur) {
                compteur2++;
            }
        }
        if(compteur1==3 || compteur2==3) {
            aligne=joueur;
        }
    }

    return aligne;

}


int changeTourJoueur(int tourJoueur) {
//BUT: Passer d'un joueur a un autre entre les tours
//ENTREE:   int tourJoueur: le joueur ayant joue au tour precedent
//SORTIE:   Le joueur jouant au prochain tour

    int tourProchain;
    if(tourJoueur == 1) {
        tourProchain = 2;
    } else {
        tourProchain = 1;
    }
    return tourProchain;
}


void dessinPlateau(int nTab[TAILLE][TAILLE]) {
//BUT: Dessiner le plateau avec les O et les X des joueurs dessus.
//ENTREE:   int nTab[TAILLE][TAILLE]: Le tableau du plateau de jeu.
//SORTIE:   Rien.

    int i,j;
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if (nTab[j][i]==1) {
                printf(" O ");
            } else if (nTab[j][i]==2) {
                printf(" X ");
            } else {
                printf("   ");
            }
            if(j<2) {
                printf("|");
            }
        }
        printf("\n");
        if(i<2) {
            printf("-----------\n");
        }
    }
    printf("\n");
}

void finPartie(int gagnant) {
//BUT: Afficher les resultats en fin de partie
//ENTREE:   int gagnant: Le joueur gagnant ou -1 s'il y a egalite
//SORTIE:   Rien.

    printf("Fin de la partie !\n");
    if(gagnant == -1) {
        printf("Egalite !\n");
    } else {
        printf("Le gagnant est le joueur %d !",gagnant);
    }
}
