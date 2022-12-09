#include "FunctionAccommodation.h"

PAccommodation Creat_Accommodation(float data[7],float price) // function to create accommodation, set table d[3] and distance to 0
{
    PAccommodation Accommodation1 = MALLOC(Accommodation,1);
    
    int j;
    
    // Check if there was no memory allocation problem
    
    if (Accommodation1==NULL)
    {
    	printf("Memory allocation error");
        exit(1);
    }

    
    for (j=0;j<7;j++) // set data
        {
            (Accommodation1->data)[j] = data[j];
        }
    for (j=0;j<3;j++) Accommodation1->d[j]=0; // set d[3] to table of 0
    Accommodation1->distance=0; // set distance to 0
    Accommodation1->price=price; // set price

    return Accommodation1;


}

void Edit_Accommodation(PAccommodation Accommodation,float data[7],float distance,float d[3], float price) // function to edit accommodation
{
    int j;
    for (j=0;j<7;j++) // set data
        {
            (Accommodation->data)[j] = data[j];
        }
    Accommodation->distance=distance; // set distance
    for (j=0;j<3;j++) Accommodation->d[j]=d[j]; // set d[3]
    Accommodation->price=price; // set price

}

void Edit_Accommodation_By_User(PAccommodation Accommodation) // modify the accommodation with the values ​​provided by the user
{
    int i;
    float data[7],d[3]={0};

    // I ask the user for the characteristics of the accommodation (without price)

    printf("\n\nWhat are the characteristics of the accommodation ?\n\nIndicate them separated by a space and in the following order : \n\nAccommodates Bedrooms Bathrooms Beds Minimum_nights Maximum_nights Number_of_reviews\n\n");

    scanf("%f %f %f %f %f %f %f",&data[0],&data[1],&data[3],&data[2],&data[4],&data[5],&data[6]);

    Edit_Accommodation(Accommodation,data,0,d,0); // modify the accommodation with the values ​​provided by the user
}



void Distance(PAccommodation Accommodation1,PAccommodation Accommodation2) // Calculates the distances and the total distance between 2 accommodations
{
    int i;
    float distance;
  
    for (i=0; i<3;i++) 
    {
        Accommodation2->d[i]= pow( (Accommodation1->data[i]) - (Accommodation2->data[i]) , 2); // I apply the distance formula for the first 3 characteristics of the table : (x1-x2)^2
        distance += Accommodation2->d[i]; // I store the sum of the 3 distances for formula of total distance
    }
    distance = sqrt(distance); // I apply formula of total distance

    Accommodation1->distance = distance; 
    Accommodation2->distance = distance; // set distance in Accommodation1 and Accommodation2, I stock it in both so that the order of the accommodation does not matter
}

void Calculate_Distance_Similarity(PAccommodation Accommodation, PAccommodation tableOfAccommodation, int size) // Calculate the distance between a accommodation and all those in the TableOfAccommodation
{
    int i;

    for (i=0; i<size; i++)  Distance( Accommodation,tableOfAccommodation+i); // I execute the distance function between the accommodation and the i element of the TableOfAccommodation
    
}

void Swap(PAccommodation a, PAccommodation b) // Swap two PAccommodation
{
    float data[7]={0};
    PAccommodation tmp = Creat_Accommodation(data,0);

    Edit_Accommodation(tmp,a->data,a->distance,a->d,a->price); // tmp = a
    Edit_Accommodation(a,b->data,b->distance,b->d,b->price); // a = b
    Edit_Accommodation(b,tmp->data,tmp->distance,tmp->d,tmp->price);// b = tmp

    free(tmp);
}
void Sort_Quick(PAccommodation tab, int first, int last) // sort by recursive division
{
    int pivot, i, j;
    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while((tab+i)->distance <= (tab+pivot)->distance && i < last)  // find the min in left
                i++;
            while((tab+j)->distance  > (tab+pivot)->distance) // find the max in left
                j--;
            if(i < j) {
                Swap(tab+i, tab+j); // I swap min and max
            }
        }
        Swap(tab+pivot, tab+j); // swap tab[pivot] with max
        Sort_Quick(tab, first, j - 1);
        Sort_Quick(tab, j + 1, last);
    }

}

