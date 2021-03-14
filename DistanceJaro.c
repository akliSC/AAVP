#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TRUE    1
#define FALSE   0
int maximum(int a,int b);
int minimum(int a, int b);
double DistanceJaro(char* motA, char* motB,int longueurA,int longueurB);
void DistanceJaroCalculeTemps(char* motA, char* motB, int longueurA, int longueurB);
int main (int argc, char* argv[])
{

	if(argc < 3) {
		printf("le nombre d'argument est  trop peu, Veuillez entrer 2 mots\n");
		exit(EXIT_FAILURE);
	}

	char* motA = NULL;
	char* motB = NULL;
	int longueurA = 0;
	int longueurB = 0;

	motA = strdup(argv[1]);
	motB = strdup(argv[2]);

	longueurA = strlen(motA);
	longueurB = strlen(motB);

	printf("La distance de Jaro de (%s,%s) = %f\n",motA,motB,DistanceJaro(motA,motB,longueurA,longueurB));
	DistanceJaroCalculeTemps(motA,motB,longueurA,longueurB);
	
}
double DistanceJaro(char* motA, char* motB,int longueurA,int longueurB){
    double correspondance = 0.0;
    double transposition = 0.0;
    /* si les deux mot sont vides le programme retroune 1
    si l'un des mots est vide le programme retourne 0 */
    if (longueurA == 0 && longueurB == 0)
    {
    	return 1.0;
    } else if (longueurA == 0 || longueurB == 0){return 0.0;}
    /*on calcule le max eloignement entre deux caractères */
    int max_eloignement = (int) maximum(longueurA, longueurB)/2 - 1;
    /* deux tableau boolean pour savoir si un caractère correspont d'unmot à un autre caractère d'un autre mot */
    int *corresA = calloc(longueurA, sizeof(int));
    int *corresB = calloc(longueurB, sizeof(int));
    /* on cherche les correspondance */
    for (int i = 0; i < longueurA; i++) {
        int deb = maximum(0, i - max_eloignement);
        int fin = minimum(i + max_eloignement + 1, longueurB);
        for (int j = deb; j < fin; j++) {
            if (corresB[j]) continue; /* si motB a deja correspondance */
            if (motA[i] != motB[j]) continue; /* si les deux caractères ne coresspondent pas*/
            corresA[i] = TRUE;
            corresB[j] = TRUE;
            correspondance++;
            break;
        }
    }
    /*si le nombre de correspondance est null en retourne 0*/
    if (correspondance == 0) {
        free(corresA);
        free(corresB);
        return 0.0;
    }
    /*on calcule les transpositions*/
    int j = 0;
    for (int i = 0; i < longueurA; i++) {
        if (!corresA[i]) continue;
        while (!corresB[j]) j++;
        if (motA[i] != motB[j]) transposition++;
        j++;
    }
    /* on devise le nombre transposition par deux */
    transposition = transposition/2.0;
    free(corresA);
    free(corresB);
    /* on retourne la distance de jaro */
    return ((correspondance / longueurA) +(correspondance / longueurB) +((correspondance - transposition) / correspondance)) / 3.0;
}
void DistanceJaroCalculeTemps(char* motA, char* motB, int longueurA, int longueurB)
{

	clock_t tmp_debut;
	clock_t tmp_fin;
	double temp_exc;
	tmp_debut = clock();
	printf("temps debut %ld\n", tmp_debut);
	DistanceJaro(motA, motB, longueurA, longueurB);
	tmp_fin = clock();
	printf("temps fin %ld\n",tmp_fin);
        temp_exc = (double)(tmp_fin - tmp_debut)/ CLOCKS_PER_SEC;
        printf("le temps execution %f\n", temp_exc);
}


int maximum(int a,int b)
{
	if(a>b){return a;}else{return b;}
}
int minimum(int a,int b)
{
	if(a<b){return a;}else{return b;}
}
