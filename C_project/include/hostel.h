#ifndef HOSTEL_H
#define HOSTEL_H
#define NAME_LEN 100
typedef struct {
    int id;
    char name[NAME_LEN];
    int price;
    int ac;
    int attached_bath;
    float distance_km;
    int capacity;
    int occupied;
} Hostel;

int loadHostels(Hostel **arr);
int saveHostels(Hostel *arr, int n);
int addHostel(Hostel h);
int updateHostel(int id, Hostel h);
Hostel *recommendHostel(Hostel *arr, int n, int budget, int want_ac, int want_bath, float max_distance, int *out_index);
#endif
