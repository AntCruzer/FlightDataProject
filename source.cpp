// FUNCTION LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// CONSTANTS
#define BUF_SIZE    30
#define LOOP        1
#define EXIT        "."
#define FAILURE     -1.0


/*  STRUCT DATA TYPE    :       FlightInfo
    FIELDS              :       char* flightDest    - flight destination
                                char* flightDate    - flight date
                                double flightFare   - flight fare ($)
    DESCRIPTION         :       Data type stores flight information.     
 */
struct FlightInfo
{
	char* flightDest = NULL;
	char* flightDate = NULL;
    double flightFare;
};


/*  LINKED LIST DATA STRUCTURE NODE
    -------------------------------
    STRUCT DATA TYPE    :       FlightNode
    FIELDS              :       FlightInfo info     - FlightInfo data type
                                FlightInfo* next    - FlightInfo pointer to next node in linked list
                                FlightInfo* prev    - FlightInfo pointer to previous node in linked list
*/
struct FlightNode
{
    struct FlightInfo info;
	struct FlightNode* next;
    struct FlightNode* prev;
};


// FUNCTION PROTOTYPES
void clearCR(char* buf);                                                    
double getNum(void);                                                        
FlightNode* createFlightNode(char* destination, char* date, double fare);   
void printFlightInfo(FlightNode* head);                                      
void freeMemory(FlightNode* head);                                          
FlightNode* findFlight(FlightNode* head, char* destination, char* date);    
void deleteNode(FlightNode* node, FlightNode** head, FlightNode** tail);    
bool insertByFare(FlightNode* node, FlightNode** head, FlightNode** tail);  
bool insertByDest(FlightNode* node, FlightNode** head, FlightNode** tail);  


int main(void)
{
    /* PROMPT LOOP VARIABLES */

    // head pointers
    FlightNode* head = NULL;                            
    FlightNode* head2 = NULL;

    // tail pointers
    FlightNode* tail = NULL;
    FlightNode* tail2 = NULL;

    // new nodes
    FlightNode* newNode = NULL;                         
    FlightNode* newNode2 = NULL;                        

    
    char inputDest[BUF_SIZE];                           // string for destination
    char inputDate[BUF_SIZE];                           // string for date
    double fare = 0;                                    // double for cost of flight
    bool insertionStatus = false;                       // insertion status     
    bool insertionStatus2 = false;                      // insertion status  



    /* AFTER PROMPT LOOP VARIABLES */

    // nodes to move

    FlightNode* foundNode = NULL;                       // node being searched
    FlightNode* foundNode2 = NULL;                      

    FlightNode* changedNode = NULL;                     // node(s) with new fare
	FlightNode* changedNode2 = NULL;                    

    char searchDest[BUF_SIZE];                          // destination of flight searched
    char searchDate[BUF_SIZE];                          // date of flight searched

    bool insertNew = false;                             // insertion statuses for new nodes
    bool insertNew2 = false;
    double newFare = 0;                                 // updated fare

    // loop user prompt
    while (LOOP)
    {
        printf("Enter a flight destination: ");         // destination prompt
        fgets(inputDest, BUF_SIZE, stdin);              // obtain user input
        clearCR(inputDest);                             // clear carriage return

        // user wants to exit?
		if (strcmp(inputDest, EXIT) == 0)
		{
			break;	                                    // quit getting flight info
		}

        printf("Enter a flight date: ");                // date prompt
        fgets(inputDate, BUF_SIZE, stdin);              // obtain user input
        clearCR(inputDate);                             // clear carriage return

        // user wants to exit?
		if (strcmp(inputDate, EXIT) == 0)
		{
			break;	                                    // quit getting flight info
		}

        // fare prompt
        printf("Enter cost of fare: ");                 // fare prompt
        fare = getNum();                                // obtain value
        
        // verify fare
        if (fare == FAILURE)
        {
            break;
        }
        
        // allocate memory for new nodes
        newNode = createFlightNode(inputDest, inputDate, fare);
        newNode2 = createFlightNode(inputDest, inputDate, fare);

        // insert node by fare
        insertionStatus = insertByFare(newNode, &head, &tail);

        // insert node by destination
        insertionStatus2 = insertByDest(newNode2, &head2, &tail2);

        // if node creation fails
        if ( (insertionStatus == FAILURE) || (insertionStatus2 == FAILURE) )
        {
            printf("ERROR: INSERTION FAILED\n");
        }
    }

    // display flights in linked list
    printf("\n");
    printf("Flights arranged by fare\n");
    printf("--------------------------------------\n");
    printFlightInfo(head);
    
    printf("\n");

    printf("Flights arranged by destination\n");
    printf("--------------------------------------\n");
    printFlightInfo(head2);
    printf("\n");


    printf("Enter a flight destination you wish to change fare: ");     // prompt for destination
	fgets(searchDest, BUF_SIZE, stdin);                                 // obtain user input
	clearCR(searchDest);                                                // get rid of carriage return

    printf("Enter a flight date you wish to change fare: ");            // prompt for fare
	fgets(searchDate, BUF_SIZE, stdin);                                 // obtain user input
	clearCR(searchDate);                                                // get rid of carriage return

    // look for flight
    foundNode = findFlight(head, searchDest, searchDate);
    foundNode2 = findFlight(head2, searchDest, searchDate);

    if (foundNode != NULL)
    {
        // fare prompt
        printf("Enter a new fare: ");                 // new fare prompt
        newFare = getNum();                           // obtain value
        
        // fare unchanged
        if (foundNode->info.flightFare == newFare)
        {
            printf("Fare unchanged.\n");
        }
        else
        {
            // create node with new fare
            changedNode = createFlightNode(searchDest, searchDate, newFare);
            changedNode2 = createFlightNode(searchDest, searchDate, newFare);

            // delete node with outdated fare
            
            deleteNode(foundNode, &head, &tail);
            deleteNode(foundNode2, &head2, &tail2);

            // insert node with updated fare
            insertNew = insertByFare(changedNode, &head, &tail);
            insertNew2 = insertByDest(changedNode2, &head2, &tail2);

            // if node creation fails
            if ( (insertionStatus == FAILURE) || (insertionStatus2 == FAILURE) )
            {
                printf("ERROR: INSERTION FAILED\n");
            }
        }
    }
    else
    {
        printf("Flight not found\n");
    }

    // display flights in linked lists
    printf("\n");
    printf("Flights arranged by fare\n");
    printf("--------------------------------------\n");
    printFlightInfo(head);
    
    printf("\n");

    printf("Flights arranged by destination\n");
    printf("--------------------------------------\n");
    printFlightInfo(head2);
    printf("\n");

    // free allocated memory
    freeMemory(head);
    freeMemory(head2);
    printf("ALLOCATED MEMORY FREED\n");
    printf("END OF PROGRAM\n");
    return 0;
}



