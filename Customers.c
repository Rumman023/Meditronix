
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"Array.h"
#include"ExpiryCheck.h"
#include"Customer.h"

#define PATH_TO_FILE "./MedicineInventory.txt"
#define PATH_TO_LIST_SIZE "./InventorySize.txt"
#define PATH_TO_LOGIN_INFO "./AccountInfo.txt"
#define PATH_TO_CUSTOMER_INFO "./CustomerInfo.txt"
#define Prescriptions "./Prescription.txt"
#define PATH_TO_VALIDITYCHECKER "./BuyingValidity.txt"

#define MAX_LINE_LENGTH 100
#define MAX_MED_LEN 50

int inventory_size;
int quantity;


void customer_print_inventory(controller* array_control)
{
    printf("\t\t\t\t\t\t\t");
    draw_border(80,'=');
    printf("\t\t\t\t\t\t\t\t\t\tCurrently available Medicines\n");
    printf("\t\t\t\t\t\t\t");
    draw_border(80,'=');
    printf("\t\t\t\t\t\t\t%5s %-15s %-10s %-12s %-9s \n", "      ", "Name", "MRP/Tk", "Quantity", "Expiry");
    for (int i = 0; i < array_control->count; i++)
    {
        if (array_control->med_arr[i].tag == 'g' && array_control->med_arr[i].status[0] == 'V')
        {
            printf("\t\t\t\t\t\t\t%5## %-20s %-10d %-10d %2d/%-7d \n", array_control->med_arr[i].Name,
                   array_control->med_arr[i].mrp,
                   array_control->med_arr[i].Quantity,
                   array_control->med_arr[i].expiry_month,
                   array_control->med_arr[i].expiry_year);
        }
        else
        {
            continue;
        }
    }
    printf("\t\t\t\t\t\t\t");
    draw_border(80,'=');
}

void customer_serialize_inventory(FILE* fp,controller* array_control,int start,int end)
{

    for(int i=start; i<end; i++)
    {
        fprintf(fp,"Name: %s\n",array_control->med_arr[i].Name);
        fprintf(fp,"Tag: %c\n",array_control->med_arr[i].tag);
        fprintf(fp,"Cost: %d\n",array_control->med_arr[i].cost);
        fprintf(fp,"MRP: %d\n",array_control->med_arr[i].mrp);
        fprintf(fp,"Quantity: %d\n",array_control->med_arr[i].Quantity);
        fprintf(fp,"Exp_Month: %d\n",array_control->med_arr[i].expiry_month);
        fprintf(fp,"Exp_Year: %d\n",array_control->med_arr[i].expiry_year);
    }
}

void customer_serialize_List_size(FILE* fp,int size)
{
    fprintf(fp,"List_Size: %d",size);
}

void customer_deserialize_inventory(FILE* fp,controller* array_control,int inventory_size)
{


    for(int i=0; i<inventory_size; i++)
    {
        fscanf(fp," Name: %s",&array_control->med_arr[i].Name);
        fscanf(fp," Tag: %c",&array_control->med_arr[i].tag);
        fscanf(fp," Cost: %d",&array_control->med_arr[i].cost);
        fscanf(fp," MRP: %d",&array_control->med_arr[i].mrp);
        fscanf(fp," Quantity: %d",&array_control->med_arr[i].Quantity);
        fscanf(fp," Exp_Month: %d",&array_control->med_arr[i].expiry_month);
        fscanf(fp," Exp_Year: %d",&array_control->med_arr[i].expiry_year);
        array_control->count++;

    }
}
void customer_deserialize_List_Size(FILE* fp)
{

    fscanf(fp," List_Size: %d",&quantity);

}

//=======================================File Handling Ends Here===============================================

//=========================================Customer Menu==================================================
void customer()
{
    print_centre("Welcome to Customer window\n");
    print_centre("Please enter what type of medicine you want to buy:\n");
    print_centre("(#1)Generic Medicine\n");
    print_centre("(#2)Prescribed Medicine\n");
    print_centre("(#3)View Prescription\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\tYour choice: ");
    int choice;
    scanf("%d",&choice);
    if(choice==1)
    {
        system("cls");
        generic_medicine();
    }
    else if(choice==2)
    {
        system("cls");
        login_customer();
    }
    else if(choice==3)
    {
        system("cls");
        view_prescription();
    }
    else
    {
        printf("\n");
        print_centre("Not a valid option\n");
        printf("\t\t\t\t\t\t\t\t\t\tPress e to exit to home menu.Press any other character to try again: ");
        char t;
        fflush(stdin);
        scanf("%c",&t);
        if(t=='e')
        {
            system("cls");
            home();
        }
        else
        {
            system("cls");
            customer();
        }
    }
}

