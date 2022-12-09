#include "FunctionCreatTable.h"
#include "FunctionAccommodation.h"


int main(int argc, char *argv[])
{
 
    
    FILE* file_airbnb_Data = NULL;
    FILE* file_airbnb_Entrainement = NULL;
    FILE* file_airbnb_Test = NULL; 
    PAccommodation tableOfAccommodation, tabEntrainement,tabTest;

    int i,k,sizeData,sizeEntrainement,sizeTest,MIN,MAX;
    float data[7],price,MAO=0;
    float* tabPrediction;
    PAccommodation Accommodation=Creat_Accommodation(data,0);
    char restart[10];
    
    
    
    file_airbnb_Data = fopen("./data/airbnb_donnees_propre.csv", "r");
    file_airbnb_Entrainement = fopen("./data/airbnbEntrainement.csv", "r");
    file_airbnb_Test = fopen("./data/airbnbTest.csv", "r");
 
    // Check that the file has been well open

    if (file_airbnb_Data == NULL || file_airbnb_Entrainement == NULL || file_airbnb_Test == NULL )
    {
         printf("File open error");
         exit(1);
    }

    
    // Create a table that will contain the accommodation of the airbnb's data base

    
    sizeData = Count_nb_line(file_airbnb_Data); // size_airbnb_Data represent the number of accommodation in the airbnb's data base
    tableOfAccommodation = Data_file_to_table(file_airbnb_Data,sizeData,1); // creation an table of airbnb's data base's accommodations

    /* Question A,B,C and D */

    printf("\nDo you want to make a new price prediction, find the most efficient k (BONUS) or exit ? (price\\bonus\\exit) \n\n");

    scanf("\n%s", restart);

    while(restart[0]=='p' || restart[0]=='b')
    {

        
        while(restart[0]=='p')// I ask at the end if the user wants to estimate another price
        {

            Edit_Accommodation_By_User(Accommodation); // modify the accommodation with the values ​​provided by the user

            printf("\nWhat is the desired value of k ? ( k must be less than or equal to %d )\n\n",sizeData);

            scanf("%d", &k);

            Distance(Accommodation,tableOfAccommodation);

            price = Predict_Price(Accommodation,tableOfAccommodation,sizeData,k); // defines the price of the accommodation entered by the user according to k
            
            printf("\nThe predicted price is : %.2f $\n",price);

            printf("\nDo you want to make a new price prediction, find the most efficient k (BONUS) or exit ? (price\\bonus\\exit) \n\n");

            scanf("\n%s", restart);

        }

        /* Question E,F,G,H,I and J*/

        while(restart[0]=='b')// I ask at the end if the user wants to find another k 
        {

            printf("\nWe can find the value of k the most efficient in an interval\n\nIndicate the desired interval in the form : MIN MAX\n\nExample : To get the most efficient value of k between 1 and 100 type : 1 100\n\n");
            
            scanf("%d %d", &MIN,&MAX);

            printf("\n\nThe most efficient value of k is : %d",Find_Better_k(MIN,MAX));

            printf("\n\nDo you want to make a new price prediction, find the most efficient k (BONUS) or exit ? (price\\bonus\\exit) \n\n");

            scanf("\n%s", restart);

        }
    }
    fclose(file_airbnb_Data);
    free(tableOfAccommodation);
    free(Accommodation);
    
    return 0;

   


}