/*
    FUNCTION        :       clearCR()
    PARAMETERS      :       char* buf - C-Style string that will be modified
    RETURN VALUE    :       NONE
    DESCRIPTION     :       This function gets rid of the carriage return
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
*   FUNCTION        :       getNum()
*   PARAMETERS      :       void
*   RETURNS         :       double number
*   DESCRIPTION     :       This function gets a double value from the user. 
                            If the user enters a valid integer, the value is stored
                            in the return value. If the user-entered value is not valid,
                            -1 is returned.
*/
double getNum(void)
{
    char record[BUF_SIZE]; /* record stores the string */
    double number = 0;

    /* use fgets() to get a string from the keyboard */
    fgets(record, BUF_SIZE, stdin);

    /*  
        extract the number from the string; sscanf() returns a number
        corresponding with the number of items it found in the string   
    */
    if (sscanf(record, "%lf", &number) != 1)
    {
        /* if the user did not enter a number recognizable by
         * the system, set number to -1 */
        number = -1.0;
    }
    return number;
}



/*
    FUNCTION        :       createFlightInfo()
    PARAMETERS      :       char* destination   - string representing flight destination
                            char* date          - string representing flight date
                            double fare         - double represting flight fare
    RETURN VALUE    :       NONE
    DESCRIPTION     :       This function allocates two blocks of memory to
				            contain the destination string and date string.
*/
FlightNode* createFlightNode(char* destination, char* date, double fare)
{
    // initialize node to be inserted to linked list
    FlightNode* node = NULL;                

    // allocate memory for node
	node = (FlightNode*)malloc(sizeof(FlightNode));

    if (node == NULL)
	{
		printf("ERROR: OUT OF MEMORY\n");
		return NULL;
	}

    node->next = NULL;
    node->prev = NULL;

    // allocate memory for destination field
	node->info.flightDest = (char*)malloc(strlen(destination) * sizeof(char) + 1);

    if (node->info.flightDest == NULL)
	{
		printf("ERROR: OUT OF MEMORY\n");
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
		printf("ERROR: OUT OF MEMORY\n");
        return NULL;
	}
	else
	{
		strcpy(node->info.flightDate, date);
	}

    node->info.flightFare = fare;

    return node;
}



/*
    FUNCTION        :       printFlightInfo()
    PARAMETERS      :       FlightInfo* head - head of linked list of flights
    RETURN VALUE    :       NONE
    DESCRIPTION     :       This function displays data stored in the list of FlightNodes
*/
void printFlightInfo(FlightNode* head)
{
    FlightNode* ptr = head;

    while (ptr != NULL)
    {
        printf("%-35s %-35s %-35.2f\n", ptr->info.flightDest, ptr->info.flightDate, ptr->info.flightFare);
        ptr = ptr->next;
    }
}



