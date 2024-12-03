#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUSES 20 // Increase the maximum number of buses
#define MAX_BUS_SEATS 8
#define MAX_ROWS 4
#define MAX_COLUMNS 10

static int p = 0; 
// Counter to keep track of the number of buses

// Structure to represent a bus
struct Bus 
{
    
    char busn[10]; 
    // Increased the size of bus number
    
    char driver[20]; 
    // Increased the size of driver's name
    
    char arrival[15]; 
    // Increased the size of arrival time
    
    char depart[15]; 
    // Increased the size of departure time
    
    char from[20]; 
    // Increased the size of departure location
    
    char to[20];
    // Increased the size of destination location
    
    char type[20]; 
    // Added bus type
    
    char paymentMode[20]; 
    // Added payment mode
    
    char feedback[100]; 
    // Added feedback field
    
    char coordinatorName[20]; 
    // Added bus coordinator name
    
    char coordinatorContact[15]; 
    // Added bus coordinator contact
    
    char facilities[100]; 
    // Added facilities available in the bus
    
    char seat[MAX_ROWS][MAX_COLUMNS][15]; 
    // 3D array to represent bus seats
    
    char passengerGender[MAX_ROWS][MAX_COLUMNS]; 
    // 2D array to represent passenger gender
    
    int passengerAge[MAX_ROWS][MAX_COLUMNS]; 
    // 2D array to represent passenger age
};

// Array of Bus structures to store bus information
struct Bus bus[MAX_BUSES];

// Function to print a horizontal line of characters
void vline(char ch, int length) 
{
    
    for (int i = length; i > 0; i--)
        printf("%c", ch);
}

// Function to install a new bus
void install(struct Bus *b) 
{
    
    printf("\n Enter bus no: ");
    scanf("%s", b->busn);
    
    printf("\n Enter Driver's name: ");
    scanf("%s", b->driver);
    
    printf("\n Arrival time: ");
    scanf("%s", b->arrival);
    
    printf("\n Departure: ");
    scanf("%s", b->depart);
    
    printf("\n From: ");
    scanf("%s", b->from);
    
    printf("\n To: ");
    scanf("%s", b->to);
    
    printf("\n Enter Bus Type: ");
    scanf("%s", b->type);
    
    printf("\n Enter Payment Mode: ");
    scanf("%s", b->paymentMode);  

    // Initialize all seats as "Empty"
    for (int i = 0; i < MAX_ROWS; i++) 
    {
        
        for (int j = 0; j < MAX_COLUMNS; j++) 
        {
            
            strcpy(b->seat[i][j], "Empty");
        }
    }

    p++; // Increment the bus counter
    
    // Collect coordinator details and facilities
    printf("\n Enter Bus Coordinator Name: ");
    scanf("%s", b->coordinatorName);
    
    printf("\n Enter Bus Coordinator Contact: ");
    scanf("%s", b->coordinatorContact);
    
    printf("\n Enter Facilities Available in the Bus: ");
    scanf(" %[^\n]s", b->facilities);
    
    // Collect feedback
    printf("\n Provide feedback for the bus: ");
    scanf(" %[^\n]s", b->feedback);
    
    printf("\n BUS ADDED SUCCESSFULLY\n");
    
     // Initialize passenger details
    for (int i = 0; i < MAX_ROWS; i++) 
    {
        
        for (int j = 0; j < MAX_COLUMNS; j++) 
        {
            
            b->passengerGender[i][j] = '\0'; 
            // Initialize gender as empty
            b->passengerAge[i][j] = 0; 
            // Initialize age as 0
        }
    }
}

// Function to display and handle feedback
void displayFeedback(struct Bus *b)
{

    int n;
    char number[10];
    printf(" Enter bus no: ");
    scanf("%s", number);

    for (n = 0; n < p; n++) {
        if (strcmp(b[n].busn, number) == 0) 
        {
        
            printf("\n Feedback for Bus No %s:\n", b[n].busn);
            printf(" %s\n", b[n].feedback);
            return;
        }
    }

    printf(" Bus not found. Enter correct bus no: ");
}

