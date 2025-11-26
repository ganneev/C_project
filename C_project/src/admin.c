// src/admin.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/admin.h"
#include "../include/hostel.h"

int adminLogin() {
    char pwd[64];
    const char *correct = "admin123";
    printf("Enter admin password: ");
    scanf("%63s", pwd);
    return strcmp(pwd, correct) == 0;
}

int adminMenu() {
    while (1) {
        printf("\n-- Admin Menu --\n1. Add hostel\n2. Update hostel\n3. View hostels\n4. Exit admin\nChoose: ");
        int c; if (scanf("%d", &c) != 1) return 0;
        if (c == 1) {
            Hostel h;
            printf("Enter name: "); scanf(" %[^\n]", h.name);
            printf("Enter price per month (int): "); scanf("%d", &h.price);
            printf("AC? 1/0: "); scanf("%d", &h.ac);
            printf("Attached bath? 1/0: "); scanf("%d", &h.attached_bath);
            printf("Distance (km): "); scanf("%f", &h.distance_km);
            printf("Capacity: "); scanf("%d", &h.capacity);
            h.occupied = 0;
            if (addHostel(h)) printf("Hostel added.\n"); else printf("Error adding hostel.\n");
        } else if (c == 2) {
            int id; printf("Enter hostel id to update: "); scanf("%d", &id);
            Hostel *arr = NULL; int n = loadHostels(&arr);
            int found = 0;
            for (int i = 0; i < n; ++i) if (arr[i].id == id) { found = 1; break; }
            if (!found) { printf("Hostel not found.\n"); free(arr); continue; }
            Hostel h;
            for (int i=0;i<n;++i) if (arr[i].id==id) { h = arr[i]; break; }
            printf("Editing hostel. Enter new values:\n");
            printf("New name: "); scanf(" %[^\n]", h.name);
            printf("New price: "); scanf("%d", &h.price);
            printf("AC? 1/0: "); scanf("%d", &h.ac);
            printf("Attached bath? 1/0: "); scanf("%d", &h.attached_bath);
            printf("Distance (km): "); scanf("%f", &h.distance_km);
            printf("Capacity: "); scanf("%d", &h.capacity);
            if (updateHostel(id, h)) printf("Updated.\n"); else printf("Update failed.\n");
            free(arr);
        } else if (c == 3) {
            Hostel *arr = NULL; int n = loadHostels(&arr);
            if (n==0) printf("No hostels yet.\n");
            for (int i=0;i<n;++i) {
                Hostel *p = &arr[i];
                printf("%d: %s | ₹%d | AC:%d | Bath:%d | %.2fkm | cap:%d occ:%d\n",
                    p->id, p->name, p->price, p->ac, p->attached_bath, p->distance_km, p->capacity, p->occupied);
            }
            free(arr);
        } else return 0;
    }
    return 0;
}
