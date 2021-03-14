#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int DistanceHamming(char* motA, char* motB,int longueurA,int longueurB);
void  DistanceHammingCalculeTemps(char* motA, char* motB, int longueurA, int longueurB);
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

	printf("La distance de Hamming de (%s,%s) = %d\n",motA,motB,DistanceHamming(motA,motB,longueurA,longueurB));
	DistanceHammingCalculeTemps(motA,motB,longueurA,longueurB);
}

int DistanceHamming(char* motA, char* motB, int longueurA, int longueurB)
{
	 int i;
	 int distance = 0;
	if(longueurA != longueurB) 
	{
		printf("les deux mots ne sont pas de la meme longueur\n");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < longueurA; i++)
			if(motA[i] != motB[i])
				distance = distance + 1;
	return distance;
}


void DistanceHammingCalculeTemps(char* motA, char* motB, int longueurA, int longueurB)
{

	clock_t tmp_debut;
	clock_t tmp_fin;
	double temp_exc;
	tmp_debut = clock();
	printf("temps debut %ld\n", tmp_debut);
	DistanceHamming(motA, motB, longueurA, longueurB);
	tmp_fin = clock();
	printf("temps fin %ld\n",tmp_fin);
        temp_exc = (double)(tmp_fin - tmp_debut)/ CLOCKS_PER_SEC;
        printf("le temps execution %f\n", temp_exc);
}