// Function to reserve a seat in a bus
void allotment() 
{
   
    int seat;
    char number[10];
top:
    printf("\n Bus no: ");
    scanf("%s", number);

    int n;
    for (n = 0; n <= p; n++) 
    {
        
        if (strcmp(bus[n].busn, number) == 0)
            break;
    }

    while (n <= p) 
    {
        
        printf("\n Seat Number: ");
        scanf("%d", &seat);
        
        getchar();

        if (seat > (MAX_ROWS * MAX_COLUMNS)) 
        {
            
            printf("\n There are only %d seats available in this bus\n", MAX_ROWS * MAX_COLUMNS);
        } 
        else 
        {
            
            // Check if the seat is empty
           if (strcmp(bus[n].seat[(seat - 1) / MAX_COLUMNS][(seat - 1) % MAX_COLUMNS], "Empty") == 0)
            {
                
                printf(" \nEnter passenger's name: ");
                scanf("%s", bus[n].seat[seat / MAX_COLUMNS][(seat % MAX_COLUMNS) - 1]);
                
                char gender;
                int age;

                printf(" \nEnter passenger's gender (M/F): ");
                scanf(" %c", &gender);

                printf(" \nEnter passenger's age: ");
                scanf("%d", &age);
                
                printf(" \n\nSeat Reserved Successfully\n");
                break;
            } 
            
            else 
            {
                
                printf(" The seat no. is already reserved.\n");
            }
        }
    }

    if (n > p) 
    {
    
        printf(" Enter correct bus no.\n");
        goto top;
    }
    
     // Get passenger details
    char gender;
    int age;

    // Store passenger details in the seat
    bus[n].passengerGender[seat / MAX_COLUMNS][(seat % MAX_COLUMNS) - 1] = gender;
    bus[n].passengerAge[seat / MAX_COLUMNS][(seat % MAX_COLUMNS) - 1] = age;
}

// Function to set all seats in a bus as "Empty"
void empty(struct Bus *b) 
{
    
    for (int i = 0; i < MAX_ROWS; i++) 
    {
    
        for (int j = 0; j < MAX_COLUMNS; j++) 
        {
    
            strcpy(b->seat[i][j], "Empty");
        }
    }
}

// Function to display information about a specific bus
void show(struct Bus *b) 
{
    int n;
    char number[10];
    printf(" Enter bus no: ");
    scanf("%s", number);

    for (n = 0; n <= p; n++)
    {
        if (strcmp(b[n].busn, number) == 0) 
        {
            break;
        }
    }

    if (n <= p) 
    {
        vline('*', 80);
        printf("\nBus no:  %s\n", bus[n].busn);
        printf("Driver: %s\n", bus[n].driver);
        printf("Arrival time: %s\n", bus[n].arrival);
        printf("Departure Time: %s\n", bus[n].depart);
        printf("From: %s\n", bus[n].from);
        printf("To: %s\n", bus[n].to);
        vline('*', 80);
        position(b, n);

        int a = 1;
        for (int i = 0; i < MAX_ROWS; i++) 
        {
            for (int j = 0; j < MAX_COLUMNS; j++) 
            {
                a++;
                if (strcmp(b->seat[i][j], "Empty") != 0)
                    printf("\n The seat no %d is reserved for %s.", (a - 1), b->seat[i][j]);
            }
        }
    } 
    else 
    {
        printf(" Bus not found. Enter correct bus no: ");
    }
}


// Function to display the available seats in a bus
void position(struct Bus *b, int l) 
{
    
    int s = 0;
    p = 0;
    for (int i = 0; i < MAX_ROWS; i++) 
    {
        
        printf("\n");
        for (int j = 0; j < MAX_COLUMNS; j++) 
        {
            
            s++;
            if (strcmp(b->seat[i][j], "Empty") == 0) 
            {
                
                printf("%5d.%10s", s, b->seat[i][j]);
                p++;
            } 
            else 
            {
                
                printf("%5d.%10s", s, b->seat[i][j]);
            }
        }
    }
    printf("\n There are %d seats empty in Bus No: %s", p, b->busn);
}

