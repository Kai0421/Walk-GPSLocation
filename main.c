#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define d2r (M_PI / 180.0)
#define SIZE 100
#define RADIUS 20 //in the unit of Kilometers (KM)
#define CRNTLAT 51.888649   //current Latitude
#define CRNTLONG -8.524988  //Current Longitude

/**
* Student Name : Ren Kai Tam
* Student Number : R00095982
* All Original work from Kai Tam **/

struct Walks{

    char* nameOfWalk[SIZE]; // corrin
    char* county[SIZE]; //cork
    double distance; //500m
    double difficultLevel; //1
    double heightClimbed; //52meters
    double GPSLongCoord; //52.1
    double GPSLatcoord; //-8.1

};

//Declaration Of Methods
int readFromFile(struct Walks* arrWalks, char * fileName);  //Read the text file declaraton
void displayAllWalks(struct Walks* arrWalks, int numbOfWalks); //Declaration method for option 1
void displaySpecificCounty(struct Walks* arrWalks, int numbOfWalk); //Declaration method for option 2
void displaySortedByDistance(struct Walks* arrWalks, int numbOfWalks);//Declaration method for option 3
void displaySummaryWalks(struct Walks* arrWalks, int numbOfWalks);//Declaration method for option 4
void displayLongestWalk(struct Walks* arrWalks, int numbOfWalks);//Declaration method for option 5
void openFireFoxDisplayLocation(struct Walks* arrWalks, int numbOfWalks);//Declaration method for option 6
void displayWalkIn20KM(struct Walks* arrWalks, int numbOfWalks);//Declaration method for option 7

//Extra methods for each options
double distanceInKm(double lat1, double long1, double lat2, double long2);//Declaration method for option 7
void openFireFox(char* marker); //Declaration method for option 6
void clearScreen(); //Declaration for Clear Screen Methods
void printData(struct Walks* arrWalks, int i); //Declaration for printing data for each case

int main(int argc, char* argv[]){

    //Create array of walks structure
    struct Walks w[SIZE];

    int numbOfWalks = readFromFile(w, argv[1]);

    //Check to see is the number of argumens is greater than 2
    if (argc == 2)
    {
        enum {FALSE = 0, TRUE};
        int quit = FALSE;

        while (quit != TRUE)
        {
            printf("\n1.Display All Walks\n2.Display Walks for specific county\n3.Display Walks Sorting by distance\n4.Display Summary Walks\n");
            printf("5.Display Longest Walk\n6.Open Firefox\n7.Walks within 20KM\n8.Exit\n\nPlease select an option from the menu:");

            int option;
            scanf("%i", &option);

            switch(option)
            {
                case 1:
                    displayAllWalks(w, numbOfWalks);
                    break;

                case 2:
                    displaySpecificCounty(w, numbOfWalks);
                    break;

                case 3:
                    displaySortedByDistance(w, numbOfWalks);
                    break;

                case 4:
                    displaySummaryWalks(w, numbOfWalks);
                    break;

                case 5:
                    displayLongestWalk(w, numbOfWalks);
                    break;

                case 6:
                    openFireFoxDisplayLocation(w, numbOfWalks);
                    break;

                case 7:
                    displayWalkIn20KM(w, numbOfWalks);
                    break;

                case 8:
                    printf("choice of 8 - Exit");
                    quit = TRUE;
                    break;

                default: printf("Other\n");
            }
        }
    }
    else
    {
         printf("No Program arguments set");
    }
    return 0;
}

//Display & Verify if the walks in the surrounding of your current walks is within 20 mile - Method for Case 7
void displayWalkIn20KM(struct Walks* arrWalks, int numbOfWalks){

    //Applied Clear Screen
    clearScreen();

    double returnDistance[numbOfWalks];

    printf("\nD.L\t  H.Clm\t   Distce     Longitude latitude  Name  Co.\n");

    int i;
    for(i = 0; i < numbOfWalks; i++)
    {
        returnDistance[i] = distanceInKm( CRNTLAT, CRNTLONG, arrWalks[i].GPSLatcoord, arrWalks[i].GPSLongCoord);


        //If the distance is less than 20 KM Print out
        if (RADIUS > returnDistance[i])
        {
            printData(arrWalks, i);
        }
    }
}

