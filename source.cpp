// FUNCTION LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// CONSTANTS (OK)
#define BUF_SIZE    30
#define PROMPT      1
#define EXIT        "."



/*  STRUCT DATA TYPE    :       FlightInfo
    FIELDS              :       char* flightDest    - flight destination
                                char* flightDate    - flight date
    DESCRIPTION         :       Data type stores flight information.     
 */
struct FlightInfo
{
	char* flightDest = NULL;
	char* flightDate = NULL;
};



/*  LINKED LIST DATA STRUCTURE NODE
    -------------------------------
    STRUCT DATA TYPE    :       FlightNode
    FIELDS              :       FlightInfo info     - FlightInfo data type
                                FlightInfo* next    - FlightInfo pointer to next node in linked list
*/
struct FlightNode
{
    struct FlightInfo info;
	struct FlightNode* next;
};



// FUNCTION PROTOTYPES
void clearCR(char* buf);                                                    
FlightNode* createFlightNode(char* destination, char* date);                
void printFlightInfo(FlightNode* head);                                     
void freeMemory(FlightNode* head);                                          



int main(void)
{
    // identify variables
    FlightNode* head = NULL;                            // head pointer
    FlightNode* ptr = NULL;                             // traversing node pointer
    FlightNode* newNode = NULL;                         // pointer to new node
    char inputDest[BUF_SIZE];                           // string for destination
    char inputDate[BUF_SIZE];                           // string for date

    while (PROMPT)
    {
        printf("Enter a flight destination: ");         // destination prompt
        fgets(inputDest, BUF_SIZE, stdin);              // obtain user input
        clearCR(inputDest);                             // clear carriage return

        // user wants to exit?
		if (strcmp(inputDest, EXIT) == 0)
		{
			break;	                                    // quit getting flight info
		}

        // date prompt
        printf("Enter a flight date: ");                // date prompt
        fgets(inputDate, BUF_SIZE, stdin);              // obtain user input
        clearCR(inputDate);                             // clear carriage return

        // user wants to exit?
		if (strcmp(inputDate, EXIT) == 0)
		{
			break;	                                    // quit getting flight info
		}

        // allocate memory for new node
        newNode = createFlightNode(inputDest, inputDate);

        // memory allocation failed?
        if (newNode == NULL)
        {
            break;
        }

        // empty linked list?
        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            ptr = head;
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }

            // insert node to the end of the LL
			ptr->next = newNode;
        }
    }

    // display flights in linked list
    printFlightInfo(head);

    // free allocated memory
    freeMemory(head);

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
FlightNode* createFlightNode(char* destination, char* date)
{
    // initialize node to be inserted to linked list
    FlightNode* node = NULL;                

    // allocate memory for node
	node = (FlightNode*)malloc(sizeof(FlightNode));

    if (node == NULL)
	{
		printf("Out of memory\n");
		return NULL;
	}

    node->next = NULL;

    // allocate memory for destination field
	node->info.flightDest = (char*)malloc(strlen(destination) * sizeof(char) + 1);

    if (node->info.flightDest == NULL)
	{
		printf("Out of memory\n");
        return NULL;
	}
	else
	{
		strcpy(node->info.flightDest, destination);
	}

    // allocate memory for the date field
	node->info.flightDate = (char*)malloc(strlen(date) * sizeof(char) + 1);

	if (node->info.flightDate == NULL)
	{
		printf("Out of memory\n");
        return NULL;
	}
	else
	{
		strcpy(node->info.flightDate, date);
	}

    return node;
}



/*
    Function:       printFlightInfo()
    Parameters:     FlightInfo* head - head of linked list of flights
    Return Value:   NONE
    Description:    This function displays data stored in the list of FlightNodes
*/
void printFlightInfo(FlightNode* head)
{
    FlightNode* ptr = head;

    while (ptr != NULL)
    {
        printf("%-35s %-35s\n", ptr->info.flightDest, ptr->info.flightDate);
        ptr = ptr->next;
    }
}



/*
    Function:       freeMemory()
    Parameters:     FlightInfo* head - head of linked list of flights
    Return Value:   NONE
    Description:    This function displays data stored in the list of FlightNodes
*/
void freeMemory(FlightNode* head)
{
    FlightNode* curr = NULL;
    FlightNode* ptr = head;

    while (ptr != NULL)
    {
        // first, save the current cell
		curr = ptr;
		// next, move to the next cell
		ptr = ptr->next;
		// can't free curr before getting the next pointer
		free(curr->info.flightDest);		// free up space in that field
		free(curr->info.flightDate);
		free(curr);
    }
}


