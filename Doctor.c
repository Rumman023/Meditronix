
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include"Doctor.h"
#include"Array.h"
#include"ExpiryCheck.h"
#include"Customer.h"

#define PATH_TO_LOGIN_INFO "./DoctorInfo.txt"

void convertToChar(int* number, char str[])
{
    sprintf(str, "%d", *number);
    srand((unsigned)time(NULL));
    for (int i = 0; i < 5; i += ((rand() % 4)))
    {
        str[i] = str[i] + ((rand() % 22) + 17);
    }
    return;
}

int generateRandomNum(int n)
{
    srand((unsigned)time(NULL));
    return n * rand() % 99999;
}



///input of patient's info for the prescription generation

void getPatientInput(PatientInfo* patient)
{
    printf("\n\t\t\t\t\t\t\t\t\t\t\t\tGENERATE PRESCRIPTION\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t_____________________\t\t\t\t\n\n");
    printf("\n\t\t\t\t\t\t\t\t\t\tEnter patient information:\n");
    printf("\t\t\t\t\t\t\t\t\t\tName: ");
    fgets(patient->name, 50, stdin);
    printf("\t\t\t\t\t\t\t\t\t\tAge: ");
    scanf("%d", &patient->age);
    getchar();
    printf("\t\t\t\t\t\t\t\t\t\tGender: ");
    fgets(patient->gender, 20, stdin);
}

///input of medication info for the prescription generation

void getMedicationInput(MedicationInfo* medication, int num)
{
    printf("\n\t\t\t\t\t\t\t\t\t\tEnter information for Medicine %d:\n", num);
    printf("\t\t\t\t\t\t\t\t\t\tName: ");
    fgets(medication->name, 50, stdin);
    printf("\t\t\t\t\t\t\t\t\t\tDosage: ");
    fgets(medication->dosage, 20, stdin);
    printf("\t\t\t\t\t\t\t\t\t\tQuantity: ");
    scanf("%d", &medication->quantity);
    getchar();
    printf("\t\t\t\t\t\t\t\t\t\tFrequency: ");
    fgets(medication->frequency, 50, stdin);
}

///writing to the text file that contains prescription records

void createPrescription(char prescription[], int* unique, char* code, PatientInfo* patient, MedicationInfo* medications, int num_medications)
{
    *unique = generateRandomNum(rand());
    convertToChar(unique, code);
    int medicine_count= num_medications;

    sprintf(prescription, "Prescription Code: %s\n\nPatient Number: %d\nNumber of Medicine: %d\nName: %sAge: %d\nGender: %s", code, *unique, medicine_count, patient->name, patient->age, patient->gender);

    for (int i = 0; i < num_medications; i++)
    {
        sprintf(prescription + strlen(prescription), "Medication %d:\nName: %sDosage: %sQuantity: %d\nFrequency: %s\n", i+1, medications[i].name, medications[i].dosage, medications[i].quantity, medications[i].frequency);
    }

    FILE *fp3=fopen("\BuyingValidity.txt","a");
    FILE *fp4=fopen("\Name&code.txt", "a");

    fprintf(fp3,"%s\n",code);


    fprintf(fp4,"%s",patient->name);
    fprintf(fp4,"%s\n",code);


    for(int i = 0; i  < num_medications; i++)
    {
        fprintf(fp3,"%d ",medications[i].quantity);
    }
    fprintf(fp3,"\n\n");

    fclose(fp3);
    fclose(fp4);


}

///saving to the text file

void saveToFile(char prescription[], char file_name_str[])
{
    FILE* fp = fopen(file_name_str, "a");
    if (fp == NULL)
    {
        printf("[Error saving the file]\n");
        exit(1);
    }
    fprintf(fp, "%s\n", prescription);
    fclose(fp);
}

///printing the prescription records on command

void readAndDisplayFile(char file_name_str[])
{
    FILE* fp = fopen(file_name_str, "r");
    if (fp == NULL)
    {
        printf("[Error reading and displaying the file]\n");
        exit(1);
    }

    char buffer[500];
    printf("\n\t\t\t\t\t\t\t\t\tPRESCRIPTION RECORDS\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t\t____________________\t\t\t\t\n\n");
    while (fgets(buffer, 500, fp))
    {
        printf("%s", buffer);
    }

    fclose(fp);
}

