// Antonio Hughes 
// Sandra Chavez 
// October 28, 2020

// Project 3 - Application for Thread Sorting

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// We declare our global variables of the array and the array size
int *originalArray;  // PrimaryArray
int sizeOfArray;     // size

// Set up structure that will allow of passing arguments to our thread function
typedef struct array_structure
{
    int *sorted_array_first;
    int *sorted_array_second;
} arrayStructure;

// This method will sort the first half of our array
void *sort_first_array(void *args){
    arrayStructure *primaryArrayStructure1 = args;

    int firstHalf = sizeOfArray/2;  //firstHalf == size 1
    int temp;

    // Chose to use bubble sort to sort the array
    for(int i = 0; i < firstHalf - 1; ++i){
        for(int j = 0; j < firstHalf - i - 1; ++j){
            if(primaryArrayStructure1->sorted_array_first[j] > primaryArrayStructure1->sorted_array_first[j + 1]){
                temp = primaryArrayStructure1->sorted_array_first[j];
                primaryArrayStructure1->sorted_array_first[j] = primaryArrayStructure1->sorted_array_first[j + 1];
                primaryArrayStructure1->sorted_array_first[j + 1] = temp;
            }
        }
    }
    return NULL;
}


// This method will sort the second half of our array
void *sort_second_array(void *args){
    arrayStructure *primaryArrayStructure2 = args;

    int secondHalf = sizeOfArray - (sizeOfArray/2);
    int temp;

    // Chose to use bubble sort to sort the array
    for(int i = 0; i < secondHalf - 1; ++i){
        for(int j = 0; j < secondHalf - i - 1; ++j){
            if(primaryArrayStructure2->sorted_array_second[j] > primaryArrayStructure2->sorted_array_second[j + 1]){
                temp = primaryArrayStructure2->sorted_array_second[j];
                primaryArrayStructure2->sorted_array_second[j] = primaryArrayStructure2->sorted_array_second[j + 1];
                primaryArrayStructure2->sorted_array_second[j + 1] = temp;
            }
        }
    }
    return NULL;
}

// This method will merge the two previously sorted arrays and sort it one more time
void *mergeArrays(void *args){
    arrayStructure *primaryArrayStructure1 = args;
    int firstHalf = sizeOfArray/2;
    int secondHalf = sizeOfArray - firstHalf;
    int i = 0, j = 0, k = 0;

    while(i < firstHalf && j < secondHalf){

        // If sorted array 1 is smaller than sorted array 2, then put array 1 element in primary array
        // else put element of sorted array 2 in primary array
        if (primaryArrayStructure1->sorted_array_first[i] < primaryArrayStructure1->sorted_array_second[j])
            originalArray[k++] = primaryArrayStructure1->sorted_array_first[i++];
        else
            originalArray[k++] = primaryArrayStructure1->sorted_array_second[j++];    
    }

    // Now we can store the rest of the elements of the first sorted array
    while(i < firstHalf)
        originalArray[k++] = primaryArrayStructure1->sorted_array_first[i++];
    
    // Now we can store the rest of the elements of the second sorted array
    while(j < secondHalf)
        originalArray[k++] = primaryArrayStructure1->sorted_array_second[j++]; 

    return NULL;
    
}

// Main function

int main(){

    // Declare threads
    pthread_t sort_thread_1;
    pthread_t sort_thread_2;
    pthread_t merge_threads;
    arrayStructure args;

    printf("Enter the size of the array to be sorted:");
    scanf("%d", &sizeOfArray);
    printf("\n");

    printf("Size of array is:%d\n", sizeOfArray);
    printf("\n");

    originalArray = (int *)malloc(sizeOfArray * sizeof(int));
    args.sorted_array_first = (int *)malloc((sizeOfArray/2) * sizeof(int));
    args.sorted_array_second = (int *)malloc((sizeOfArray - (sizeOfArray/2)) * sizeof(int));

    printf("Enter the Unsorted Original Array:");
    for (int i = 0; i < sizeOfArray; ++i){
        scanf("%d", &originalArray[i]);
    }
    
    // Passing first half of the original array to first sorted array
    for(int j = 0; j < sizeOfArray/2; ++j){
        args.sorted_array_first[j] = originalArray[j];
    }

    // Passing second half of the original array to second sorted array
    for(int k = 0; k < sizeOfArray - (sizeOfArray/2); ++k){
        args.sorted_array_second[k] = originalArray[k + (sizeOfArray/2)];
    }

    // Create threads and pass the arrays in
    pthread_create(&sort_thread_1, NULL, &sort_first_array, (void *)&args);
    pthread_create(&sort_thread_2, NULL, &sort_second_array, (void *)&args);

    // Wait for both threads to finish sorting
    pthread_join(sort_thread_1, NULL);
    pthread_join(sort_thread_2, NULL);

    // Print sorted array 1
    printf("\nSorted Thread 1: ");
    for(int k = 0; k < sizeOfArray/2; ++k){
        printf("%d ",args.sorted_array_first[k]);
    }
    printf("\n");

    // Print sorted array 2
    printf("\nSorted Thread 2: ");
    for(int x = 0; x < sizeOfArray - (sizeOfArray/2); ++x){
        printf("%d ",args.sorted_array_second[x]);
    }
    printf("\n");

    // Create merging thread and pass both sorted arrays into it
    pthread_create(&merge_threads, NULL, &mergeArrays, (void *)&args);

    // Wait until merging threads is finished merging the elements
    pthread_join(merge_threads, NULL);

    // Print the new original array
    printf("\nSorted Original Array: ");
    for(int l = 0; l < sizeOfArray; ++l){
        printf("%d ",originalArray[l]);
    }
    printf("\n\n");
}