// Function to display information about all available buses
void avail() 
{
   
    for (int n = 0; n < p; n++) 
    {
   
        vline('*', 80);
        printf("\nBus no:  %s\n", bus[n].busn);
    
        printf("Driver: %s\n", bus[n].driver);
    
        printf("Arrival time: %s\n", bus[n].arrival);
    
        printf("Departure Time: %s\n", bus[n].depart);
    
        printf("From: %s\n", bus[n].from);
    
        printf("To: %s\n", bus[n].to);
    
        vline('*', 80);
        vline('_', 80);
    }
}

// Function to display the main menu
void displayMenu() 
{
   
    printf("\n\n");
    
    printf(" **********************************************\n\n");

    printf(" BUS RESERVATION SYSTEM PROJECT IN C\n\n");

    printf(" [1].Add Bus\n");

    printf(" [2].Bus reservation\n");

    printf(" [3].Show\n");

    printf(" [4].Buses available\n");
    
    printf (" [5].Cancel Reservation\n");
    
    printf (" [6].Display Statistics\n");
    
    printf(" [7].Search by Driver Name\n");
    
    printf(" [8].Search by Bus Type\n");
    
    printf(" [9].Search by Payment Mode\n");
    
    printf(" [10].Provide Feedback\n");
    
    printf (" [11].Print Ticket\n");
    
    printf(" [12].Exit\n");

    printf(" **********************************************\n\n");

    printf("\n Enter your choice:-> ");

}


// Function to cancel a seat reservation
void cancelReservation() 
{
    
    char number[10];
    int seat;

    printf("\n Enter bus no: ");
    scanf("%s", number);

    int n;
    for (n = 0; n <= p; n++) 
    {
        
        if (strcmp(bus[n].busn, number) == 0)
            break;
    }

    while (n <= p) 
    {
        
        printf("\n Enter seat number to cancel reservation: ");
        scanf("%d", &seat);

        if (seat > (MAX_ROWS * MAX_COLUMNS) || seat < 1) 
        {
            
            printf("\n Invalid seat number\n");
        } 
        else if (strcmp(bus[n].seat[seat / MAX_COLUMNS][(seat % MAX_COLUMNS) - 1], "Empty") == 0) 
        {
            
            printf(" The seat no. is not reserved.\n");
        } 
        else 
        {
            
            printf(" Reservation for seat %d canceled successfully.\n", seat);
            strcpy(bus[n].seat[seat / MAX_COLUMNS][(seat % MAX_COLUMNS) - 1], "Empty");
            break;
        }
    }

    if (n > p) 
    {
       
        printf(" Enter correct bus no.\n");
    }
}


// Function to search for a bus by the driver's name
void searchByDriverName() 
{
    
    char driverName[20];
    printf("\n Enter driver's name: ");
    scanf("%s", driverName);

    printf("\n Buses with driver %s:\n", driverName);
    for (int i = 0; i < p; i++) 
    {
        
        if (strcmp(bus[i].driver, driverName) == 0) 
        {
            
            printf(" - Bus no: %s\n", bus[i].busn);
        }
    }
}


// Function to display statistics
void displayStatistics() 
{
    
    int totalBuses = p;
    int totalSeats = MAX_ROWS * MAX_COLUMNS;
    int reservedSeats = 0;

    for (int i = 0; i < p; i++) 
    {
        
        for (int j = 0; j < MAX_ROWS; j++) 
        {
            
            for (int k = 0; k < MAX_COLUMNS; k++) 
            {
                
                if (strcmp(bus[i].seat[j][k], "Empty") != 0) 
                {
                    
                    reservedSeats++;
                }
            }
        }
    }

    printf("\n ***** BUS RESERVATION SYSTEM STATISTICS *****\n");
    
    printf("\n Total Buses: %d\n", totalBuses);
    
    printf(" Total Seats per Bus: %d\n", totalSeats);
    
    printf(" Reserved Seats: %d\n", reservedSeats);
    
    printf(" Available Seats: %d\n", totalBuses * totalSeats - reservedSeats);
    
    printf(" *********************************************\n");
}


