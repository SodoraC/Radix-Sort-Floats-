#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100
#define NUM_BITS 32

int Negative_num_count = 0;
int Positive_num_count = 0;

const unsigned int NEGATIVE_POSITIVE_MASK = 1<<31;

void radix_sort(unsigned int array[], int n, int k);
void join_arrays(unsigned array[], unsigned array_0[], unsigned array_1[], int count_0s, int count_1s);
void print_arr(unsigned arr[], int arr_ct);

int main(){
    printf("Please enter your your numbers one at a time below: \n");
    int Number_counter = 0;
    float Array_of_numbers[MAX];
    unsigned unsigned_arr[MAX];
    char yn_str[10];

    while(true){
        printf("%d: ", Number_counter+1);
        scanf("%f", &Array_of_numbers[Number_counter]);
        Number_counter ++;

        if((Number_counter%5) == 0){
            printf("Do you want to enter more numbers? (yes or no): ");
            scanf("%s", yn_str);
            if(strcmp(yn_str, "yes") == 0)
                continue;
            else if(strcmp(yn_str, "no") == 0)
                break;
        }
        if(Number_counter == 100)
            break;
    }

    int neg_count = 0, pos_count = 0;
    unsigned neg_arr[MAX], pos_arr[MAX];
    
    for(int i = 0; i < Number_counter; i++){
        if((*((unsigned int *)&Array_of_numbers[i])&NEGATIVE_POSITIVE_MASK) == NEGATIVE_POSITIVE_MASK){
            neg_arr[neg_count] = *(unsigned int *)&Array_of_numbers[i];
            neg_count++;
        }
        else if((*((unsigned int *)&Array_of_numbers[i])&NEGATIVE_POSITIVE_MASK) == 0){
            pos_arr[pos_count] = *(unsigned int *)&Array_of_numbers[i];
            pos_count++;
        }
    }


    radix_sort(neg_arr, neg_count, NUM_BITS);
    radix_sort(pos_arr, pos_count, NUM_BITS);

    // reverse negative array
    unsigned neg_arr_rev[neg_count];
    int index = 0;
    for(int i = neg_count-1; i >= 0; i--){
        neg_arr_rev[index] = neg_arr[i];
        index++;
    }

    join_arrays(unsigned_arr, neg_arr_rev, pos_arr, neg_count, pos_count);

    // print_arr(neg_arr_rev, neg_count);
    // print_arr(pos_arr, pos_count);
    print_arr(unsigned_arr, Number_counter);
}


void radix_sort(unsigned int array[], int n, int k){
    unsigned int mask, count0 = 0, count1 = 0;
    unsigned int bucket0[MAX], bucket1[MAX];

    for(int d = 0; d < k; d++){
        mask = 1<<d; 
        int count0 = 0, count1 = 0;
        for(int i = 0; i < n; i++){
            if((array[i] & mask) == 0){
                bucket0[count0] = array[i];
                count0++;
            }
            else{
                bucket1[count1] = array[i];
                count1++;
            }
        }
        join_arrays(array, bucket0, bucket1, count0, count1);
    }
}


void join_arrays(unsigned array[], unsigned array_0[], unsigned array_1[], int count_0s, int count_1s){
    for(int i = 0; i < count_0s; i++){
        array[i] = array_0[i];

    }
    for(int i = 0; i < count_1s; i++){
        array[i+count_0s] = array_1[i];
    }
}

void print_arr(unsigned arr[], int arr_ct){
    float temp = 0;
    for(int i = 0; i < arr_ct; i++){
        temp=*(float *)&arr[i];
        printf("%.2f, ", temp);
    }
    printf("\n\n");
}