//======================THIS IS THE MENU FOR BUYING GENERIC MEDICINE WITHOUT PRESCRIPTION=====================

void generic_medicine()
{
    //-----------------Deserializing Inventory----------
    FILE* fp2 = fopen(PATH_TO_LIST_SIZE,"r");
    customer_deserialize_List_Size(fp2);
    fclose(fp2);
    controller array_control = new_array(quantity);
    FILE* fp = fopen(PATH_TO_FILE,"r");
    if(fp == NULL)
    {
        print_centre("Error cannot access shop\n");
        system("cls");
        customer();
    }
    customer_deserialize_inventory(fp,&array_control,quantity);
    fclose(fp);
    //Checking for expired medicine
    int month,year;
    print_date(&month,&year);
    check_for_expired_meds(&array_control,month,year);
    customer_print_inventory(&array_control);

    // structure for generating bill
    Billing Bill[30];
    int j=0;
    while(1)
    {
        char name[50];
        int amount,k=0,p=0;
        int finding_medicine=0;
        int total_stock=0;
        int prev_stock_tracker[10];
        printf("\t\t\t\t\t\t Enter The Name of The Medicine you want to buy: ");
        scanf("%s",&name);
        printf("\t\t\t\t\t\t Enter The Amount of The Medicine you want to buy: ");
        scanf("%d",&amount);
        for(int i = 0; i < array_control.count; i++)
        {
            if(strcmp(name,array_control.med_arr[i].Name)==0 && array_control.med_arr[i].status[0]=='V')
            {
                if(amount<= array_control.med_arr[i].Quantity)
                {
                    array_control.med_arr[i].Quantity=array_control.med_arr[i].Quantity-amount;
                    Bill[j].Amount=amount;
                    Bill[j].Price=array_control.med_arr[i].mrp*amount;
                    strcpy(Bill[j].Name,name);
                    j++;
                    finding_medicine++;
                    break;
                }
                else if(total_stock+ array_control.med_arr[i].Quantity >=amount )
                {
                    array_control.med_arr[i].Quantity=array_control.med_arr[i].Quantity+total_stock-amount;
                    Bill[j].Price=0;
                    Bill[j].Amount=amount;
                    for(p=0; p<k; p++)
                    {
                        Bill[j].Price+=array_control.med_arr[prev_stock_tracker[p]].Quantity*array_control.med_arr[prev_stock_tracker[p]].mrp;
                        array_control.med_arr[prev_stock_tracker[p]].Quantity=0;
                    }
                    Bill[j].Price+=((amount-total_stock)*array_control.med_arr[i].mrp);
                    strcpy(Bill[j].Name,name);
                    j++;
                    finding_medicine++;
                    break;
                }
                else if(amount> array_control.med_arr[i].Quantity)
                {
                    total_stock+=array_control.med_arr[i].Quantity;
                    prev_stock_tracker[k]=i;
                    k++;
                }
            }
        }
        if(finding_medicine==0)
        {
            printf("\t\t\t\t\t\t\t\t\t\tSorry this medicine is not available in this amount.\n");
            printf("\t\t\t\t\t\t\t\t\t\tDo you want to buy anything else?(Y/N) : ");
            fflush(stdin);
            char opt;
            scanf("%c",&opt);
            if(opt=='Y' || opt=='y')continue;
            else
            {
                system("cls");
                break;
            }
        }
        else
        {
            printf("\t\t\t\t\t\t\t\t\t\tBuying %s in %d amount\n",name,amount);
            printf("\t\t\t\t\t\t\t\t\t\tDo you want to buy anything else?(Y/N) : ");
            fflush(stdin);
            char opt;
            scanf("%c",&opt);
            if(opt=='Y' || opt=='y')continue;
            else
            {
                system("cls");
                break;
            }
        }
    }

    //---------------------Generating Bill----------------------------

    print_date(&month,&year);
    printf("\t\t\t\t\t\t\t");
    draw_border(60,'=');
    printf("\t\t\t\t\t\t\t\t\t\tBILL\n");
    printf("\t\t\t\t\t\t\t");
    draw_border(60,'=');
    printf("\t\t\t\t\t\t\t%5s %-20s %-10s %-12s \n", "    ", "Name", "MRP/Tk", "Quantity");
    int total=0;
    for(int k=0; k<j; k++)
    {
        printf("\t\t\t\t\t\t\t%5d) %-20s %-10d %-12d \n",k+1,Bill[k].Name,Bill[k].Price,Bill[k].Amount);
        total+=Bill[k].Price;
    }
    printf("\t\t\t\t\t\t\t");
    draw_border(60,'=');
    printf("\t\t\t\t\t\t\t\t\tTOTAL BILL : %d TK\n",total);

    //-------------------Serializing Inventory----------------------

    FILE* fp6 = fopen(PATH_TO_FILE,"w");
    FILE* fp7 = fopen(PATH_TO_LIST_SIZE,"w");

    customer_serialize_List_size(fp7,array_control.count);
    customer_serialize_inventory(fp6,&array_control,0,array_control.count);
    fclose(fp6);
    fclose(fp7);
    printf("\t\t\t\t\t\t\t\t\tTHANK YOU FOR TRUSTING US!\n\n");
    printf("\t\t\t\t\t\t\t\t\tPRESS ANY KEY TO GO BACK TO HOME: ");
    char opt;
    fflush(stdin);
    scanf("%c",&opt);
    system("cls");
    home();

}

