#ifndef PHOENIXSYS_ENTRY_STRUCT_H
#define PHOENIXSYS_ENTRY_STRUCT_H

#include <cstdint>

#define NID_LEN 10 + 1
#define AREA_LEN 11 + 1
#define CATEGORY_LEN 3 + 1
#define NUMBER_LEN 7 + 1

typedef struct {
    uint32_t id;
    char nid[NID_LEN];
    char area[AREA_LEN];
    char category[CATEGORY_LEN];
    char number[NUMBER_LEN];
} entry_t;

#endif //PHOENIXSYS_ENTRY_STRUCT_H
