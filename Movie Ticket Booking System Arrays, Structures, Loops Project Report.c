#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MOVIES 5
#define MAX_ROWS 10
#define MAX_COLS 10
#define MAX_BOOKINGS 100

// Structure to store movie information
struct Movie {
    int id;
    char name[50];
    char genre[30];
    float price;
    int totalSeats;
    int availableSeats;
    int seats[MAX_ROWS][MAX_COLS];
};

// Structure to store booking information
struct Booking {
    int bookingId;
    int movieId;
    char customerName[50];
    char phoneNumber[15];
    int seatRow;
    int seatCol;
    float amount;
    int isActive;
};

// Global variables
struct Movie movies[MAX_MOVIES];
struct Booking bookings[MAX_BOOKINGS];
int movieCount = 0;
int bookingCount = 0;
int bookingIdCounter = 1001;

// Function declarations
void initializeMovies();
void displayMainMenu();
void viewMovies();
void bookTicket();
void viewBookings();
void cancelBooking();
void displaySeats(int movieIndex);
int findAvailableBookingSlot();
void clearScreen();
void pauseScreen();

int main() {
    int choice;
    
    initializeMovies();
    
    printf("\n=================================================\n");
    printf("   WELCOME TO MOVIE TICKET BOOKING SYSTEM\n");
    printf("=================================================\n");
    pauseScreen();
    
    while(1) {
        clearScreen();
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                clearScreen();
                viewMovies();
                pauseScreen();
                break;
            case 2:
                clearScreen();
                bookTicket();
                pauseScreen();
                break;
            case 3:
                clearScreen();
                viewBookings();
                pauseScreen();
                break;
            case 4:
                clearScreen();
                cancelBooking();
                pauseScreen();
                break;
            case 5:
                printf("\n=================================================\n");
                printf("   Thank you for using our booking system!\n");
                printf("=================================================\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
                pauseScreen();
        }
    }
    
    return 0;
}

void initializeMovies() {
    // Movie 1
    movies[0].id = 1;
    strcpy(movies[0].name, "Avatar 3");
    strcpy(movies[0].genre, "Sci-Fi/Action");
    movies[0].price = 250.0;
    movies[0].totalSeats = 100;
    movies[0].availableSeats = 100;
    
    // Movie 2
    movies[1].id = 2;
    strcpy(movies[1].name, "Inception Returns");
    strcpy(movies[1].genre, "Thriller");
    movies[1].price = 200.0;
    movies[1].totalSeats = 100;
    movies[1].availableSeats = 100;
    
    // Movie 3
    movies[2].id = 3;
    strcpy(movies[2].name, "The Comedy Club");
    strcpy(movies[2].genre, "Comedy");
    movies[2].price = 180.0;
    movies[2].totalSeats = 100;
    movies[2].availableSeats = 100;
    
    // Movie 4
    movies[3].id = 4;
    strcpy(movies[3].name, "Horror Nights");
    strcpy(movies[3].genre, "Horror");
    movies[3].price = 220.0;
    movies[3].totalSeats = 100;
    movies[3].availableSeats = 100;
    
    // Movie 5
    movies[4].id = 5;
    strcpy(movies[4].name, "Romance Forever");
    strcpy(movies[4].genre, "Romance");
    movies[4].price = 190.0;
    movies[4].totalSeats = 100;
    movies[4].availableSeats = 100;
    
    movieCount = 5;
    
    // Initialize all seats as available (0 = available, 1 = booked)
    for(int i = 0; i < movieCount; i++) {
        for(int j = 0; j < MAX_ROWS; j++) {
            for(int k = 0; k < MAX_COLS; k++) {
                movies[i].seats[j][k] = 0;
            }
        }
    }
    
    // Initialize bookings
    for(int i = 0; i < MAX_BOOKINGS; i++) {
        bookings[i].isActive = 0;
    }
}

void displayMainMenu() {
    printf("\n=================================================\n");
    printf("         MOVIE TICKET BOOKING SYSTEM\n");
    printf("=================================================\n");
    printf("  1. View Available Movies\n");
    printf("  2. Book Ticket\n");
    printf("  3. View My Bookings\n");
    printf("  4. Cancel Booking\n");
    printf("  5. Exit\n");
    printf("=================================================\n");
}

void viewMovies() {
    printf("\n=================================================\n");
    printf("            AVAILABLE MOVIES\n");
    printf("=================================================\n");
    printf("%-5s %-25s %-15s %-10s %-10s\n", "ID", "Movie Name", "Genre", "Price(Rs)", "Available");
    printf("-------------------------------------------------\n");
    
    for(int i = 0; i < movieCount; i++) {
        printf("%-5d %-25s %-15s %-10.2f %-10d\n", 
               movies[i].id, 
               movies[i].name, 
               movies[i].genre, 
               movies[i].price,
               movies[i].availableSeats);
    }
    printf("=================================================\n");
}

void displaySeats(int movieIndex) {
    printf("\n=================================================\n");
    printf("         SEAT LAYOUT FOR: %s\n", movies[movieIndex].name);
    printf("=================================================\n");
    printf("              SCREEN THIS WAY\n");
    printf("=================================================\n");
    
    printf("    ");
    for(int j = 0; j < MAX_COLS; j++) {
        printf("%2d ", j + 1);
    }
    printf("\n");
    
    for(int i = 0; i < MAX_ROWS; i++) {
        printf("%c   ", 'A' + i);
        for(int j = 0; j < MAX_COLS; j++) {
            if(movies[movieIndex].seats[i][j] == 0) {
                printf("[O]");
            } else {
                printf("[X]");
            }
        }
        printf("\n");
    }
    
    printf("\n[O] = Available    [X] = Booked\n");
    printf("=================================================\n");
}

