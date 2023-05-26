#pragma once

typedef struct
{
    char Name[50];
    char tag;         // g for generic s for specialized
    int Quantity;
    int cost;
    int mrp;
    int expiry_month;
    int expiry_year;
    char status[10];
} Medicine ;

typedef struct
{
    Medicine* med_arr;
    int count;
    int capacity;

} controller;

controller new_array (int init_size);

/// done
int grow_array(controller *array_control,int new_capacity);

/// done
void delete_med_byIndex(controller *array_control,int index_num);

/// done
void delete_med_byName(controller *array_control,char* name);

/// done
void update_stock(controller *array_control,int index_num);

/// @brief sort the medicine array in a specified order;
/// @param 2nd argument (1 or 2) if 1,sort in alphabetical order if 2 show expired meds first
/// Note: Do at last
/// done
void sort_med_array(controller *array_control,int option);

void help();


