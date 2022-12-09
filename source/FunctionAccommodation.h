#ifndef CONSTANTE_Accommodation
#define CONSTANTE_Accommodation

typedef struct Accommodation Accommodation;
typedef Accommodation* PAccommodation;

#include "FunctionCreatTable.h"

struct Accommodation
{
    float data[7]; // contains the characteristics of the accommodation
    float d[3]; // contains the distances according to the characteristics : Accommodates, Bedrooms and Beds
    float price; // contain price
    float distance; // contain total distance
};


PAccommodation Creat_Accommodation(float data[7], float price); // function to create accommodation, set table d[3] and distance to 0
void Edit_Accommodation(PAccommodation,float data[7],float distance,float d[3], float price); // function to edit accommodation
void Edit_Accommodation_By_User(PAccommodation); // modify the accommodation with the values ​​provided by the user
void Distance(PAccommodation Accommodation1,PAccommodation Accommodation2); // Calculates the distances and the total distance between 2 accommodations
void Calculate_Distance_Similarity(PAccommodation Accommodation, PAccommodation tableOfAccommodation , int size); // Calculate the distance between a accommodation and all those in the TableOfAccommodation
void Swap(PAccommodation a, PAccommodation b); // Swap two PAccommodation
void Sort_Quick(PAccommodation tab, int first, int last);// sort by recursive division
void Mix(PAccommodation tab,int size);// I mix randomly the TableOfAccommodation
float Predict_Price(PAccommodation Accommodation,PAccommodation table,int size, int k); // I assemble all the functions to make a program that estimates the price with k random accommodation in the table
float Calculate_MAO(PAccommodation tabTest,float* tabPrediction,int sizeTest); // Calculate MAO
int Find_Better_k(int MIN,int MAX);



#endif