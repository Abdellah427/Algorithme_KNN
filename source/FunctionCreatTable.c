#include "FunctionCreatTable.h"

int Count_nb_line(FILE* file) // Count number of lines-1 in a file (-1 because the fisrt line isn't data)
{
    char c;
    int count=0;
    for (c = getc(file); c != EOF; c = getc(file)) // advance through the whole file character by character
    {
        if (c == '\n') // if we past to new line
        {
        c=getc(file); // first character of next line 
            if (c >= '0' && c <= '9') count ++; // increment count if first character of newline is number between 0 and 9 (because can be space or line break)
        }

    }
    fseek(file,0,SEEK_SET); // put the cursor back to the beginning
    return count-1;
}

void Print_Tab(PAccommodation tab, int size) // Displays a accodommation table
{
    int i,j;
    for (i=0;i<size;i++){

        printf("Accommodation %d : ",i);
        
        for (j=0;j<7;j++)
        {
        printf("%f-",(tab+i)->data[j]);
        
        }

        printf("%f-",(tab+i)->price);
        printf("%f",(tab+i)->distance);
        
        
        printf("\n");

       
    }
}


PAccommodation Data_file_to_table(FILE* file,int tableSize,int version) // creation an table of airbnb's data base's accommodations, the characteristic files in the files are not in the same order in donnees propre and Test/Entrainement, so version = 1 is for donnees propre and version = 2 is for Test / Entrainement
{
    float tab[7];
    float d[3] = {0,0,0};
    float ValueUseless,price; // ValueUseless is use to hold the first line value (the id) which is not useful in this program
    int i,j;


    PAccommodation tableOfAccommodation = MALLOC(Accommodation,tableSize); 

    // Check if there was no memory allocation problem

    if (tableOfAccommodation==NULL)
    {
    	printf("Memory allocation error");
        exit(1);
    }
    
    while(fgetc(file)!='\n'); // Use for past the first line with name of data
    
    for(i=0;i<tableSize-1;i++)
    {

        if (version == 1) fscanf(file,"%f,%f,%f,%f,%f,%f,%f,%f,%f\n",&ValueUseless,&tab[0],&tab[1],&tab[3],&tab[2],&price,&tab[4],&tab[5],&tab[6]);
        else fscanf(file,"%f,%f,%f,%f,%f,%f,%f,%f,%f\n",&ValueUseless,&tab[0],&tab[1],&tab[3],&tab[2],&tab[4],&tab[5],&tab[6],&price);

        //I store the characteristics of the accommodation in the following order :
        //Accommodates Bedrooms Beds Bathrooms Minimum_nights Maximum_nights Number_of_reviews
        //I reversed places beds and Bathrooms for that the 3 characteristics that I will use are at the beginning
        Edit_Accommodation(tableOfAccommodation+i,tab,0,d,price);

    }


    fseek(file,0,SEEK_SET); 
    
    return tableOfAccommodation ;

}