//=====================THIS IS THE MENU FOR BUYING PRESCRIBED MEDICINE============================

void login_customer()
{

    print_centre("Welcome to Patient's window\n");
    print_centre("To buy medicine please log in\n");
    char input_code[100];
    printf("\t\t\t\t\t\t\t\t\t\tUnique Prescription No: ");
    fflush(stdin);
    scanf("%s",&input_code);

    //Opening Prescription file to find prescription

    FILE* Log;
    Log = fopen(Prescriptions,"r");

    if(Log == NULL)
    {
        printf("Error: Prescription Info Not Found\n");
        print_centre("Press any key to return to home page");
        char opt;
        scanf("%c",&opt);
        system("cls");
        home();
    }
    while(!feof(Log))
    {
        char scancode[100];
        fscanf(Log,"%s",&scancode);
        if(strcmp(scancode,input_code)==0)
        {
            fseek(Log, -(strlen(scancode)+19), SEEK_CUR);
            fscanf(Log,"%s",&scancode);
            if(strcasecmp(scancode,"Prescription")==0)break;
            else Log=NULL;
        }
    }
    if(feof(Log)){
        print_centre("Error: Prescription Info Not Found\n");
        printf("\t\t\t\t\t\t\t\t\t\tPress any key to return to home page: ");
        char opt;
        fflush(stdin);
        scanf("%c",&opt);
        system("cls");
        home();
    }
    system("cls");
    Prescription* CurPres= get_prescription(Log);
    //creating time element
    int month,year;
    print_date(&month,&year);
    print_prescription(CurPres);
    fclose(Log);
    printf("\t\t\t\t\t\t\tDo you want to buy any medicines?(Y/N)-");
    char c;
    fflush(stdin);
    scanf("%c",&c);
    if(c=='Y'|| c=='y')
    {
        FILE* fp2 = fopen(PATH_TO_LIST_SIZE,"r");
        customer_deserialize_List_Size(fp2);
        fclose(fp2);
        controller array_control = new_array(quantity);
        FILE* fp = fopen(PATH_TO_FILE,"r");
        if(fp == NULL)
        {
            printf("\t\t\t\t\t\t\t\t\t\tError cannot access shop\n");
            printf("\t\t\t\t\t\t\t\t\t\tPress any key to return to home page: ");
            char opt;
            scanf("%c",&opt);
            system("cls");
            home();
        }
        customer_deserialize_inventory(fp,&array_control,quantity);
        fclose(fp);
        //Checking for expired medicine

        check_for_expired_meds(&array_control,month,year);

        // structure for generating bill
        Billing Bill[30];
        int j=0;
        while(1)
        {
            char name[50];
            int index,amount,k=0,p=0;
            int finding_medicine=0;
            int total_stock=0;
            int prev_stock_tracker[10];
            printf("\t\t\t\t\t\t Enter The Index of The Medicine you want to buy: ");
            scanf("%d",&index);
            strcpy(name,CurPres->Medicines[index-1].Name);
            printf("\t\t\t\t\t\t Enter The Amount of The Medicine you want to buy: ");
            scanf("%d",&amount);
            for(int i = 0; i < array_control.count; i++)
            {
                if(strcmp(name,array_control.med_arr[i].Name)==0 && array_control.med_arr[i].status[0]=='V')
                {
                    if(CurPres->Medicines[index-1].PurchaseAbility<amount)
                    {
                        printf("\t\t\t\t\tSorry this amount is over your purchase limit\n\t\t\t\t\tDo you want to buy anything else?(Y/N):");
                        char P;
                        fflush(stdin);
                        scanf("%c",&P);
                        if(P=='Y'||P=='y')
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else if(amount<= array_control.med_arr[i].Quantity)
                    {
                        array_control.med_arr[i].Quantity=array_control.med_arr[i].Quantity-amount;
                        Bill[j].Amount=amount;
                        Bill[j].Price=array_control.med_arr[i].mrp*amount;
                        strcpy(Bill[j].Name,name);
                        j++;
                        finding_medicine++;
                        break;
                    }
                    else if(total_stock+ array_control.med_arr[i].Quantity >=amount )
                    {
                        array_control.med_arr[i].Quantity=array_control.med_arr[i].Quantity+total_stock-amount;
                        Bill[j].Price=0;
                        Bill[j].Amount=amount;
                        for(p=0; p<k; p++)
                        {
                            Bill[j].Price+=array_control.med_arr[prev_stock_tracker[p]].Quantity*array_control.med_arr[prev_stock_tracker[p]].mrp;
                            array_control.med_arr[prev_stock_tracker[p]].Quantity=0;
                        }
                        Bill[j].Price+=((amount-total_stock)*array_control.med_arr[i].mrp);
                        strcpy(Bill[j].Name,name);
                        j++;
                        finding_medicine++;
                        break;
                    }
                    else if(amount> array_control.med_arr[i].Quantity)
                    {
                        total_stock+=array_control.med_arr[i].Quantity;
                        prev_stock_tracker[k]=i;
                        k++;
                    }
                }
            }
            if(finding_medicine==0)
            {
                printf("\t\t\t\t\t\t\t\t\t\tSorry this medicine is not available in this amount.\n");
                printf("\t\t\t\t\t\t\t\t\t\tDo you want to buy anything else?(Y/N) : ");
                fflush(stdin);
                char opt;
                scanf("%c",&opt);
                if(opt=='Y' || opt=='y')continue;
                else
                {
                    system("cls");
                    break;
                }
            }
            else
            {
                printf("\t\t\t\t\t\t\t\t\t\tBuying %s in %d amount\n",name,amount);
                printf("\t\t\t\t\t\t\t\t\t\tDo you want to buy anything else?(Y/N) : ");
                fflush(stdin);
                char opt;
                scanf("%c",&opt);
                if(opt=='Y' || opt=='y')continue;
                else
                {
                    system("cls");
                    break;
                }
            }
        }

        //---------------------Generating Bill----------------------------

        print_date(&month,&year);
        printf("\t\t\t\t\t\t\t");
        draw_border(60,'=');
        printf("\t\t\t\t\t\t\t\t\t\tBILL\n");
        printf("\t\t\t\t\t\t\t");
        draw_border(60,'=');
        printf("\t\t\t\t\t\t\t%5s %-20s %-9s %-12s \n", "   ", "Name", "MRP/Tk", "Quantity");
        int total=0;
        for(int k=0; k<j; k++)
        {
            printf("\t\t\t\t\t\t\t%5d) %-20s %-9d %-12d \n",k+1,Bill[k].Name,Bill[k].Price,Bill[k].Amount);
            total+=Bill[k].Price;
        }
        printf("\t\t\t\t\t\t\t");
        draw_border(60,'=');
        printf("\t\t\t\t\t\t\t\t\tTOTAL BILL : %d TK\n",total);

        //-------------------Serializing Inventory----------------------

        FILE* fp6 = fopen(PATH_TO_FILE,"w");
        FILE* fp7 = fopen(PATH_TO_LIST_SIZE,"w");

        customer_serialize_List_size(fp7,array_control.count);
        customer_serialize_inventory(fp6,&array_control,0,array_control.count);
        fclose(fp6);
        fclose(fp7);
        printf("\t\t\t\t\t\t\t\t\tTHANK YOU FOR TRUSTING US!\n\n");
        printf("\t\t\t\t\t\t\t\t\tPRESS ANY KEY TO GO BACK TO HOME: ");
        char opt;
        fflush(stdin);
        scanf("%c",&opt);
        system("cls");
        home();

    }

   else {
    system("cls");
    home();
   }

}


void view_prescription()
{
    print_centre("Welcome to Patient's window\n");
    print_centre("To view prescription please log in\n");
    char input_code[100];
    printf("\t\t\t\t\t\t\t\t\t\tUnique Prescription No: ");
    fflush(stdin);
    scanf("%s",&input_code);

    //Opening Prescription file to find prescription

    FILE* Log;
    Log = fopen(Prescriptions,"r");

    if(Log == NULL)
    {
        printf("Error: Prescription Info Not Found\n");
        print_centre("Press any key to return to home page");
        char opt;
        scanf("%c",&opt);
        system("cls");
        home();
    }
    while(!feof(Log))
    {
        char scancode[100];
        fscanf(Log,"%s",&scancode);
        if(strcmp(scancode,input_code)==0)
        {
            fseek(Log, -(strlen(scancode)+19), SEEK_CUR);
            fscanf(Log,"%s",&scancode);
            if(strcasecmp(scancode,"Prescription")==0)break;
            else Log=NULL;
        }
    }
    if(feof(Log)){
        print_centre("Error: Prescription Info Not Found\n");
        printf("\t\t\t\t\t\t\t\t\t\tPress any key to return to home page: ");
        char opt;
        fflush(stdin);
        scanf("%c",&opt);
        system("cls");
        home();
    }
    system("cls");
    Prescription* CurPres= get_prescription(Log);
    //creating time element
    /*if(strcmp(input_name,CurPres->Name)){
            print_centre("Invalid Name or Code\n");
            char opt;
            scanf("%c",&opt);
            system("cls");
            home();

    }*/
    int month,year;
    print_date(&month,&year);
    print_prescription(CurPres);
    fclose(Log);
    printf("\t\t\t\t\t\t\t\t\tPRESS ANY KEY TO GO BACK TO HOME: ");
    char opt;
    fflush(stdin);
    scanf("%c",&opt);
    system("cls");
    home();

}



//-------------------Function for deserializing Prescription-------------------

Prescription* get_prescription(FILE* Log)
{
    Prescription* CurPres =(Prescription*) malloc(sizeof(Prescription));
    fscanf(Log," Code: %s",&CurPres->PresCode);
    fscanf(Log," Patient Number: %d",&CurPres->PatNum);
    fscanf(Log," Number of Medicine: %d",&CurPres->MedNo);
    fscanf(Log," Name: %[^\n]s",&CurPres->Name);
    fscanf(Log," Age: %d",&CurPres->Age);
    fscanf(Log," Gender: %s",&CurPres->Gender);
    int i,p,t=CurPres->MedNo;
    for(i=0; i<t; i++)
    {
        fscanf(Log," Medication %d:",&p);
        fscanf(Log," Name: %[^\n]s",&CurPres->Medicines[i].Name);
        fscanf(Log," Dosage: %[^\n]s",&CurPres->Medicines[i].Dosage);
        fscanf(Log," Quantity: %d",&CurPres->Medicines[i].Quantity);
        fscanf(Log," Frequency: %[^\n]s",&CurPres->Medicines[i].Frequency);
        CurPres->Medicines[i].PurchaseAbility=CurPres->Medicines[i].Dosage;
    }
    return CurPres;
}

//------------------------FUNCTION FOR PRINTING PRESCRIPTION-----------------------

void print_prescription(Prescription* CurPres)
{
    draw_border(200,'=');
    printf("\t\t\t\t\t\t\t\t\tPrescription of %s \n",CurPres->Name);
    draw_border(200,'=');
    printf("\t\t\t\t\t\t\t\t\t\tPrescription Code: %s\n",CurPres->PresCode);
    printf("\t\t\t\t\t\t\t\t\t\tPatient Number: %d\n",CurPres->PatNum);
    printf("\t\t\t\t\t\t\t\t\t\tNumber of Medicine: %d\n",CurPres->MedNo);
    printf("\t\t\t\t\t\t\t\t\t\tAge: %d\n",CurPres->Age);
    printf("\t\t\t\t\t\t\t\t\t\tGender: %s\n",CurPres->Gender);
    printf("\n\n\t\tMedications: \n");
    int i,t=CurPres->MedNo;
    for (i = 0; i < t; i++)
{
    printf("\t\t%d) Name: %-15s", i + 1, CurPres->Medicines[i].Name);
    printf("Dosage: %-10s", CurPres->Medicines[i].Dosage);
    printf("Quantity: %-5d", CurPres->Medicines[i].Quantity);
    printf("Frequency: %s\n", CurPres->Medicines[i].Frequency);
}

}
