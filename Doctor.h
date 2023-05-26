#include<string.h>
#pragma once

///struct for patient info
typedef struct
{
    char name[50];
    int age;
    char gender[20];
} PatientInfo;

///struct for medication info
typedef struct
{
    char name[50];
    char dosage[20];
    int quantity;
    char frequency[50];
} MedicationInfo;

void getPatientInput(PatientInfo* patient);
void getMedicationInput(MedicationInfo* medication, int num);
void createPrescription(char prescription[], int* unique, char* code, PatientInfo* patient, MedicationInfo* medications, int num_medications);
void saveToFile(char prescription[], char file_name_str[]);
void readAndDisplayFile(char file_name_str[]);
void GetCodebyPatientName();
void Doctor_Menu();
void login_to_DocMenu();
