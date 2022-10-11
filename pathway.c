#include <stdlib.h>
#include "enzyme.h"
#include "pathway.h"

struct pathway {
  char *nom;
  int taille;
  ptr_enzyme *tab;
};

ptr_pathway creerpathway() {
  ptr_pathway voie = (ptr_pathway) malloc (sizeof(struct pathway));
  voie->nom = NULL;
  voie->taille = 0;
  voie->tab = NULL;
  return voie;
}

void saisie_voie(ptr_pathway voie) {
  int i;
  voie->nom=(char *)malloc(sizeof(char) * 30);
  printf("Nom de la voie métabolique?\n");
  scanf("%s", voie->nom);
  printf("Nombre d'enzymes\n");
  scanf("%d", &voie->taille);
  voie->tab=(ptr_enzyme *)malloc(sizeof(ptr_enzyme) * voie->taille);
  for (i=0; i<voie->taille; i++) {
    ptr_enzyme item = creerenzyme();
    item = saisie_enzyme(item);
    voie->tab[i]=item;
  }
}
    
void affichage_voie(ptr_pathway voie) {
  int i;
  printf("-------------\n");
  if (voie->taille==0 || voie == NULL) {
    printf("Le tableau est vide, veuillez le remplir.\n");
  } else {
    printf("Nom voie : %s, taille : %d\n", (voie->nom == NULL) ? "NULL" : voie->nom, voie->taille);
    for (i=0; i < voie->taille; i++) {
      affiche(voie->tab[i]);
    }
  }
  printf("-------------\n");
}

void ouvrir_voie(ptr_pathway voie, FILE* fichier) {
  char *_nom;
  int poids;
  voie->nom=(char *)malloc(sizeof(char) * 30);
  fscanf(fichier, "%s %d", voie->nom, &voie->taille);
  int j;
  voie->tab=(ptr_enzyme *)malloc(sizeof(ptr_enzyme) * voie->taille);
  for (j=0; j<voie->taille; j++) {
    _nom=(char *)malloc(sizeof(char) * 30); 
    fscanf(fichier, "%s %d", _nom, &poids);
    ptr_enzyme item=creer_enzyme(_nom,poids);
    voie->tab[j]=item;   
  }
}
  


void sauvegarder_voie(ptr_pathway voie, FILE* out) {
  int i;
  fprintf(out, "%s %d ", voie->nom, voie->taille);
  for (i=0; i<voie->taille; i++) {  
    sauvegarde(voie->tab[i], out);
  }
}