// Function to search for a bus by the bus type
void searchByBusType() 
{
    
    char busType[20];
    printf("\n Enter bus type: ");
    scanf("%s", busType);

    printf("\n Buses of type %s:\n", busType);
    for (int i = 0; i < p; i++) 
    {
        
        if (strcmp(bus[i].type, busType) == 0) 
        {
            
            printf(" - Bus no: %s\n", bus[i].busn);
        }
    }
}


// Function to search for a bus by payment mode
void searchByPaymentMode() 
{
    
    char paymentMode[20];
    printf("\n Enter payment mode: ");
    scanf("%s", paymentMode);

    printf("\n Buses with payment mode %s:\n", paymentMode);
    for (int i = 0; i < p; i++) 
    {
        
        if (strcmp(bus[i].paymentMode, paymentMode) == 0) 
        {
            
            printf(" - Bus no: %s\n", bus[i].busn);
        }
    }
}


// Function to print the bus ticket
void printTicket(struct Bus *b) 
{
    printf("\n ***** BUS TICKET *****\n");
    printf(" Bus No: %s\n", b->busn);
    printf(" Driver: %s\n", b->driver);
    printf(" Arrival Time: %s\n", b->arrival);
    printf(" Departure Time: %s\n", b->depart);
    printf(" From: %s\n", b->from);
    printf(" To: %s\n", b->to);
    printf(" Bus Type: %s\n", b->type);
    printf(" Payment Mode: %s\n", b->paymentMode);
    printf(" Coordinator Name: %s\n", b->coordinatorName);
    printf(" Coordinator Contact: %s\n", b->coordinatorContact);
    printf(" Facilities: %s\n", b->facilities);
    
    printf("\n ***** PASSENGER DETAILS *****\n");

    for (int i = 0; i < MAX_ROWS; i++) 
    {
        for (int j = 0; j < MAX_COLUMNS; j++) 
        {
            if (strcmp(b->seat[i][j], "Empty") != 0) 
            {
                printf(" Seat No %d: Reserved for %s\n", (i * MAX_COLUMNS + j + 1), b->seat[i][j]);
                // Print passenger details like gender and age here
            }
        }
    }
    printf(" *************************\n");
}




// Main function
int main() 
{
    
    int choice;
    while (1) 
    {
        
        displayMenu();
        scanf("%d", &choice);

        switch (choice) 
        {
            
            case 1: install(&bus[p]);
            // Add a new bus
                break;
            
            case 2: allotment(); 
            // Reserve a seat in a bus
                break;
            
            case 3: show(&bus[0]); 
            // Show information about a specific bus
                break;
            
            case 4: avail(); 
            // Display information about all available buses
                break;
            
            case 5: cancelReservation(); 
            // Cancel a seat reservation
                break;
            
            case 6: displayStatistics();
            // Display system statistics
                break;
            
            case 7: searchByDriverName(); 
            // Search for a bus by driver's name
                break;
            
            case 8: searchByBusType(); 
            // Search for a bus by bus type
                break;
            
            case 9: searchByPaymentMode(); 
            // Search for a bus by payment mode
                break;
            
            case 10: displayFeedback(&bus[0]); 
            // Provide feedback for a bus
                break;
            
           case 11: 
                // Print the bus ticket for the last added bus
                if (p > 0) 
                {
                    printTicket(&bus[p - 1]);
                }
                else 
                {
                    printf("No buses added yet.\n");
                }
                // Don't exit here if you want to continue
                break;

            case 12:
                // Exit the program
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("\t\t\tInvalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
