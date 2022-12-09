#ifndef CONSTANTE_Table
#define CONSTANTE_Table

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "FunctionAccommodation.h"


#define MALLOC(x,size) (x *)(malloc(sizeof(x)*size));
#define TRUE 1;
#define FALSE 0;

int Count_nb_line(FILE*); // Count number of lines-1 in a file (-1 because the fisrt line isn't data)
void Print_Tab(PAccommodation tab, int size); // Displays a accodommation table

PAccommodation Data_file_to_table(FILE* file,int tableSize,int version); // creation an table of airbnb's data base's accommodations, the characteristic files in the files are not in the same order in donnees propre and Test/Entrainement, so version = 1 is for donnees propre and version = 2 is for Test / Entrainement





#endif
