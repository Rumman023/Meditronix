#include<string.h>
#include"Array.h"
#pragma once

typedef struct _validity{
   char Code[100];
   int Val[10];
   int Size;
} Validity;

typedef struct _Billing{
     char Name[50];
     int Amount;
     int Price;
     int Total;
}Billing;

typedef struct _Medi
{
    char Name[50];
    int Quantity;
    char Dosage[10];
    char Frequency[20];
    int PurchaseAbility;
} Medi ;

typedef struct Prescription
{
    char PresCode[10];
    char Name[50];
    int PatNum;
    int MedNo;
    int Age;
    char Gender[10];
    Medi Medicines[10];

} Prescription;

//this is the main customer window
void customer();
void login_customer();
void generic_medicine();
void view_prescription();
Prescription* get_prescription(FILE* Log);
void print_prescription(Prescription* CurPres);
void customer_print_inventory(controller* array_control);

