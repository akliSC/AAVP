#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int DistanceLevenshteinIterative(char* motA, char* motB,int longueurA,int longueurB);
int DistanceLevenshteinRecursive(char* motA, char* motB,int longueurA,int longueurB);
int minimum(int a, int b, int c);
void DistanceLevenshteinIterativeCalculeTemps(char* motA, char* motB, int longueurA, int longueurB);
void DistanceLevenshteinRecursiveCalculeTemps(char* motA, char* motB, int longueurA, int longueurB);
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

	printf("La distance de Levenshtein itérative de {%s,%s} = %d\n",motA,motB,DistanceLevenshteinIterative(motA,motB,longueurA,longueurB));
	printf("La distance de Levenshtein récursive de {%s,%s} = %d\n",motA,motB,DistanceLevenshteinRecursive(motA,motB,longueurA,longueurB));
//DistanceLevenshteinIterativeCalculeTemps(motA,motB,longueurA,longueurB);
//DistanceLevenshteinRecursiveCalculeTemps(motA,motB,longueurA,longueurB);
	
}
int DistanceLevenshteinIterative(char* motA, char* motB, int longueurA, int longueurB){
	int ** Distance = (int **) malloc (sizeof(int *) * (longueurA +1));
	int i,j,remp,dist;
	// initalisation de la premiere ligne
	for(i = 0; i <= longueurA; i++)
		{
			Distance[i] = (int *) malloc (sizeof(int ) * (longueurB+1));
			Distance[i][0] = i;	
			
		}
	// initalisation de la premiere colonne
	for(j = 0; j <= longueurB; j++)
		{
			Distance[0][j] = j;	
			
		}
	// remplissage de tableau 
	for(i = 1; i <= longueurA; i++)
		{
			for(j = 1; j <= longueurB; j++)
				{
					if(motA[i-1] == motB[j-1])
						{
							remp = 0;
						}
					else
						{
							remp =1;
						}
					Distance[i][j] = minimum(Distance[i-1][j]+1,Distance[i][j-1]+1,Distance[i-1][j-1]+remp);
				}
		}
		// on stock la distance de levenshtein (la dernière case du tableau) dans dist
		dist = Distance[longueurA][longueurB];
		// free
		for(i= 0; i<= longueurA;i++)
			free(Distance[i]);
		free(Distance);
		return dist;

}
int DistanceLevenshteinRecursive(char* motA, char* motB,int longueurA,int longueurB){
	int a,b,c,remp;
	// si le motA est vide la distance est la taille de motB
	if(longueurA == 0){
		return longueurB;
	}
	// si le motB est vide la distance est la taille de motA
	if(longueurB == 0){
		return longueurA;
	}
	// on vérifier si le dernier caractère des deux mots est identiques
	if(motA[longueurA-1] == motB[longueurB-1])
		{
			remp = 0;
		}
	else
		{
			remp =1;
		}
a =DistanceLevenshteinRecursive(motA,motB,longueurA-1,longueurB)+1; // supression
b =DistanceLevenshteinRecursive(motA,motB,longueurA,longueurB-1)+1; // insertion
c =DistanceLevenshteinRecursive(motA,motB,longueurA-1,longueurB-1)+remp; // remplacement 
// on return le min entre a,b,c 
return minimum(a,b,c);
}
void DistanceLevenshteinIterativeCalculeTemps(char* motA, char* motB, int longueurA, int longueurB)
{

	clock_t tmp_debut;
	clock_t tmp_fin;
	double temp_exc;
	tmp_debut = clock();
	printf("temps debut itérative %ld\n", tmp_debut);
	DistanceLevenshteinIterative(motA, motB, longueurA, longueurB);
	tmp_fin = clock();
	printf("temps fin itérative %ld\n",tmp_fin);
        temp_exc = (double)(tmp_fin - tmp_debut)/ CLOCKS_PER_SEC;
        printf("le temps execution itérative %f\n", temp_exc);
}
void DistanceLevenshteinRecursiveCalculeTemps(char* motA, char* motB, int longueurA, int longueurB)
{

	clock_t tmp_debut;
	clock_t tmp_fin;
	double temp_exc;
	tmp_debut = clock();
	printf("temps debut Recursive %ld\n", tmp_debut);
	DistanceLevenshteinIterative(motA, motB, longueurA, longueurB);
	tmp_fin = clock();
	printf("temps fin Recursive %ld\n",tmp_fin);
        temp_exc = (double)(tmp_fin - tmp_debut)/ CLOCKS_PER_SEC;
        printf("le temps execution récursive %f\n", temp_exc);
}

int minimum( int a,int b, int c)
{
	if(a <= b && a <= c)
	{
		return a;
	}
	else if(b <= a  && b <= c)
	{
		return b;
	}
	else
	{	
		return c;
	}
}
