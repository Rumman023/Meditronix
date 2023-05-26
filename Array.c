#include "Array.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

controller new_array(int init_size)
{
    controller ctrl = (controller)
    {
        .med_arr= NULL,
        .count = 0,
        .capacity = init_size
    };

    ctrl.med_arr = ( Medicine * )malloc(ctrl.capacity * sizeof(Medicine));

    if(ctrl.med_arr == NULL)
        exit(1);

    return ctrl;
}

int grow_array(controller *array_control,int new_capacity)
{


    Medicine* requested = ( Medicine * )realloc
                          (
                              array_control->med_arr,
                              ((array_control->capacity) +new_capacity)* sizeof(Medicine)
                          );
    if(requested == NULL)
    {
        return 0;
    }
    else
    {
        array_control->med_arr = requested;
        array_control->capacity+= new_capacity;
        return 1;
    }
}

//Minus 1 for any index entered, Index starts from 1 in the menu
void delete_med_byIndex(controller *array_control,int index_num)
{
    if(index_num>=1 && index_num<= array_control->count){
    for(int i=index_num-1; i<(array_control->count); i++)
    {
        array_control->med_arr[i]=array_control->med_arr[i+1];
    }
    array_control->count--;
    }


    else
    {
        printf("%40s","This index does not exist!!\n");
    }
}

void update_stock(controller *array_control,int index_num)
{
    //printf("%d\n",array_control->count);//For debugging

   if(index_num>=1 && index_num<= array_control->count){
    int new_expiry_month;
    int new_expiry_year;

    printf("Enter Expiry Date(mm/yyyy): ");
    scanf("%d/%d",&new_expiry_month,&new_expiry_year);

    int med_exp_month = array_control->med_arr[index_num-1].expiry_month;
    int med_exp_year = array_control->med_arr[index_num-1].expiry_year;
    int added_quantity;

    if(new_expiry_month == med_exp_month && new_expiry_year == med_exp_year)
    {
        printf("Enter quantity: ");
        scanf("%d",&added_quantity);
        array_control->med_arr[index_num-1].Quantity += added_quantity;
       // printf("%d",array_control->med_arr[index_num-1].Quantity); // debug

        printf("Enter Buying Cost: ");
        scanf("%d",&array_control->med_arr[index_num-1].cost);
        printf("Enter Selling Cost: ");
        scanf("%d",&array_control->med_arr[index_num-1].mrp);

        printf("Select tag(g or s): ");
        scanf(" %c",&array_control->med_arr[index_num-1].tag);
    }

    else
    {
        grow_array(array_control,2);

        int i = array_control->count;

        printf("Enter quantity added: ");
        scanf("%d",&array_control->med_arr[i].Quantity);
        printf("Enter Buying Cost: ");
        scanf("%d",&array_control->med_arr[i].cost);
        printf("Selling Rate(MRP): ");
        scanf("%d",&array_control->med_arr[i].mrp);
        printf("Select tag(g or s): ");
        scanf(" %c",&array_control->med_arr[i].tag);

        array_control->med_arr[i].expiry_month = new_expiry_month;
        array_control->med_arr[i].expiry_year = new_expiry_year;

        strcpy(array_control->med_arr[i].Name,array_control->med_arr[index_num-1].Name);
        array_control->count++;
    }
    }

    else
    {
        printf("%40s","This index does not exist!!\n");
    }
}

void delete_med_byName(controller *array_control,char* target_name)
{
    int size = array_control->count;
    int found_index;
    int found = 0; //false

    for(int i=0; i<size;i++)
        if(strcmp(array_control->med_arr[i].Name,target_name)==0)
            {
              found = 1;
              found_index = i+1;
              break;
            }

    if(found == 0)
    {
        printf("Name not Found !!\n");
        return;
    }
    else if (found == 1)
    {
        delete_med_byIndex(array_control,found_index);
    }

}

