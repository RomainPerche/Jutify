#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <math.h>
#include <ctype.h>

long int file_length(FILE *fp);
int end_of_paragraph(char *fp, int total_length, int i, int M);
long long psi(char* file, int i, int M, long long num_carac, int *space_list, long long *mem);
char TEST_DIR[100] = "../Benchmark/";

/*
Ouvre un fichier à caractères codés en ISO 8859-1 -> renvoie
Met le fichier en mémoire virtuelle pour qu'il puisse être parcouru comme un tableau.
Renvoie "AODJustify CORRECT>" suivi de la norme 3 du fichier produit au format ISO 8859-1 si le programme s'est bien exécuté.
Renvoie "AODJustify ERROR>" suivi d’un message précisant l’erreur ; aucun fichier file.out n’est alors produit.
*/
char* open_file(const char* nomFichier, long long *length){
    FILE *nouveauFichier = NULL;
    FILE *fichier = fopen(strcat(TEST_DIR, nomFichier), "r");
    char *carac = NULL;
    if (fichier == NULL) {
        printf("zizi\n");
    }
    else {
        int fd = fileno(fichier);
        *length = file_length(fichier);
        printf("longueur : %d\n", *length);
        //Tableau de caractères du fichier.
        carac = mmap(NULL, *length, PROT_READ, MAP_PRIVATE, fd, 0);
        fclose(fichier);
    }
    return carac;
    /*Nouveau fichier dans lequel on va écrire le texte justifié.*/
    //nouveauFichier = fopen(strcat(nomFichier, "Justified"), "w+");
}

/* Renvoie la longueur du fichier en nombre de caractères. */
long int file_length(FILE *fp){
    //On va à la fin.
    fseek(fp, 0L, SEEK_END);
    long int size = ftell(fp);
    //On se remet au début pour la suite.
    fseek(fp, 0L, SEEK_SET);
    return size;
}

/* Renvoie 1 si la fin du paragraphe se trouve dans les M caractères après
le caractère i. Le caractère '\r' marque la fin d'un paragraphe s'il est
précédé d'un '\n' et suivi d'un '\n'. */
int end_of_paragraph(char* tab, int total_length, int i, int M) {
    for (int k = i; (k < i + M) && (k+3 < total_length); k++){
        if ((tab[k+1] == '\n') && (tab[k+2] == '\r') && (tab[k+3] == '\n')){
            return 1;
        }
    }
    return 0;
}

/* Renvoie la norme 3 optimisée du texte justifié. Ecrit un 1 dans la liste
space_list à chaque position où il faut ajouter un espace. mem est la liste des
appels mémoïsés. space_list et mem ont une taille égale au nombre de caractères
dans le fichier. */
long long psi(char *file, int i, int M, long long num_carac, int *new_line_list, long long *mem){
    if (end_of_paragraph(file, num_carac, i, M)) {
        return 0;
    }
    if (mem[i] != -1) {
        return mem[i];
    }
    long long mini = INFINITY;
    long long arg_min = 0;
    long long val = mini;
    for (int k = i; k <= i+M; k++){
        if (file[k] == ' ' | file[k] == '\r'){
            val = psi(file, k+1, M, num_carac, new_line_list, mem) + pow(M-(k-i), 3);
        }
        if (val < mini) {
            mini = val;
            arg_min = k;
        }
    }
    new_line_list[arg_min] = 1;
    mem[i] = mini;
    return mini;
}

void afficher_tab(int *tab, int length){
    for (int i=0; i < length; i++){
        if (tab[i] == 1){
            printf("%d\n", i);
        }
    }
}

int main(){
    long long *length = malloc(sizeof(long long));
    char *tab = open_file("court-un-paragraphe-8859-1.in", length);
    printf("HHHHHHHHHHHHHHHHHHHHHHHHH");
    //printf("%c", tab[45]);
    /*
    for (int k = 0; k < *length; k++) {
        if (tab [k] == ' ') {
            //printf("%d\n", k);
        }
    }
*/
    int *new_line_list = calloc(*length, sizeof(int));
    long long *mem = malloc(*length * sizeof(long long));
    for (int i=0; i < *length; i++){
        mem[i] = -1;
    }
    printf("%d\n", psi(tab, 0, 54, *length, new_line_list, mem));
    afficher_tab(new_line_list, *length);
    return 0;
}