/*
    FUNCTION        :       freeMemory()
    PARAMETERS      :       FlightInfo* head - head of linked list of flights
    RETURN VALUE    :       NONE
    DESCRIPTION     :       This function frees allocated memory during the program's runtime.
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
        // free(curr->info.flightFare);
		free(curr);
    }
}



/*
    FUNCTION        :       findFlight()
    PARAMETERS      :       FlightInfo* head    - pointer to head node in linked list
                            char* destination   - string holding destination
                            char* date          - string holding date
    RETURN VALUE    :       NONE
    DESCRIPTION     :       This function allocates two blocks of memory to
				            contain the destination string and date string.
*/
FlightNode* findFlight(FlightNode* head, char* destination, char* date)
{
    FlightNode* ptr = head;
	FlightNode* foundNode = NULL;

	while (ptr != NULL)
	{
		if ((strcmp(ptr->info.flightDest, destination) == 0) 
        && (strcmp(ptr->info.flightDate, date) == 0))
		{
			foundNode = ptr;
			break;
		}
		ptr = ptr->next;
	}
	return foundNode;
}



/*
    FUNCTION        :       deleteNode()
    PARAMETERS      :       FlightInfo* node    - pointer to node
                            FlightNode** head   - head of linked list
                            FligthNode** tail   - tail of linked list
    RETURN VALUE    :       NONE
    DESCRIPTION     :       This function deletes node in linked list
                            without orphaning other nodes' pointers.
*/
void deleteNode(FlightNode* node, FlightNode** head, FlightNode** tail) 
{
    if (!node) return;                      // Node is NULL, exit early

    // Adjust pointers
    if (node == *head) 
    {
        *head = node->next;
        if (*head) (*head)->prev = NULL;
    } 
    else 
    {
        node->prev->next = node->next;
    }
    if (node == *tail) 
    {
        *tail = node->prev;
        if (*tail) (*tail)->next = NULL;
    } 
    else 
    {
        node->next->prev = node->prev;
    }

    // Free node's memory
    free(node->info.flightDest);
    free(node->info.flightDate);
    free(node);
}



/*
    FUNCTION        :       insertByFare()
    PARAMETERS      :       FlightInfo* node    - pointer to node
                            FlightNode** head   - head of linked list
                            FligthNode** tail   - tail of linked list
    RETURN VALUE    :       bool - whether or not insertion was done successfully
    DESCRIPTION     :       This function inserts a new node in linked list
                            in order of flights' fare values.
*/
bool insertByFare(FlightNode* node, FlightNode** head, FlightNode** tail) {
    if (*head == NULL) 
    {  // Empty list
        *head = node;
        *tail = node;
        return true;
    }
    
    // Locate the insertion point
    FlightNode* current = *head;
    while (current != NULL && current->info.flightFare < node->info.flightFare) 
    {
        current = current->next;
    }
    
    if (current == NULL) 
    {  
        // Insert at end
        node->prev = *tail;
        (*tail)->next = node;
        *tail = node;
    } 
    else if (current == *head) 
    {  
        // Insert at beginning
        node->next = *head;
        (*head)->prev = node;
        *head = node;
    } 
    else 
    {  
        // Insert in the middle
        node->prev = current->prev;
        node->next = current;
        current->prev->next = node;
        current->prev = node;
    }
    
    return true;
}



/*
    FUNCTION        :       insertByDest()
    PARAMETERS      :       FlightInfo* node    - pointer to node
                            FlightNode** head   - head of linked list
                            FligthNode** tail   - tail of linked list
    RETURN VALUE    :       bool - whether or not insertion was done successfully
    DESCRIPTION     :       This function inserts a new node in linked list
                            in order of flights' destination.
*/
bool insertByDest(FlightNode* node, FlightNode** head, FlightNode** tail) {
    if (*head == NULL) 
    {  
        // Empty list
        *head = node;
        *tail = node;
        return true;
    }
    
    // Locate the insertion point
    FlightNode* current = *head;
    while (current != NULL && strcmp(current->info.flightDest, node->info.flightDest) < 0) 
    {
        current = current->next;
    }
    
    if (current == NULL) 
    {  
        // Insert at end
        node->prev = *tail;
        (*tail)->next = node;
        *tail = node;
    } 
    else if (current == *head) 
    {  
        // Insert at beginning
        node->next = *head;
        (*head)->prev = node;
        *head = node;
    } 
    else 
    {  
        // Insert in the middle
        node->prev = current->prev;
        node->next = current;
        current->prev->next = node;
        current->prev = node;
    }
    
    return true;
}


