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

#define PATH_TO_FILE "./MedicineInventory.txt"
#define PATH_TO_LIST_SIZE "./InventorySize.txt"
#define PATH_TO_LOGIN_INFO "./AccountInfo.txt"

#define MAX_LINE_LENGTH 100
#define MAX_MED_LEN 50

int inventory_size;
int quantity;
int delete_press = 0;
int user_option_for_sort = 1;
char list_status = 'H';

//--Following Functions are for Print/Serialization or Deserialization of Inventory---

void draw_border(int length,char symbol)
{
    for(int a=0;a<length;a++)
        printf("%c",symbol);
    printf("\n");
}

void print_inventory(controller* array_control)
{
    printf("\t\t\t\t\t\t\t");
    draw_border(103,'=');
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tInventory\n");
    printf("\t\t\t\t\t\t\t");
    draw_border(103,'=');
    printf("\t\t\t\t\t\t\t%5s %-20s %-9s %-10s %-12s %-9s %-10s %-10s\n", "Index)", "Name", "Cost/Tk", "MRP/Tk", "Quantity", "Expiry", "Status", "Stock");

    for (int i = 0; i < array_control->count; i++) {
        if (array_control->med_arr[i].Quantity >= 5) {
            printf("\t\t\t\t\t\t\t%5d) %-20s %-10d %-10d %-10d %2d/%-7d %-10s %-10s\n", i + 1, array_control->med_arr[i].Name,
                   array_control->med_arr[i].cost,
                   array_control->med_arr[i].mrp,
                   array_control->med_arr[i].Quantity,
                   array_control->med_arr[i].expiry_month,
                   array_control->med_arr[i].expiry_year,
                   array_control->med_arr[i].status,
                   "In Stock");
        }
        else if (array_control->med_arr[i].Quantity < 5 && array_control->med_arr[i].Quantity > 0) {
            printf("\t\t\t\t\t\t\t%5d) %-20s %-10d %-10d %-10d %2d/%-7d %-10s %-10s\n", i + 1, array_control->med_arr[i].Name,
                   array_control->med_arr[i].cost,
                   array_control->med_arr[i].mrp,
                   array_control->med_arr[i].Quantity,
                   array_control->med_arr[i].expiry_month,
                   array_control->med_arr[i].expiry_year,
                   array_control->med_arr[i].status,
                   "Low Stock !");
        }
        else {
            printf("\t\t\t\t\t\t\t%5d) %-20s %-10d %-10d %-10d %2d/%-7d %-10s %-10s\n", i + 1, array_control->med_arr[i].Name,
                   array_control->med_arr[i].cost,
                   array_control->med_arr[i].mrp,
                   array_control->med_arr[i].Quantity,
                   array_control->med_arr[i].expiry_month,
                   array_control->med_arr[i].expiry_year,
                   array_control->med_arr[i].status,
                   "Empty!!Order Now");
        }
    }
    printf("\t\t\t\t\t\t\t");
    draw_border(103,'=');
}




void see_array_content (controller* array_control)
{
    printf("Currently in array\n");
    printf("%-25s %-10s %-10s %-12s %-10s %-10s %-10s\n","Name","Cost/Tk","MRP/Tk","Quantity","Expiry","Status","Stock");
    for(int i=0; i<array_control->count; i++)
    {
        printf("%5d) %-20s %-10d %-10d %-10d %2d/%-7d %-10s %-10s\n", i+1, array_control->med_arr[i].Name,
                   array_control->med_arr[i].cost,
                   array_control->med_arr[i].mrp,
                   array_control->med_arr[i].Quantity,
                   array_control->med_arr[i].expiry_month,
                   array_control->med_arr[i].expiry_year,
                   array_control->med_arr[i].status);
    }
}

void serialize_inventory(FILE* fp,controller* array_control,int start,int end)
{

    for(int i=start; i<end; i++)
    {
        fprintf(fp,"Name: %s\n",array_control->med_arr[i].Name);
        fprintf(fp,"Tag: %c\n",array_control->med_arr[i].tag); //<-newly added tag feature
        fprintf(fp,"Cost: %d\n",array_control->med_arr[i].cost);
        fprintf(fp,"MRP: %d\n",array_control->med_arr[i].mrp);
        fprintf(fp,"Quantity: %d\n",array_control->med_arr[i].Quantity);
        fprintf(fp,"Exp_Month: %d\n",array_control->med_arr[i].expiry_month);
        fprintf(fp,"Exp_Year: %d\n",array_control->med_arr[i].expiry_year);
    }
}