//Identify the walks within 20 KM radius of your current location - Method for Case 7
double distanceInKm(double lat1, double long1, double lat2, double long2){
    double dlong = (long2 - long1) * d2r;
    double dlat = (lat2 - lat1) * d2r;
    double a = pow(sin(dlat/2.0), 2) + cos(lat1*d2r) * cos(lat2*d2r) * pow(sin(dlong/2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = 6367 * c;

    //Returning the distance between your current location and the destination of the walk
    return d;
}

//Open Firefox displaying the location of walks - Method for case 6
void openFireFoxDisplayLocation(struct Walks* arrWalks, int numbOfWalks){

    //Applied Clear Screen
    clearScreen();

    //request variable created here
    char currentLat[SIZE] = "", currentLong[SIZE] = "";
    char marker[SIZE*5] = ""; // Current Latitude And Longitude

    struct Walks corkWalk[SIZE];

    int level, i, a, countyCount = 0;

    for(a = 0; a < numbOfWalks; a++)
    {
        if(strcmp(arrWalks[a].county, "Cork") == 0)
        {
            corkWalk[countyCount] = arrWalks[a];
            countyCount++;
        }
    }

    for (i = 0; i < countyCount; i++)
    {
        char dLong[SIZE], dLat[SIZE];
        sprintf(dLong, "%f", corkWalk[i].GPSLongCoord);
        sprintf(dLat, "%f,", corkWalk[i].GPSLatcoord);

        //Concatenate Marker with longtitude and latitude
        strcat(marker, dLat);
        strcat(marker, dLong);
        strcat(marker, "/");
    }

    //converting current latitude longitude to String
    sprintf(currentLat, "%f,", CRNTLAT);
    sprintf(currentLong, "%f", CRNTLONG);

    //Concatenate current Location to the marker
    strcat(marker, currentLat);
    strcat(marker, currentLong);
    strcat(marker, "/");

    //Check Marker
    //printf("%s\n\n", marker);

    openFireFox(marker);
}

//Open Browser
void openFireFox(char* marker){

    char url[SIZE*6] = "start www.google.ie/maps/dir//"; // Using the URL
    strcat(url, marker); // Marker containing 2 coordinates

    //Using system command to start default web browser to launch the start command along with the URL
    system(url);
}

//Display Sorted Walks bby distance - Method for Case 3
void displaySortedByDistance(struct Walks* arrWalks, int numbOfWalks){

    //Applied Clear Screen
    clearScreen();

    int i, a, b;

    for (i = 0; i < numbOfWalks - 1; i++)
    {
        for (a = i + 1; a < numbOfWalks; a++)
        {
            if( arrWalks[a].distance < arrWalks[i].distance)
            {
                struct Walks temp;


                temp = arrWalks[i];
                arrWalks[i] = arrWalks[a];
                arrWalks[a] = temp;
            }
        }
    }

    printf("\nD.L\t  H.Clm\t   Distce     Longitude latitude  Name  Co.\n");
    for(b = 0; b < numbOfWalks; b++)
    {
       printData(arrWalks, b);
    }
}

//Display Detail of the longest walk - Method for Case 5
void displayLongestWalk(struct Walks* arrWalks, int numbOfWalks){

    //Applied Clear Screen
    clearScreen();

    struct Walks longest = arrWalks[0];

    int count = 0;
    while(count < numbOfWalks)
    {
        if(arrWalks[count].distance > longest.distance)
        {
            longest = arrWalks[count];
        }
        count++;
    }

    //print out
    printf("\nD.L\t  H.Clm\t   Distce     Longitude latitude  Name  Co.\n");
    printf("%f %f %f %f %f %s %s\n\n", longest.difficultLevel,  longest.heightClimbed, longest.distance, longest.GPSLongCoord, longest.GPSLatcoord, longest.nameOfWalk, longest.county);
}

//Display Summary of walks - Method for Case 4
void displaySummaryWalks(struct Walks* arrWalks, int numbOfWalks){

    //Applied Clear Screen
    clearScreen();

    char counties[SIZE][SIZE];
    int i, b = 0, count = 1;

    strcpy(counties[0], arrWalks->county);

    //This add all counties (but no duplicates county)
    while(b < count)//
    {
        for (i = 0; i < numbOfWalks; i++)
        {
            if(strcmp(arrWalks[i].county, counties[b]) == 1) // if the county is not equal
            {
                strcpy(counties[count], arrWalks[i].county);
                count++; // increment the counter to go to the next available index.
                b++; // if their not equal b add 1, to go to the next county to compare with array of walks county
            }
        }
        b++;
    }

//    Print out arrays of counties for checking purpose
//    int c;
//    for(c = 0; c < count; c++)
//    {
//        printf("\n\n%i %s", count, counties[c]);
//    }

    int a, d;
    for(a = 0; a < count; a++)
    {
        printf("%s\nD.L\t  H.Clm\t   Distce     Longitude latitude  Name  Co.\n", counties[a]);

        for(d = 0; d < numbOfWalks; d++)
        {
            if(strcmp(counties[a], arrWalks[d].county) == 0)
            {
                printData(arrWalks, d);
            }
        }
    }
}

//Display all walks - Method For Case 1
void displayAllWalks(struct Walks* arrWalks, int numbOfWalks){

    //Applied Clear Screen
    clearScreen();

    printf("\nD.L\t  H.Clm\t   Distce     Longitude latitude  Name  Co.\n");
    int i;
    for(i = 0; i < numbOfWalks; i++)
    {
        printData(arrWalks, i);
    }
}

//Display Walks for specific county - Method for Case 2
void displaySpecificCounty(struct Walks* arrWalks, int numbOfWalk){

    //Applied Clear Screen
    clearScreen();

    printf("Enter the county:");
    char county[256];
    scanf("%s", &county);

     printf("\nD.L\t  H.Clm\t   Distce     Longitude latitude  Name  Co.\n");
    int i;
    for (i = 0; i < numbOfWalk; i++)
    {
        if( strcmp(county, arrWalks[i].county) == 0)
        {
             printData(arrWalks, i);
        }
    }
}

//Read all the data from data.txt into the arrWalks array
int readFromFile(struct Walks* arrWalks, char * fileName){

    char mystring [SIZE];
    int count = 0;
    FILE* pFile;
    pFile = fopen(fileName, "r");

    if(pFile == NULL)
    {
        printf("No Such File");
    }
    else
    {
        while( fgets (mystring , 100 , pFile) != NULL )
        {
           // printf("%s\n", mystring);

            char s1[SIZE], s2[SIZE], s3[SIZE], s4[SIZE], s5[SIZE], s6[SIZE], s7[SIZE];
            char *ptr1, *ptr2, * ptr3, * ptr4, * ptr5;
            sscanf(mystring, "%s %s %s %s %s %s %s", s1, s2, s3, s4, s5, s6, s7);

            //converting to numbers
            arrWalks[count].difficultLevel = strtod(s1,&ptr1);
            arrWalks[count].heightClimbed = strtod(s2,&ptr2);
            arrWalks[count].distance = strtod(s3,&ptr3);
            arrWalks[count].GPSLatcoord = strtod(s4,&ptr4);
            arrWalks[count].GPSLongCoord = strtod(s5,&ptr5);

            strcpy(arrWalks[count].nameOfWalk, s6);
            strcpy(arrWalks[count].county, s7);

            count++;
        }
        fclose (pFile);
    }
    return count;
}

//Clear Screen Method
void clearScreen(){
    system("cls");
}

//Print out Method for each case
void printData(struct Walks* arrWalks, int i){
    printf("%f %f %f %f %f %s %s\n\n", arrWalks[i].difficultLevel,  arrWalks[i].heightClimbed, arrWalks[i].distance, arrWalks[i].GPSLongCoord, arrWalks[i].GPSLatcoord, arrWalks[i].nameOfWalk, arrWalks[i].county);
}
