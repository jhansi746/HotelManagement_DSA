#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 10

struct Room {
    int roomNumber;
    int isAvailable;
    char guestName[50];
};

struct Hotel {
    struct Room rooms[MAX_ROOMS];
};

void initializeRooms(struct Hotel *hotel) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        hotel->rooms[i].roomNumber = i + 1;
        hotel->rooms[i].isAvailable = 1;
        strcpy(hotel->rooms[i].guestName, "None");
    }
}

void checkIn(struct Hotel *hotel) {
    int roomNumber;
    char guestName[50];

    printf("Enter room number to check-in: ");
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number!\n");
        return;
    }

    struct Room *room = &hotel->rooms[roomNumber - 1];
    if (!room->isAvailable) {
        printf("Sorry, room %d is already occupied.\n", roomNumber);
        return;
    }

    printf("Enter guest name: ");
    getchar();
    fgets(guestName, sizeof(guestName), stdin);
    guestName[strcspn(guestName, "\n")] = 0;

    room->isAvailable = 0;
    strcpy(room->guestName, guestName);
    printf("Checked in successfully! Room %d is now occupied by %s.\n", roomNumber, guestName);
}

void checkOut(struct Hotel *hotel) {
    int roomNumber;

    printf("Enter room number to check-out: ");
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number!\n");
        return;
    }

    struct Room *room = &hotel->rooms[roomNumber - 1];
    if (room->isAvailable) {
        printf("Room %d is already vacant.\n", roomNumber);
        return;
    }

    room->isAvailable = 1;
    strcpy(room->guestName, "None");
    printf("Checked out successfully! Room %d is now vacant.\n", roomNumber);
}

void displayRooms(struct Hotel *hotel) {
    printf("\nRoom Status:\n");
    printf("Room No. | Status   | Guest Name\n");
    printf("--------------------------------\n");

    for (int i = 0; i < MAX_ROOMS; i++) {
        struct Room *room = &hotel->rooms[i];
        printf("%8d | %-8s | %s\n", room->roomNumber, 
               room->isAvailable ? "Available" : "Occupied", 
               room->guestName);
    }
}

int main() {
    struct Hotel hotel;
    int choice;

    initializeRooms(&hotel);

    do {
        printf("\nHotel Management System\n");
        printf("1. Check-in\n");
        printf("2. Check-out\n");
        printf("3. Display room status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkIn(&hotel);
                break;
            case 2:
                checkOut(&hotel);
                break;
            case 3:
                displayRooms(&hotel);
                break;
            case 4:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
