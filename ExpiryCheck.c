#include"ExpiryCheck.h"
#include<time.h>
#include<string.h>
#include"Array.h"
void print_date(int* month,int* year)
{
    time_t now = time(NULL);
    struct tm* cur_time = localtime(&now);

    *month = cur_time->tm_mon +1;
    *year = cur_time->tm_year + 1900;

    printf("Date: %d/%d/%d\n",cur_time->tm_mday,*month,*year);

    return;
}

void check_for_expired_meds( controller* array_control,int month,int year)
{
    for(int i=0; i<array_control->count; i++)
    {
        long long int exp_mon = (array_control->med_arr[i].expiry_year - 2000)*12 + array_control->med_arr[i].expiry_month;
        long long int date_since_2000 = (year-2000)*12 + month;
        if(exp_mon>=date_since_2000)
            strcpy(array_control->med_arr[i].status,"Valid");
        else
            strcpy(array_control->med_arr[i].status,"Expired!");
    }
}

void show_med_withType(controller* array_control)
{
    printf("\t\t\t\t\t\t\t");
    draw_border(120,'=');
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tInventory\n");
    printf("\t\t\t\t\t\t\t");
    draw_border(120,'=');
    printf("\t\t\t\t\t\t\t%5s %-20s %-15s %-9s %-10s %-12s %-9s %-10s %-10s\n", "Index)", "Name","Type", "Cost/Tk", "MRP/Tk", "Quantity", "Expiry", "Status", "Stock");

    for (int i = 0; i < array_control->count; i++) {
        char product_type[50];
        if(array_control->med_arr[i].tag == 's')
            strcpy(product_type,"Specialized");
        else if(array_control->med_arr[i].tag == 'g')
            strcpy(product_type,"Generic");


        if (array_control->med_arr[i].Quantity >= 5) {
            printf("\t\t\t\t\t\t\t%5d) %-20s %-15s %-10d %-10d %-10d %2d/%-7d %-10s %-10s\n", i + 1, array_control->med_arr[i].Name,
                   product_type,
                   array_control->med_arr[i].cost,
                   array_control->med_arr[i].mrp,
                   array_control->med_arr[i].Quantity,
                   array_control->med_arr[i].expiry_month,
                   array_control->med_arr[i].expiry_year,
                   array_control->med_arr[i].status,
                   "In Stock");
        }
        else if (array_control->med_arr[i].Quantity < 5 && array_control->med_arr[i].Quantity > 0) {
            printf("\t\t\t\t\t\t\t%5d) %-20s %-15s %-10d %-10d %-10d %2d/%-7d %-10s %-10s\n", i + 1, array_control->med_arr[i].Name,
                   product_type,
                   array_control->med_arr[i].cost,
                   array_control->med_arr[i].mrp,
                   array_control->med_arr[i].Quantity,
                   array_control->med_arr[i].expiry_month,
                   array_control->med_arr[i].expiry_year,
                   array_control->med_arr[i].status,
                   "Low Stock !");
        }
        else {
            printf("\t\t\t\t\t\t\t%5d) %-20s %-15s %-10d %-10d %-10d %2d/%-7d %-10s %-10s\n", i + 1, array_control->med_arr[i].Name,
                   product_type,
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
    draw_border(120,'=');
}