///function that searches patient's name gives the corresponding prescription code

void GetCodebyPatientName()
{
    char patient_name[100];

    printf("\n\t\t\t\t\t\t\t\t\t\t\tSEARCH PATIENT\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t_______________\t\t\t\t\n\n");
    printf("\t\t\t\t\t\t\t\t\t\tEnter patient name: ");
    fgets(patient_name, 100, stdin);
    patient_name[strcspn(patient_name, "\n")] = '\0'; // Removes the trailing newline character

    FILE* file_ptr = fopen("Name&code.txt", "r");
    if (file_ptr == NULL)
    {
        printf("\t\t\t\t\t\t\t\t\t\tError opening file!\n");
        return;
    }

    char line[500];
    int found = 0;
    int name_matched = 0;

    while (fgets(line, 500, file_ptr) != NULL)
    {
        if (strstr(line, patient_name) != NULL)
        {
            if (name_matched == 0)
            {
                system("cls");
                printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\tSEARCH PATIENT\t\t\t\t\n");
                printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t_______________\t\t\t\t\n\n");
                printf("\n\n\t\t\t\t\t\t\t\t\t\tPatient Found!\n\n\t\t\t\t\t\t\t\t\t\tPrescription Code(s):\n");
                name_matched = 1;
            }

            char prescription_code[10];
            fgets(prescription_code, 10, file_ptr); // Read the prescription code from the next line
            prescription_code[strcspn(prescription_code, "\n")] = '\0'; // Remove the trailing newline character
            printf("\t\t\t\t\t\t\t\t\t\t%s\n", prescription_code);
            found++;
        }
    }

    fseek(file_ptr, 0, SEEK_SET);
    fclose(file_ptr);

    if (!found)
    {
        system("cls");
        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\tSEARCH PATIENT\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t_______________\t\t\t\t\n\n");
        printf("\nPatient not found!\n");
    }
}


///doctor's menu navigation

void Doctor_Menu()
{
    char choice;
    PatientInfo patient;
    MedicationInfo medications[20];
    int num_medications = 0; /// Counter
    char prescription[500], file_name_str[] = "Prescription.txt";
    int unique;
    char code[10];

    while (1)
    {
        system("cls");
        print_centre(" Doctor's Menu\n\n");
        print_centre("1. Create Prescription\n");
        print_centre("2. View Prescription Records\n");
        print_centre("3. Search Patient to Get Code\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t4. Exit\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\tEnter your choice: ");
        scanf(" %c", &choice);
        getchar();

        switch (choice)
        {
        case '1':
        {
            system("cls");
            num_medications = 0;
            getPatientInput(&patient);

            char add_medications_choice;
            do
            {
                getMedicationInput(&medications[num_medications], num_medications+1);
                num_medications++;
                printf("\n\t\t\t\t\t\t\t\t\t\tAdd another medicine? (y/n): ");
                scanf(" %c", &add_medications_choice);
                getchar();
            }
            while (add_medications_choice == 'y' || add_medications_choice == 'Y');

            createPrescription(prescription, &unique, code, &patient, medications, num_medications);
            saveToFile(prescription, file_name_str);

            system("cls");

            printf("\n\t\t\t\t\t\t\t\t\tGENERATE PRESCRIPTION\t\t\t\t\n");
            printf("\t\t\t\t\t\t\t\t\t_____________________\t\t\t\t\n\n");

            printf("\n\n\t\t\t\t\t\tPrescription has been created!\n\t\t\t\t\t\tThe prescription is saved to file %s\n\n", file_name_str);

            printf("\t\t\t\t\t\tPlease keep the Prescription code and Patient Number for future reference.\n\t\t\t\t\t\tPrescription Code: %s\n\t\t\t\t\t\tPatient Number: %d\n", code,unique);

            break;
        }
        case '2':
        {
            system("cls");

            readAndDisplayFile(file_name_str);
            break;
        }

        case '3':
        {
            system("cls");

            GetCodebyPatientName();
            break;
        }

        case '4':
        {
            system("cls");
            home();
        }
        default:
        {
            printf("\nInvalid choice! Please try again.\n");
            break;
        }
        }

        printf("\nPress enter to continue...");
        getchar();
    }
}

///login to doctor's menu

void login_to_DocMenu()
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
        printf("%120s","Welcome Rumman\n");
        Doctor_Menu();
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
