// src/user.c
#include <stdio.h>
#include <stdlib.h>
#include "../include/user.h"
#include "../include/hostel.h"

int userMenu() {
    Hostel *arr = NULL; int n = loadHostels(&arr);
    if (n==0) { printf("No hostels available currently.\n"); return 0; }
    float budget;
    int want_ac, want_bath;
    float max_distance;
    printf("\n-- User Mode --\nEnter your yearly budget: "); scanf("%f", &budget);
    printf("Do you want AC? 1/0: "); scanf("%d", &want_ac);
    printf("Attached bathroom? 1/0: "); scanf("%d", &want_bath);
    printf("Max distance (m) you're willing to travel: "); scanf("%f", &max_distance);
    int idx;
    Hostel *best = recommendHostel(arr, n, budget, want_ac, want_bath, max_distance, &idx);
    if (!best) {
        printf("Sorry, no hostels match your criteria.\n");
    } else {
        printf("Recommended: %s (id %d)\nPrice: ₹%d | AC:%d | Bath:%d | Distance:%.2fkm | Free beds:%d\n",
            best->name, best->id, best->price, best->ac, best->attached_bath, best->distance_km, best->capacity - best->occupied);
        printf("Do you want to book this hostel? 1/0: ");
        int book; scanf("%d", &book);
        if (book) {
            arr[idx].occupied += 1;
            if (saveHostels(arr, n)) printf("Booking recorded. Contact admin for confirmation.\n");
            else printf("Failed to record booking.\n");
        }
    }
    free(arr);
    return 0;
}
