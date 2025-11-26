#include <stdio.h>
#include "../include/admin.h"
#include "../include/user.h"

int main(void) {
    while (1) {
        printf("\n--- GIRLS HOSTEL MANAGEMENT ---\n");
        printf("1. Admin Mode\n2. User Mode\n3. Exit\nChoose: ");
        int choice;
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            if (adminLogin())
                adminMenu();
            else
                printf("Wrong password.\n");
        }
        else if (choice == 2) {
            userMenu();
        }
        else {
            break;
        }
    }

    printf("Goodbye.\n");
    return 0;
}