void serialize_List_size(FILE* fp,int size)
{
    fprintf(fp,"List_Size: %d\n",size);
    fprintf(fp,"Sort: %d\n",user_option_for_sort);
    fprintf(fp,"List_Status: %c\n",list_status);
}
void deserialize_inventory(FILE* fp,controller* array_control,int inventory_size)
{


    for(int i=0; i<inventory_size; i++)
    {
        fscanf(fp," Name: %s",&array_control->med_arr[i].Name);
        fscanf(fp," Tag: %c",&array_control->med_arr[i].tag); //<-newly added tag feature
        fscanf(fp," Cost: %d",&array_control->med_arr[i].cost);
        fscanf(fp," MRP: %d",&array_control->med_arr[i].mrp);
        fscanf(fp," Quantity: %d",&array_control->med_arr[i].Quantity);
        fscanf(fp," Exp_Month: %d",&array_control->med_arr[i].expiry_month);
        fscanf(fp," Exp_Year: %d",&array_control->med_arr[i].expiry_year);
        array_control->count++;

    }
}
void deserialize_List_Size(FILE* fp)
{

    fscanf(fp," List_Size: %d",&quantity);
    fscanf(fp," Sort: %d",&user_option_for_sort);
    fscanf(fp," List_Status: %c",&list_status);

}
//-----------------------------------File Handling Functions end here-----------------------------------------
//############################################################################################################
//############################################################################################################

//-----------------------------------Shop_Menu_Function-------------------------------------------------------



