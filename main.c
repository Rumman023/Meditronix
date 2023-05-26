//Uses two txt doc for operation
//InventorySize works with the size of the inventory and reads or writes to it
//MedicineInventory Stores the medicine info

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"Array.h"
#include"ExpiryCheck.h"
#include"ShopOwner.h"
#include"Customer.h"
#include"Doctor.h"

#define PATH_TO_FILE "./MedicineInventory.txt"
#define PATH_TO_LIST_SIZE "./InventorySize.txt"
#define PATH_TO_LOGIN_INFO "./AccountInfo.txt"
#define PATH_TO_CUSTOMER_INFO "./CustomerInfo.txt"
#define Prescriptions "./Prescriptions.txt"

#define MAX_LINE_LENGTH 100
#define MAX_MED_LEN 50



void print_centre(char *s)
{
        printf("%95s","");
        printf("%*s%*s\n",10+strlen(s)/2,s,10-strlen(s)/2,"");
}

void home()
{

   printf("\n\n\n\n\n\n\n\n\n\n");
   print_centre("Welcome to Meditronix");
   printf("\n\n\n\n");
   print_centre("Choose a Menu:..");
   print_centre("Doctor's Page (#1)");
   print_centre("Pharmacy Page (#2)");
   print_centre("Customer & Billings (#3)");


   int menu_choice;

   printf("\n%118s","Please Select (1/2/3): ");
   scanf("%d",&menu_choice);

   if(menu_choice == 1)
   {
       system("cls");
       login_to_DocMenu();
   }

   else if (menu_choice == 2)
   {
       system("cls");
       login_to_shop();

   }

   else if (menu_choice == 3)
   {
       system("cls");
       customer();

   }
   else
   {
       print_centre("Invalid input.Please try again\n");
       system("cls");
       home();

   }
}

int main()
{


  home();

}


