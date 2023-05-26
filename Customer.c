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

/*int inventory_size;
int quantity;



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


void login_customer()
{
    print_centre("Welcome to Customer window\n");
    print_centre("To buy medicine please log in\n");
    char input_code[100];
    char input_name[100];
    printf("\t\t\t\t\t\t\t\t\t\tName: ");
    fflush(stdin);
    scanf("%[^\n]s",&input_name);
    printf("\t\t\t\t\t\t\t\t\t\tUnique Prescription No: ");
    fflush(stdin);
    scanf("%s",&input_code);
    FILE* Log;
    Log = fopen(Prescriptions,"r");

    if(Log == NULL)
    {
        printf("Error: Prescription Info Not Found\n");
        home();
    }

    while(1)
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
        else if(Log==NULL)
        {
            printf("Error: Prescription Info Not Found\n");
            home();
        }
    }
    system("cls");
    Prescription* CurPres= get_prescription(Log);
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
            printf("Error cannot access shop\n");
        customer_deserialize_inventory(fp,&array_control,quantity);
        fclose(fp);
        FILE* val=fopen(PATH_TO_VALIDITYCHECKER,"r");
        while(1)
        {
            char val_code[100];
            fscanf(val,"%s",&val_code);
            if(strcmp(val_code,CurPres->PresCode)==0)break;
        }
        int j;
        for(j=0; j<CurPres->MedNo; j++)
        {
            fscanf(val,"%d",&CurPres->Medicines[j].PurchaseAbility);
        }
        fclose(val);

        int Bill=0;
        while(1)
        {
            int index,amount,i;
            printf("\t\t\t\t\t\t\tEnter index no of the medicine you want to buy: ");
            scanf("%d",&index);
            printf("\t\t\t\t\t\t\tEnter the quantity you want to buy: ");
            scanf("%d",&amount);
            for(i=0; i<quantity; i++)
            {
                if(strcmp(CurPres->Medicines[index-1].Name,array_control.med_arr[i].Name)==0)break;
            }
            if(i==quantity)
            {
                printf("\t\t\t\t\tSorry Medicine not available\n\t\t\t\t\tDo you want to buy anything else?(Y/N):");
                char P;
                fflush(stdin);
                scanf("%c",&P);
                if(P=='Y'||P=='y')
                {
                    continue;
                }
                else
                {
                    system("cls");
                    home();
                }
            }
            if(array_control.med_arr[i].Quantity<amount)
            {
                printf("\t\t\t\t\tSorry this amount of medicine is not in stock\n\t\t\t\t\tDo you want to buy anything else?(Y/N):");
                char P;
                fflush(stdin);
                scanf("%c",&P);
                if(P=='Y'||P=='y')
                {
                    continue;
                }
                else
                {
                    system("cls");
                    home();
                }
            }
            else if(CurPres->Medicines[index-1].PurchaseAbility<amount)
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
                    system("cls");
                    home();
                }
            }
            else
            {
                Bill+=(array_control.med_arr[i].mrp*amount);
                array_control.med_arr[i].Quantity-=amount;
                CurPres->Medicines[index-1].PurchaseAbility-=amount;
                printf("\t\t\t\t\t\tPrice of %s is %d.Your current Bill: %d .\n\t\t\t\t\t\tDo you want to buy anything else?(Y/N):"
                       ,CurPres->Medicines[index-1].Name,array_control.med_arr[i].mrp,Bill);
                char P;
                fflush(stdin);
                scanf("%c",&P);
                if(P=='Y'||P=='y')
                {
                    continue;
                }
                else
                {
                    system("cls");
                    printf("\t\t\t\t\t\t\t Thank you for shopping with us\n");

                    break;
                }

            }
        }
        FILE* fp6 = fopen(PATH_TO_FILE,"w");
                    FILE* fp7 = fopen(PATH_TO_LIST_SIZE,"w");

                    customer_serialize_List_size(fp7,array_control.count);
                    customer_serialize_inventory(fp6,&array_control,0,array_control.count);
                    fclose(fp6);
                    fclose(fp7);

                    FILE* Log5 = fopen(PATH_TO_VALIDITYCHECKER,"r");


                    Validity NewVal[10];
                    int v=0,V[10];
                    while(Log5!=NULL)
                    {
                        int l=0;
                        fscanf(Log5,"%s\n",NewVal[v].Code);
                        while(fscanf(Log5,"%d ",&NewVal[v].Val[l]))l++;
                        NewVal[v].Size=l+1;
                        v++;
                    }
                    fclose(Log5);

                    for(int k=0; k<v; k++)
                    {
                        if(strcmp(NewVal[k].Code,CurPres->PresCode)==0)
                        {
                            for(int g=0; g<CurPres->MedNo; g++)
                            {
                                NewVal[k].Val[g]=CurPres->Medicines[g].PurchaseAbility;
                            }
                        }
                    }

                    FILE* Log2 = fopen(PATH_TO_VALIDITYCHECKER,"w");
                    if(Log2==NULL)printf("Error");
                    int s,S;
                    for(s=0; s<=v; s++)
                    {
                        fprintf(Log2,"%s\n",NewVal[s].Code);
                        for(S=0; S<NewVal[s].Size; S++)fprintf(Log2,"%d ",NewVal[s].Val[S]);
                        fprintf(Log2,"\n\n" );

                    }
                    fclose(Log2);


    }
    else
    {
        printf("\t\t\t\t\t\t\tPress E to go back to main menu-");
        char exit;
        fflush(stdin);
        scanf("%c",&exit);
        system("cls");
        home();
    }

}
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
    for(i=0; i<t; i++)
    {
        printf("\t\t%d )\t",i+1);
        printf("Name: %s\t\t",CurPres->Medicines[i].Name);
        printf("Dosage : %s\t\t",CurPres->Medicines[i].Dosage);
        printf("Quantity: %d\t\t",CurPres->Medicines[i].Quantity);
        printf("Frequency: %s\n",CurPres->Medicines[i].Frequency);
    }
}
*/








/*FILE* Log;
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
    while(1)
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
        else if(Log==NULL)
        {
            print_centre("Error: Prescription Info Not Found\n");
            printf("\t\t\t\t\t\t\t\t\t\tPress any key to return to home page: ");
            char opt;
            scanf("%c",&opt);
            system("cls");
            home();
        }
    }
    system("cls");*/





    /*FILE* Log;
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
    //use int to track

    int found_code=0;

    while(feof(Log))
    {
        char scancode[100];
        fscanf(Log,"%s",&scancode);
        if(strcmp(scancode,input_code)==0)
        {
            fseek(Log, -(strlen(scancode)+19), SEEK_CUR);
            fscanf(Log,"%s",&scancode);
            if(strcasecmp(scancode,"Prescription")==0)
            {
                found_code++;
                break;
            }
            else
            {
                system("cls");
                home();
                break;
            }
        }

    }
    if(found_code==0)
    {
        print_centre("Error: Prescription Info Not Found\n");
        printf("\t\t\t\t\t\t\t\t\t\tPress any key to return to home page: ");
        char opt;
        scanf("%c",&opt);
        system("cls");
        home();
    }
    system("cls");*/



/*  for(i=0; i<t; i++)
    {
        printf("\t\t%d )\t",i+1);
        printf("Name: %s\t\t",CurPres->Medicines[i].Name);
        printf("Dosage : %s\t\t",CurPres->Medicines[i].Dosage);
        printf("Quantity: %d\t\t",CurPres->Medicines[i].Quantity);
        printf("Frequency: %s\n",CurPres->Medicines[i].Frequency);
    }*/