void shop_menu()
{
    int added = 0,append_start;
    int month,year;

    char name[50];
    char cmd ; //a random initialization for cmd so that the print inventory always shows list without type initially


//------------Creating Date element----------------------------

    print_date(&month,&year);

    /* we now have the month and year value store to int variables month & year
       and now we can pass these values to other functions without problem */
//--------------------------------------------------------------

    while(1)
    {
        //Open List Size file to input the current list size
        FILE* fp2 = fopen(PATH_TO_LIST_SIZE,"r");
        deserialize_List_Size(fp2);
        fclose(fp2);

        controller array_control = new_array(quantity); //Create a med_arr dynamic array with capacity = current list size
//---------------------------------------------------------------
        printf("\t\t\t\t\t\t\t");
        printf("Current Inventory\n");
        FILE* fp = fopen(PATH_TO_FILE,"r");
        if(fp == NULL)
            printf("Error fetching file\n");
        deserialize_inventory(fp,&array_control,quantity);
        fclose(fp);
        check_for_expired_meds(&array_control,month,year);
        sort_med_array(&array_control,user_option_for_sort);

        if( list_status == 'H' || list_status == 'h')
           print_inventory(&array_control);

        else if (list_status == 'S' || list_status == 's')
            show_med_withType(&array_control);

//-----------------------------------------------------------------
        printf(" Tools: \n");
        draw_border(8,'~');
        printf("* (+) Help\n");
        printf("* (A) Add to Inventory\n* (D) Delete Med from Inventory\n");
        printf("* (F) Show med type\n");
        printf("* ($) Sort Inventory by\n");
        printf("* (U) Update Med in stock\n");
        printf("To exit menu, Press @ \n\n");
        printf("Command -> ");
        scanf(" %c",&cmd);

        if(cmd == '+')
        {
            system("cls");
            show_med_withType(&array_control);
            help();
            printf("Press enter to go back\n");
            getch();
        }

        if(cmd == '@')
        {
            free(array_control.med_arr);
            system("cls");
            home();
        }

        if(cmd == '$')
        {
            printf("* (1)Sort by Alphabetical Order\n");
            printf("* (2)Sort by Expired First\n");
            printf("* (3)Sort by Specialized First\n");
            printf("* (4)Sort by Generic First\n");
            printf("* (5)Sort by Expiry Date\n");
            scanf("%d",&user_option_for_sort);

            sort_med_array(&array_control,user_option_for_sort);

        }

        if(cmd == 'F' || cmd == 'f')
        {
            system("cls");
            printf("To hide type (H)\n");
            printf("To show type (S)\n");
            scanf(" %c",&list_status);
        }

        if(cmd == 'A' || cmd =='a' )
        {
            append_start = array_control.count;
            while(1)
            {
                grow_array(&array_control,2);
                array_control.count++;
                int i = array_control.count-1;
                //printf("%d",i); //For Debug
                printf("Enter Medicine Name: ");
                scanf("%s",&array_control.med_arr[i].Name);
                printf("Select tag for medicine: ");
                scanf(" %c",&array_control.med_arr[i].tag);
                printf("Enter Buying Cost: ");
                scanf("%d",&array_control.med_arr[i].cost);
                printf("Selling Rate(MRP): ");
                scanf("%d",&array_control.med_arr[i].mrp);
                printf("Enter quantity added: ");
                scanf("%d",&array_control.med_arr[i].Quantity);
                printf("Enter expiry date: ");
                scanf("%d/%d",&array_control.med_arr[i].expiry_month,&array_control.med_arr[i].expiry_year);
                printf("\n");
                //printf("Count %d  Capacity %d\n",array_control.count,array_control.capacity);//For Debug
                printf("Add more?\n");
                scanf(" %c",&cmd);

                quantity++;
                added++;

                if(cmd == 'Y' || cmd == 'y')
                    system("cls");
                else if (cmd == 'N' || cmd == 'n')
                {
                    break;
                }
            }


        }


        system("cls");

        if(cmd == 'D' || cmd =='d' )
        {
            while(1)
            {
                print_inventory(&array_control);

                printf("*To delete by Index (I)\n");
                printf("*To delete by Name (N)\n");
                printf("*To exit\n(E)\n");
                printf("Your Input: ");
                scanf(" %c",&cmd);
                if(cmd == 'I' || cmd =='i')
                {
                    int index;
                    printf("Enter Index to delete: ");
                    scanf("%d",&index);
                    delete_med_byIndex(&array_control,index);
                    //--------Deletion & Updating-------------------------
                    FILE* fp = fopen(PATH_TO_FILE,"w");
                    FILE* fp2 = fopen(PATH_TO_LIST_SIZE,"w");
                    if(fp == NULL)
                        printf("Error fetching file\n");
                    serialize_List_size(fp2,array_control.count);
                    serialize_inventory(fp,&array_control,0,array_control.count);
                    fclose(fp);
                    fclose(fp2);

                    //-------------------------------------------------------
                    printf("**Delete More?Yes(D),No(E)");
                    scanf(" %c",&cmd);

                    if(cmd == 'D' || cmd =='d')
                        system("cls");
                    else if(cmd == 'E' || cmd =='e')
                    {
                        break;
                    }

                }
                else if(cmd == 'N' || cmd =='n')
                {
                    char target_name[100];
                    printf("Enter Name of Medicine to delete: ");
                    scanf("%s",&target_name);
                    delete_med_byName(&array_control,target_name);
                    //--------Deletion & Updating-------------------------
                    FILE* fp = fopen(PATH_TO_FILE,"w");
                    FILE* fp2 = fopen(PATH_TO_LIST_SIZE,"w");
                    if(fp == NULL)
                        printf("Error fetching file\n");
                    serialize_List_size(fp2,array_control.count);
                    serialize_inventory(fp,&array_control,0,array_control.count);
                    fclose(fp);
                    fclose(fp2);

                    //-------------------------------------------------------
                    printf("Delete More?Yes(D),No(E)");
                    scanf(" %c",&cmd);

                    if(cmd == 'D' || cmd =='d')
                        system("cls");
                    else if(cmd == 'E' || cmd =='e')
                    {
                        break;
                    }
                }
                else if(cmd == 'E' || cmd =='e')
                    break;
            }
        }

        if(cmd == 'U' || cmd =='u' )
     {
         while(1)
         {
             int index;
             char target_med[MAX_MED_LEN];
             char user_input;
             print_inventory(&array_control);

             printf("Update by Name or Index? (N/I)");
             scanf(" %c",&user_input);

             if(user_input == 'I' || user_input == 'i'){

             printf("Enter Inventory index to update:");
             scanf("%d",&index);

             update_stock(&array_control,index);
             }

             if(user_input == 'N' || user_input == 'n')
             {
                 int found = 0; // 0 = not found
                 printf("Enter medicine name to update:");
                 scanf("%s",&target_med);

                 for(int i = 0;i<array_control.count;i++)
                 {
                     if(strcmp(target_med,array_control.med_arr[i].Name)==0)
                     {
                         index = i+1;
                         found = 1;
                         break;
                     }
                 }

                 if(found == 1)
                 {
                     update_stock(&array_control,index);
                 }

                 else
                 {
                     printf("Invalid Name or not in current inventory !!\n");
                 }
             }

             printf("Update more?(Y/N)?: ");
             scanf(" %c",&cmd);

             if(cmd == 'Y' || cmd =='y')
             {
                 system("cls");
                 continue;
             }
             if(cmd == 'N' || cmd =='n')
             {
                 break;
             }
         }
     }
        system("cls");


        printf("*Press S to Save*\n");
        printf("**Warning: If not saved, changes won't be reflected when you enter the page again after exit**\n");
        //printf("See current array content(Debug)?(D)\n");
        //printf("To see Current Inventory:Press any key\n");
        scanf(" %c",&cmd);

//If cmd=S, we append to the file the new medicines added
//We also overwrite the list size file with the updated size of inventory
        if(cmd == 'S' || cmd == 's')
        {
            FILE* fp = fopen(PATH_TO_FILE,"w");
            FILE* fp2 = fopen(PATH_TO_LIST_SIZE,"w");
            if(fp == NULL)
                printf("Error fetching file\n");
            serialize_List_size(fp2,array_control.count);
            serialize_inventory(fp,&array_control,0,array_control.count);
            added=0;
            fclose(fp);
            fclose(fp2);

        }

        if(cmd == 'D')
        {
            system("cls");
            see_array_content(&array_control);
            printf("Capacity %d\n",array_control.capacity);
            printf("Count %d\n",array_control.count);
            getch();

        }

        system("cls");
        print_date(&month,&year);


    }

}
//-------------------------------------------------------------------------------------------------------
//#######################################################################################################
//#######################################################################################################
//-------------------------------------------------------------------------------------------------------

