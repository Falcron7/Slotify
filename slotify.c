#include <stdio.h>
#include <string.h>

#define MAX 20

struct Vehicle
{
    char number[20];
    int entryTime;
    int occupied;
};

void parkVehicle(struct Vehicle p[]);
void exitVehicle(struct Vehicle p[]);
void searchVehicle(struct Vehicle p[]);
void showStatus(struct Vehicle p[]);
void dashboard(struct Vehicle p[]);

int main()
{
    struct Vehicle parking[MAX];
    int choice, i;

    for(i = 0; i < MAX; i++)
    {
        parking[i].occupied = 0;
    }

    while(1)
    {
        printf("\n=====================================\n");
        printf("      SMART CAMPUS PARKING\n");
        printf("=====================================\n");

        printf("1. Park Vehicle\n");
        printf("2. Vehicle Exit\n");
        printf("3. Search Vehicle\n");
        printf("4. Parking Status\n");
        printf("5. Dashboard\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if(choice == 1)
            parkVehicle(parking);
        else if(choice == 2)
            exitVehicle(parking);
        else if(choice == 3)
            searchVehicle(parking);
        else if(choice == 4)
            showStatus(parking);
        else if(choice == 5)
            dashboard(parking);
        else if(choice == 6)
            break;
        else
            printf("Invalid choice.\n");
    }

    return 0;
}

void parkVehicle(struct Vehicle p[])
{
    char number[20];
    int i, entry;

    printf("\n--- Vehicle Entry ---\n");
    printf("Enter vehicle number: ");
    scanf("%19s", number);

    /* Check duplicate vehicle */
    for(i = 0; i < MAX; i++)
    {
        if(p[i].occupied == 1 &&
           strcmp(p[i].number, number) == 0)
        {
            printf("Vehicle is already parked.\n");
            return;
        }
    }

    /* Find empty slot */
    for(i = 0; i < MAX; i++)
    {
        if(p[i].occupied == 0)
        {
            printf("Enter entry hour (0-23): ");
            scanf("%d", &entry);

            strcpy(p[i].number, number);
            p[i].entryTime = entry;
            p[i].occupied = 1;

            printf("\nVehicle parked successfully!\n");
            printf("Parking Slot: %d\n", i + 1);
            printf("Entry Time: %02d:00\n", entry);
            return;
        }
    }

    printf("Parking is full.\n");
}

void exitVehicle(struct Vehicle p[])
{
    char number[20];
    int i, exitTime, duration, fee;

    printf("\n--- Vehicle Exit ---\n");
    printf("Enter vehicle number: ");
    scanf("%19s", number);

    for(i = 0; i < MAX; i++)
    {
        if(p[i].occupied == 1 &&
           strcmp(p[i].number, number) == 0)
        {
            printf("Entry Time: %02d:00\n", p[i].entryTime);
            printf("Enter exit hour (0-23): ");
            scanf("%d", &exitTime);

            if(exitTime >= p[i].entryTime)
                duration = exitTime - p[i].entryTime;
            else
                duration = 24 - p[i].entryTime + exitTime;

            if(duration == 0)
                duration = 1;

            fee = duration * 20;

            printf("\nVehicle Exit Successful\n");
            printf("Parking Slot: %d\n", i + 1);
            printf("Duration: %d hour(s)\n", duration);
            printf("Parking Fee: Rs. %d\n", fee);

            p[i].occupied = 0;
            p[i].number[0] = '\0';
            p[i].entryTime = 0;

            return;
        }
    }

    printf("Vehicle not found.\n");
}

void searchVehicle(struct Vehicle p[])
{
    char number[20];
    int i;

    printf("\n--- Search Vehicle ---\n");
    printf("Enter vehicle number: ");
    scanf("%19s", number);

    for(i = 0; i < MAX; i++)
    {
        if(p[i].occupied == 1 &&
           strcmp(p[i].number, number) == 0)
        {
            printf("\nVehicle Found\n");
            printf("Vehicle Number: %s\n", p[i].number);
            printf("Parking Slot: %d\n", i + 1);
            printf("Entry Time: %02d:00\n", p[i].entryTime);
            return;
        }
    }

    printf("Vehicle not found.\n");
}

void showStatus(struct Vehicle p[])
{
    int i, count = 0;

    printf("\n--- Parking Status ---\n");

    for(i = 0; i < MAX; i++)
    {
        if(p[i].occupied == 1)
        {
            printf("Slot %d : Occupied - %s\n",
                   i + 1, p[i].number);
            count++;
        }
        else
        {
            printf("Slot %d : Available\n", i + 1);
        }
    }

    printf("\nOccupied Slots: %d\n", count);
    printf("Available Slots: %d\n", MAX - count);
}

void dashboard(struct Vehicle p[])
{
    int i, occupied = 0;

    for(i = 0; i < MAX; i++)
    {
        if(p[i].occupied == 1)
            occupied++;
    }

    printf("\n--- Parking Dashboard ---\n");
    printf("Total Slots: %d\n", MAX);
    printf("Occupied: %d\n", occupied);
    printf("Available: %d\n", MAX - occupied);
    printf("Occupancy: %.1f%%\n",
           (occupied * 100.0) / MAX);

    printf("\nSlot Map:\n");

    for(i = 0; i < MAX; i++)
    {
        if(p[i].occupied == 1)
            printf("[X] ");
        else
            printf("[ ] ");

        if((i + 1) % 10 == 0)
            printf("\n");
    }
}
