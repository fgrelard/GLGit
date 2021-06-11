#include <stdio.h>
#include <stdlib.h>
#include "enzyme.h"
#include "pathway.h"
#include "liste.h"
#define MAX 3

/*Liste des fonctions à utiliser */
void afficheMenu();
void saisie(liste);
void affichage(liste);
void ouvrir(liste, char *);
void sauvegarder(liste);

static int cpt=0;

int main(int argc, char *argv[]) {
    liste list_pathway = creerliste();
    int reponse;
    char *nom_fichier;
    nom_fichier=(char *)malloc(sizeof(char)*30);
    while(1) {
        afficheMenu();
        scanf("%d", &reponse);
        switch (reponse) {
        case 1: {saisie(list_pathway);break;}
        case 2: {affichage(list_pathway);break; }
        case 3: {sauvegarder(list_pathway);break;}
        case 4: {
            printf("Quel fichier voulez-vous ouvrir?\n");
            scanf("%s",nom_fichier);
            ouvrir(list_pathway, nom_fichier);
            break;
        }
        case 5: {list_pathway=supprimer(list_pathway);break;}
        case 0: {return 0;}
        }
    }
    return 0;
}


void saisie(liste list_pathway) {
    int i;
    char *nom;
    int poids;
    int nombre;
    printf("Combien de voies?\n");
    scanf("%d", &nombre);
    for (i=0; i<nombre; i++) {
        ptr_pathway item=creerpathway();
        saisie_voie(item);
        ajouter(list_pathway,item);
        cpt++;
    }
}
    
void affichage(liste list_pathway) {
    int i;
    if (case_vide(list_pathway)) printf("Le tableau est vide, veuillez le remplir.\n");
    else {
        afficherliste(list_pathway);
    }
}
			     
void ouvrir(liste list_pathway, char *nom) {
    FILE *fichier;
    ptr_pathway item;
    char *_nom;
    int poids;
    fichier = fopen(nom, "r");
    if (fichier == NULL)
        printf("Mauvais fichier\n");
    else {
        do {
            item = creerpathway();
            ouvrir_voie(item, fichier);
            ajouter(list_pathway,item);
        }
        while (fgetc(fichier) != EOF);
        fclose(fichier);
    }
    printf("Chargement terminé\n");
}


void sauvegarder(liste list_pathway) {
    liste tmp = list_pathway;
    FILE *out;
    int i;
    out=fopen("resul","w");
    if (case_vide(list_pathway)) printf("Le tableau est vide, veuillez le remplir.\n");
    else {
        while (!case_vide(tmp)) {
            sauvegarder_voie(retourcontenu(tmp), out);
            tmp=case_suivante(tmp);
        }
    }
    fclose(out);
}

void afficheMenu() {
    printf("Programme Enzyme\n");
    printf("1. Entrer informations\n");
    printf("2. Afficher\n");
    printf("3. Sauvegarder\n");
    printf("4. Ouvrir un fichier\n");
    printf("5. Supprimer\n");
}