void swap(Medicine* med_a, Medicine* med_b)
{
    Medicine temp = *med_a;
    *med_a = *med_b;
    *med_b = temp;
}

int compare_Medicine(const void* a, const void* b) {
    const Medicine* med1 = (const Medicine*) a;
    const Medicine* med2 = (const Medicine*) b;

    return strcmp(med1->Name, med2->Name);
}

int compare_Medicine_byDate(const void* a, const void* b)
{
    const Medicine* med1 = (const Medicine*) a;
    const Medicine* med2 = (const Medicine*) b;

    if(med1->expiry_year > med2->expiry_year)
        return 1;

    else if(med1->expiry_year < med2->expiry_year)
        return -1;

    else if(med1->expiry_year == med2->expiry_year)
    {
        if(med1->expiry_month > med2->expiry_month)
            return 1;

        else if(med1->expiry_month < med2->expiry_month)
            return -1;

        else if(med1->expiry_month == med2->expiry_month)
            return 0;
    }
}



void sort_med_array(controller *array_control,int option)
{
    int size = array_control->count;
    if(option == 1)
    {
        qsort(array_control->med_arr,size, sizeof(Medicine), compare_Medicine);
    }

    else if (option == 2)
    {
        int expiry_count=0;
        int valid_count=0;
        int start=0;

        for(int i=0;i<array_control->count;i++)
        {
            if(strcmp(array_control->med_arr[i].status,"Expired!")==0)
            {
                swap(&array_control->med_arr[start++],&array_control->med_arr[i]);
            }
        }

    }

    else if (option == 3)
    {
        //Show Specialized meds first
        int start = 0;

        for(int i=0;i<array_control->count;i++)
        {
            if(array_control->med_arr[i].tag == 's')
            {
                swap(&array_control->med_arr[start++],&array_control->med_arr[i]);
            }
        }

    }

    else  if (option == 4)
       {
             //Show Generic meds first
              int start = 0;

        for(int i=0;i<array_control->count;i++)
        {
            if(array_control->med_arr[i].tag == 'g')
            {
                swap(&array_control->med_arr[start++],&array_control->med_arr[i]);
            }
        }

       }

    else if (option == 5)
    {

        //Arrange with dates that are close to expiry first
     qsort(array_control->med_arr,size, sizeof(Medicine), compare_Medicine_byDate);

    }


}

void help()
{
    draw_border(120,'=');
    printf("Syntaxes to follow:\n");
    draw_border(20,'~');
    printf("* Naming Syntax: Please use _ for space in words and for quoting dose/power of medicine\n");
    printf("  Example: Azmasol_Plus_25/125\n");
    printf("* For naming liquid products quote the volume after _\n");
    printf("  Example: Dettol_250ml i.e. Product_Volume(ug/mg/ml/l etc)\n");
    printf("* Please input date of expiry in the format mm/yyyy\n\n");
    printf("* For single character letter commands, you can input letters in upper or lower case\n");
    draw_border(120,'-');
    printf("How tagging works:\n");
    draw_border(20,'~');
    printf("* Tag medicines that are PRESCRIPTION ONLY with lowercase 's' shown as Specialized under Type\n");
    printf("* Tag medicines/products that do not require a prescription with lowercase 'g' shown as Generic under Type\n\n");
    draw_border(120,'-');
    printf("Inventory List element legends\n");
    draw_border(35,'~');
    printf("* Cost refers to wholesale buying cost PER UNIT of product\n");
    printf("* MRP refers to selling price PER UNIT of medicine/products\n");
    printf("** All costs and MRP are in the Currency BDT Taka\n\n");
    draw_border(120,'-');
    printf("* 1 unit Quantity equals one unit of medicine/product\n");
    printf("* Status column displays Expired when products are past expiry date\n");
    printf("* Stock column displays\n 1)In Stock for quantity>5\n 2)Low Stock for quantity<5\n 3)Empty!!Order Now for quantity=0\n\n");
    draw_border(120,'=');

}