void bookTicket() {
    int movieChoice, numSeats;
    char seatRow;
    int seatCol;
    char customerName[50];
    char phoneNumber[15];
    
    viewMovies();
    
    printf("\nEnter Movie ID to book: ");
    scanf("%d", &movieChoice);
    
    if(movieChoice < 1 || movieChoice > movieCount) {
        printf("\nInvalid Movie ID!\n");
        return;
    }
    
    int movieIndex = movieChoice - 1;
    
    if(movies[movieIndex].availableSeats == 0) {
        printf("\nSorry! All seats are booked for this movie.\n");
        return;
    }
    
    displaySeats(movieIndex);
    
    printf("\nEnter your name: ");
    scanf(" %[^\n]s", customerName);
    
    printf("Enter your phone number: ");
    scanf("%s", phoneNumber);
    
    printf("Enter number of seats to book: ");
    scanf("%d", &numSeats);
    
    if(numSeats > movies[movieIndex].availableSeats) {
        printf("\nOnly %d seats available!\n", movies[movieIndex].availableSeats);
        return;
    }
    
    float totalAmount = 0;
    int bookedSeats = 0;
    
    printf("\nEnter seat positions (e.g., A5 for Row A, Column 5):\n");
    
    for(int i = 0; i < numSeats; i++) {
        printf("Seat %d: ", i + 1);
        scanf(" %c%d", &seatRow, &seatCol);
        
        seatRow = seatRow >= 'a' ? seatRow - 'a' : seatRow - 'A';
        seatCol = seatCol - 1;
        
        if(seatRow < 0 || seatRow >= MAX_ROWS || seatCol < 0 || seatCol >= MAX_COLS) {
            printf("Invalid seat position!\n");
            i--;
            continue;
        }
        
        if(movies[movieIndex].seats[(int)seatRow][seatCol] == 1) {
            printf("Seat already booked! Choose another seat.\n");
            i--;
            continue;
        }
        
        // Book the seat
        movies[movieIndex].seats[(int)seatRow][seatCol] = 1;
        movies[movieIndex].availableSeats--;
        
        // Create booking record
        int bookingSlot = findAvailableBookingSlot();
        bookings[bookingSlot].bookingId = bookingIdCounter++;
        bookings[bookingSlot].movieId = movies[movieIndex].id;
        strcpy(bookings[bookingSlot].customerName, customerName);
        strcpy(bookings[bookingSlot].phoneNumber, phoneNumber);
        bookings[bookingSlot].seatRow = (int)seatRow;
        bookings[bookingSlot].seatCol = seatCol;
        bookings[bookingSlot].amount = movies[movieIndex].price;
        bookings[bookingSlot].isActive = 1;
        
        totalAmount += movies[movieIndex].price;
        bookedSeats++;
    }
    
    printf("\n=================================================\n");
    printf("         BOOKING CONFIRMATION\n");
    printf("=================================================\n");
    printf("Customer Name: %s\n", customerName);
    printf("Phone: %s\n", phoneNumber);
    printf("Movie: %s\n", movies[movieIndex].name);
    printf("Seats Booked: %d\n", bookedSeats);
    printf("Total Amount: Rs. %.2f\n", totalAmount);
    printf("=================================================\n");
    printf("    Booking Successful! Enjoy the movie!\n");
    printf("=================================================\n");
}

void viewBookings() {
    char phoneNumber[15];
    int found = 0;
    
    printf("\n=================================================\n");
    printf("            VIEW BOOKINGS\n");
    printf("=================================================\n");
    printf("Enter your phone number: ");
    scanf("%s", phoneNumber);
    
    printf("\n%-10s %-25s %-10s %-10s\n", "BookingID", "Movie", "Seat", "Amount");
    printf("-------------------------------------------------\n");
    
    for(int i = 0; i < MAX_BOOKINGS; i++) {
        if(bookings[i].isActive && strcmp(bookings[i].phoneNumber, phoneNumber) == 0) {
            int movieIndex = bookings[i].movieId - 1;
            printf("%-10d %-25s %c%-9d Rs. %.2f\n", 
                   bookings[i].bookingId,
                   movies[movieIndex].name,
                   'A' + bookings[i].seatRow,
                   bookings[i].seatCol + 1,
                   bookings[i].amount);
            found = 1;
        }
    }
    
    if(!found) {
        printf("No bookings found for this phone number.\n");
    }
    printf("=================================================\n");
}

void cancelBooking() {
    int bookingId;
    int found = 0;
    
    printf("\n=================================================\n");
    printf("            CANCEL BOOKING\n");
    printf("=================================================\n");
    printf("Enter Booking ID: ");
    scanf("%d", &bookingId);
    
    for(int i = 0; i < MAX_BOOKINGS; i++) {
        if(bookings[i].isActive && bookings[i].bookingId == bookingId) {
            int movieIndex = bookings[i].movieId - 1;
            
            // Free the seat
            movies[movieIndex].seats[bookings[i].seatRow][bookings[i].seatCol] = 0;
            movies[movieIndex].availableSeats++;
            
            // Mark booking as inactive
            bookings[i].isActive = 0;
            
            printf("\nBooking ID %d cancelled successfully!\n", bookingId);
            printf("Refund Amount: Rs. %.2f\n", bookings[i].amount);
            printf("=================================================\n");
            found = 1;
            break;
        }
    }
    
    if(!found) {
        printf("\nBooking ID not found or already cancelled!\n");
        printf("=================================================\n");
    }
}

int findAvailableBookingSlot() {
    for(int i = 0; i < MAX_BOOKINGS; i++) {
        if(bookings[i].isActive == 0) {
            return i;
        }
    }
    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}