void Mix(PAccommodation tab,int size) // I mix randomly the TableOfAccommodation
{
    int i,randomNb,index;
    float data[7]={0};
    PAccommodation tmp = Creat_Accommodation(data,0);
    srand(time(NULL)); // I initialize srand to the current time

    for(i=0;i<size;i++)
    {
        // Idea: roll Accommodation  by Acoommodation and exchange each Accommodation  with another Accommodation of the table at random

        randomNb = rand() % size; // I generate a random number between 0 and size-1, this represents the index of the Accommodation to be exchanged
    
        //I swap the two accommodations

        Swap(tab+randomNb,tab+i);
      
    }
}

float Predict_Price(PAccommodation Accommodation,PAccommodation table,int size, int k) // I assemble all the functions to make a program that estimates the price with k random accommodation in the table
{

    int i;
    float price =0;
    if (k>size)
    {
        printf("Error : k is greater than the number of line in data file");
        exit(1);
    }
    
    Mix(table,size); // I mix the table so as not to always have the same k first accommodations
   
    Calculate_Distance_Similarity(Accommodation,table,size); // Calculate distance of k first accommodations of TableOfAccommodation
   
    Sort_Quick(table,0,size-1); // Sort the k first accommodations of TableOfAccommodation

    //Print_Tab(table,5);
    for (i=0;i<k;i++) price += (table+i)->price; // Sum of price of k first accommodation of TableOfAccommodation

    return price/k; // return average of price
}


float Calculate_MAO(PAccommodation tabTest,float* tabPrediction,int sizeTest)
{
    int i;
    float MAO;
    for(i=0;i<sizeTest;i++) MAO += abs(tabPrediction[i]-(tabTest+i)->price);
    return MAO / sizeTest;
}


int Find_Better_k(int MIN, int MAX)
{
    FILE* file_airbnb_Entrainement = NULL;
    FILE* file_airbnb_Test = NULL; 
    PAccommodation tabEntrainement,tabTest;
    int i,k,betterk,sizeEntrainement,sizeTest;
    float* tabPrediction;
    float price,MAO=0,min;
    unsigned long secondes;


    file_airbnb_Entrainement = fopen("./data/airbnbEntrainement.csv", "r");
    file_airbnb_Test = fopen("./data/airbnbTest.csv", "r");
 

    // Check that the file has been well open

    if (MIN>=MAX)
    {
         printf("MIN need less than to MAX");
         exit(1);
    }

    if (file_airbnb_Entrainement == NULL || file_airbnb_Test == NULL )
    {
         printf("File open error");
         exit(1);
    }

    sizeEntrainement = Count_nb_line(file_airbnb_Entrainement); // size_airbnb_Entrainement represent the number of accommodation in the airbnb's data base
    tabEntrainement = Data_file_to_table(file_airbnb_Entrainement,sizeEntrainement,2); // creation an table of airbnb's test base's accommodations

    sizeTest = Count_nb_line(file_airbnb_Test); // size_airbnb_Test represent the number of accommodation in the airbnb's data base
    tabTest = Data_file_to_table(file_airbnb_Test,sizeTest,2); // creation an table of airbnb's test base's accommodations


    tabPrediction = MALLOC(float,sizeTest); 

    // Check if there was no memory allocation problem

    if (tabPrediction==NULL)
    {
    	printf("Memory allocation error");
        exit(1);
    }
    
    time_t begin = time( NULL );

    for (i=0; i<sizeTest; i++) // calculate price for every accommodation of airbnbTest
    {
        price=Predict_Price(tabTest+i,tabEntrainement,sizeEntrainement,MIN);
        tabPrediction[i]=price;
    }
    
    time_t end = time( NULL);
    secondes = (unsigned long) difftime( end, begin );
    secondes = secondes * (MAX-MIN);

    printf( "\nCalculation time estimate : %ld sec\n\n", secondes );  
    
    min = Calculate_MAO(tabTest,tabPrediction,sizeTest);

    betterk=0;

    for(k=MIN+1;k<MAX;k++) 
    {
        for (i=0; i<sizeTest; i++) // calculate price for every accommodation of airbnbTest
        {
            price=Predict_Price(tabTest+i,tabEntrainement,sizeEntrainement,k);
            tabPrediction[i]=price;
        }

        
        MAO = Calculate_MAO(tabTest,tabPrediction,sizeTest);
        
        if(min>MAO){
            
            betterk=k;
            
        }
        
    }




    fclose(file_airbnb_Entrainement);
    fclose(file_airbnb_Test);

    return betterk;
    
}
