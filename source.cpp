// FUNCTION LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// CONSTANTS
#define BUF_SIZE 30
#define LOOP_AMT 5



/*  STRUCT DATA TYPE    :       FlightInfo
    FIELDS              :       char* flightDest - flight destination
                                char* flightDate - flight date
    DESCRIPTION         :       Data type stores flight information.     
 */
struct FlightInfo
{
	char* flightDest = NULL;
	char* flightDate = NULL;
};



// FUNCTION PROTOTYPES
void clearCR(char* buf);                                                    // clears carriage return
void fillFlightInfo(FlightInfo* flight, char* destination, char* date);       // allocates and stores memory for flight data
void printFlightInfo(FlightInfo flights[]);


int main(void)
{
    // initialize variables
    int i = 0;                                  // counter
    char inputDest[BUF_SIZE];                   // c-string for destination
    char inputDate[BUF_SIZE];                   // c-string for date
    FlightInfo flights[LOOP_AMT];               // array of FlightInfo
    FlightInfo* structPointer = NULL;           // struct pointer
    structPointer = flights;                    // struct pointer points to first element of array

    // prompt user for flights
    while (i < LOOP_AMT)
    {
        printf("Enter a flight destination: "); // destination prompt
        fgets(inputDest, BUF_SIZE, stdin);      // obtain user input
        clearCR(inputDest);                     // clear carriage return
        
        // date prompt
        printf("Enter a flight date: ");        // date prompt
        fgets(inputDate, BUF_SIZE, stdin);      // obtain user input
        clearCR(inputDate);                     // clear carriage return

        // allocate and fill memory
        fillFlightInfo(structPointer, inputDest, inputDate);

        printf("\n");

        structPointer++;                        // increment position of struct pointer
        i++;                                    // increment loop counter
    }

    i = 0;                                      // reset counter

    // display flights and their data
    printFlightInfo(flights);

    // free memory after its use
    for (i = 0; i < LOOP_AMT; ++i)
    {
        free(flights[i].flightDest);
        free(flights[i].flightDate);
        printf("Flight info deleted\n");
    }

    return 0;
}



/*
    Function:       clearCR()
    Parameters:     char* buf - C-Style string that will be modified
    Return Value:   NONE
    Description:    This function gets rid of the carriage return
                    of the given c-string in the parameter.
*/
void clearCR(char* buf)
{
	char* whereCR = strchr(buf, '\n');
	if (whereCR != NULL)
	{
		*whereCR = '\0';
	}
}



/*
    Function:       fillFlightInfo()
    Parameters:     FlightInfo* flight - pointer to FlightInfo node
    Return Value:   NONE
    Description:    This function allocates two blocks of memory to
				    contain the destination string and date string.
*/
void fillFlightInfo(FlightInfo* flight, char* destination, char* date)
{
    // block of memory = (typecast)malloc(length of string multiplied by size of data type + 1 for \0)
    flight->flightDest = (char*)malloc(strlen(destination) * sizeof(char) + 1);

    if (flight->flightDest == NULL)
    {
        printf("Out of memory.\n");
    }
    else
    {
        // put contents of string in struct variable field
        strcpy(flight->flightDest, destination);
    }

    flight->flightDate = (char*)malloc(strlen(date) * sizeof(char) + 1);

    if (flight->flightDate == NULL)
	{
		printf("Out of memory\n");
	}
	else
	{
		strcpy(flight->flightDate, date);
	}
}



/*
    Function:       printFlightInfo()
    Parameters:     FlightInfo* flights - array of FlightInfo 
    Return Value:   NONE
    Description:    This function displays data stored in the array of FlightInfo
*/
void printFlightInfo(struct FlightInfo flights[])
{
    for (int i = 0; i < LOOP_AMT; ++i)
    {
        // use '-' for left-justification
        printf("%-35s %-35s\n", flights[i].flightDest, flights[i].flightDate);
    }
}