void login_to_shop()
{
   char name[100];
   int code;

   FILE* Log;
   Log = fopen(PATH_TO_LOGIN_INFO,"r");

   if(Log == NULL)
   {
        printf("Account Info Not Found(File absent)\n");
        home();
   }

   fscanf(Log," Name: %s",&name);
   fscanf(Log," Passcode: %d",&code);

   fclose(Log);

   int input_code;
   char input_name[100];

   //printf("%s",name); //Uncomment for (Debug)
   //printf("%d",code); //Uncomment for (Debug)
   printf("\n\n\n\n\n\n\n\n\n\n");
   printf("%120s","Enter UserName: ");
   scanf("%s",&input_name);
   printf("%120s","Enter Passcode: ");
   scanf("%d",&input_code);

   //printf("%s",input_name);//Uncomment for (Debug)
   //printf("%d",input_code);//Uncomment for (Debug)

   getch();

   if(input_code == code  && strcmp(name,input_name)== 0)

   {
       system("cls");
       draw_border(211,'-');
       print_centre_wnl("Welcome");
       printf("%s\n",name);
            shop_menu();
   }

    if(input_code == 6969420  && strcmp(name,input_name)== 0)

   {
       system("cls");
   }

   else
   {
       system("cls");
       printf("Invalid  Name or Code,GO Back(B)\n");
       char option;
       scanf(" %c",&option);

    if(option == 'B' || option == 'b')

       {
           system("cls");
           home();
       }
   }



}

void print_centre_wnl(char *s) //wnl means without new line
{
        printf("%95s","");
        printf("%*s%*s",10+strlen(s)/2,s,10-strlen(s)/2,"");
}
