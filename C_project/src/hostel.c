// src/hostel.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hostel.h"
#define HOSTEL_FILE "data/hostels.txt"
#define LINE_LEN 512

static int nextIdFromList(Hostel *arr, int n) {
    int max = 0;
    for (int i = 0; i < n; ++i) if (arr[i].id > max) max = arr[i].id;
    return max + 1;
}

int loadHostels(Hostel **arr) {
    FILE *f = fopen(HOSTEL_FILE, "r");
    if (!f) { *arr = NULL; return 0; }
    char line[LINE_LEN];
    int cap = 8, count = 0;
    Hostel *list = malloc(sizeof(Hostel) * cap);
    while (fgets(line, sizeof(line), f)) {
        if (count >= cap) { cap *= 2; list = realloc(list, sizeof(Hostel)*cap); }
        Hostel h;
        int scanned = sscanf(line, "%d|%99[^|]|%d|%d|%d|%f|%d|%d",
            &h.id, h.name, &h.price, &h.ac, &h.attached_bath, &h.distance_km, &h.capacity, &h.occupied);
        if (scanned >= 8) list[count++] = h;
    }
    fclose(f);
    *arr = list;
    return count;
}

int saveHostels(Hostel *arr, int n) {
    FILE *f = fopen(HOSTEL_FILE, "w");
    if (!f) return 0;
    for (int i = 0; i < n; ++i) {
        fprintf(f, "%d|%s|%d|%d|%d|%.2f|%d|%d\n",
            arr[i].id, arr[i].name, arr[i].price, arr[i].ac, arr[i].attached_bath,
            arr[i].distance_km, arr[i].capacity, arr[i].occupied);
    }
    fclose(f);
    return 1;
}

int addHostel(Hostel h) {
    Hostel *arr = NULL; int n = loadHostels(&arr);
    int newid = nextIdFromList(arr, n);
    h.id = newid;
    Hostel *newarr = realloc(arr, sizeof(Hostel)*(n+1));
    newarr[n] = h;
    int ok = saveHostels(newarr, n+1);
    free(newarr);
    return ok;
}

int updateHostel(int id, Hostel h) {
    Hostel *arr = NULL; int n = loadHostels(&arr);
    int found = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i].id == id) { h.id = id; arr[i]=h; found = 1; break; }
    }
    int ok = 0;
    if (found) ok = saveHostels(arr, n);
    free(arr);
    return ok;
}

Hostel *recommendHostel(Hostel *arr, int n, int budget, int want_ac, int want_bath, float max_distance, int *out_index) {
    int best = -1; double bestScore = -1e9;
    for (int i = 0; i < n; ++i) {
        if (arr[i].occupied >= arr[i].capacity) continue;
        if (arr[i].price > budget) continue;
        if (want_ac && !arr[i].ac) continue;
        if (want_bath && !arr[i].attached_bath) continue;
        if (arr[i].distance_km > max_distance) continue;
        double score = 0.0;
        score += (budget - arr[i].price) * 0.5;
        score += (10.0 - arr[i].distance_km) * 2.0;
        if (arr[i].ac) score += 20;
        if (arr[i].attached_bath) score += 15;
        double freeBeds = arr[i].capacity - arr[i].occupied;
        score += freeBeds * 1.0;
        if (score > bestScore) { bestScore = score; best = i; }
    }
    *out_index = best;
    if (best >= 0) return &arr[best];
    return NULL;
}
