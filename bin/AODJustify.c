#include <stdio.h>
#include <stdlib.h>

/*
Ouvre un fichier à caractères codés en ISO 8859-1 -> renvoie
Met le fichier en mémoire virtuelle pour qu'il puisse être parcouru comme un tableau.
Renvoie "AODJustify CORRECT>" suivi de la norme 3 du fichier produit au format ISO 8859-1 si le programme s'est bien exécuté.
Renvoie "AODJustify ERROR>" suivi d’un message précisant l’erreur ; aucun fichier file.out n’est alors produit.
*/
void open_file(const char* nomFichier){
    FILE *f;
    f = fopen(nomFichier, "w+");
    /* TODO */

}

/*J'utile la formule de la solution 2 ici.*/
long long psi(int i, int m, FILE* f){
    for (int k; k < i + m + 1; k++){
        if (f[k]=="\n" and f[k+1]=="\n"){ /* ici ça ne fonctionne pas mais en gros l'idée c'est de dire qu'il y une fin de paragraphe dans le lot.*/
            return 0;
        }
    return 1;
    }
}

int main(){
    return 0;
}
