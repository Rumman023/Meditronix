
#pragma once
#include"Array.h"


void draw_border(int length,char symbol);
void print_inventory(controller* array_control);
void see_array_content (controller* array_control);
void serialize_inventory(FILE* fp,controller* array_control,int start,int end);
void serialize_List_size(FILE* fp,int size);
void deserialize_inventory(FILE* fp,controller* array_control,int inventory_size);
void deserialize_List_Size(FILE* fp);
void shop_menu();
void login_to_shop();
